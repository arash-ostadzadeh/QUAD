/*
 *
 * "hArtes Reference/Benchmarking Application implementing matrix filtering (Tolstoy2)"
 *
 */
/**
 * @author        Gregor Heinrich (Arbylon) for<br>
 *                Fraunhofer Institute for Computer Graphics Research IGD<br>
 *                Cognitive Computing & Medical Imaging (A7)<br>
 *                Fraunhoferstr. 5, 64283 Darmstadt, Germany.
 *
 * @copyright     Copyright (c) 2006/2007 by Gregor Heinrich and Fraunhofer IGD.<br>
 *                All rights reserved.<br>
 *                Fraunhofer IGD provides this product without warranty of
 *                any kind and shall not be liable for any damages caused by
 *                the use of this product.
 *
 * @filename      mymath.c
 *
 * @file          mymath.c
 *
 *                Simple implementation of complex binary operations, FFT and
 *                convolution algorithms.
 *
 */

/* Note: FFT implementation based on code by Numerical Recipes
 * (Cambrige Univ. Press) and Martin Neumann's computational
 * physics notes (Univ. Vienna). Also, see Bronstein-Semendyayev.
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "mymath.h"

// windows: supress insecure warnings
#pragma warning( disable : 4996 )
#pragma warning( disable : 4244 )

#define TWOPI 6.28318530717959

#define SWAP(a,b) temp = (a); (a) = (b); (b) = temp

//; for statistics; count math-operations
//#define STATS

/******************* statistics **********************/

#ifdef STATS
void initflops() {
    flops.adds = 0;	
    flops.mults = 0;
    flops.tfuns = 0;
    flops.ffts = 0;
}
#endif

/******************** miscellaneous ******************/

int ldint(int n) {
    int p = -1;
    int m = n;
    while (m != 0) {
        m = m >> 1;
        p++;
    }
    // exact power?
    if (1 << p == n) {
        return p;
    }
    return p + 1;
}

/******************* complex stuff *******************/

complex cadd(complex x, complex y) {
    complex z;
    z.re = x.re + y.re;
    z.im = x.im + y.im;

#ifdef STATS
    flops.adds += 2;
#endif
    return z;
}

complex csub(complex x, complex y) {
    complex z;
    z.re = x.re - y.re;
    z.im = x.im - y.im;
#ifdef STATS
    flops.adds += 2;
#endif
    return z;
}

complex cmult(complex x, complex y) {
    complex z;
    real ac, bd;

    ac = x.re * y.re;
    bd = x.im * y.im;
    z.re = ac - bd;
    z.im = (x.re + x.im) * (y.re + y.im) - ac - bd;

#ifdef STATS
    // @hartes-library: depending on the hw architecture,
    // mults might not be more expensive than adds,
    // therefore also the direct multiplication
    // with 4 mults and 2 adds can be considered.
    flops.adds += 5;
    flops.mults += 3;
	flops.numberOfCmults += 1;
#endif
    return z;
}

complex cdiv(complex x, complex y) {
    complex z;
    real cd2;
    cd2 = y.re * y.re + y.im * y.im;
    z.re = (x.re * y.re + x.im * y.im) / cd2;
    z.im = (x.im * y.re - x.re * y.im) / cd2;
#ifdef STATS
    flops.adds += 3;
    flops.mults += 8;
#endif
    return z;
}

complex csmult(complex x, real a) {
    complex z;
    z.re = x.re * a;
    z.im = x.im * a;
#ifdef STATS
    flops.mults += 2;
#endif
    return z;
}

complex csdiv(complex x, real a) {
    complex z;
    z.re = x.re / a;
    z.im = x.im / a;
#ifdef STATS
    flops.mults += 2;
#endif
    return z;
}

real cmag(complex x) {
#ifdef STATS
    flops.adds +=1;
    flops.mults += 2;
    flops.tfuns += 1;
#endif
    return sqrt(x.re * x.re + x.im * x.im);
}

real _carg(complex x) {
#ifdef STATS
    flops.tfuns += 1;
#endif
    return atan2(x.im, x.re);
}

complex _cexp(real mag, real arg) {
    complex z;
    z.re = mag * cos(arg);
    z.im = mag * sin(arg);
#ifdef STATS
    flops.mults += 2;
    flops.tfuns += 2;
#endif
    return z;
}

int r2c(real* in, complex* out, int len) {
    int i;
    for (i = 0; i < len; i++) {
        out[i].re = in[i];
        out[i].im = 0.;
    }
    return 0;
}

int c2r(complex* in, real* out, int len, int mode) {
    int i;
    for (i = 0; i < len; i++) {
        if (mode == 0) {
            out[i] = (real) in[i].re;
        } else if (mode == 1) {
            out[i] = (real) in[i].im;
        } else if (mode == 2) {
            out[i] = (real) cmag(in[i]);
        } else if (mode == 3) {
            out[i] = (real) _carg(in[i]);
        } else {
            // error: \unknown mode
            return -1;
        }
    }
    return 0;
}

/********************* fft implementation *******************/

// TODO: implement real fft with half-complex format (saves almost
// half of the operations, see Chu and George 2000)
// TODO: implement half-complex reordering for SIMD operations a la brutefir

void ffw(complex *w,int idir,int n) {
    int i;
    real arg, phi;

    phi = idir * TWOPI / n;

    // TODO: this can be reduced using periodicities
    for(i=0; i<n/2; i++) {
        arg = i * phi;
        w[i].re = cos(arg);
        w[i].im = -sin(arg);
        //flops.tfuns += 2;
        //flops.mults += 3;
    }

}

int bitrev(int i,int m) {
    int ir,k;
    ir = 0;

    for(k=1; k<=m; k++) {
        ir = ir | ((i >> (k-1)) & 1) << (m-k);
    }
    return ir;
}

// @hartes-library: this should be done in hardware
void perm(complex* x, int m) {
    int n, i, ir;
    real temp;
    n = 1 << m;
    for(i=0; i<n; i++) {
        ir = bitrev(i, m);
        if(ir > i) {
            SWAP(x[ir].re, x[i].re);
            SWAP(x[ir].im, x[i].im);
        }
    }
}

/*
 * rationale: Because in the (R/T)OLS algorithm with half-frame overlap the input
 * would have to be copied twice for every signal frame, reusing an existing
 * copy of the previous input data saves 50% of input buffer copying. Nonreversed
 * and reversed permutation are being used alternatingly.
 */
// @hartes-library: this should be done in hardware
void permrev(complex* x, int m) {
    int n, i, ir;
    real temp;
    n = 1 << m;
    // TODO: integrate with bit reversal (becomes unsymmetric!)
    for (i=0; i<n/2; i++) {
        SWAP(x[i].re, x[i + n/2].re);
        SWAP(x[i].im, x[i + n/2].im);
    }
    for(i=0; i<n; i++) {
        ir = bitrev(i, m);
        if(ir > i) {
            SWAP(x[ir].re, x[i].re);
            SWAP(x[ir].im, x[i].im);
        }
    }
}

void permcpy(complex* x, complex* y, int m) {
    memcpy(y, x, (1 << m) * sizeof(complex));
    perm(y, m);
    // TODO: replace this by a direct assignment
    // from x to y
}

void permrevcpy(complex* x, complex* y, int m) {
    memcpy(y, x, (1 << m) * sizeof(complex));
    permrev(y, m);
    // TODO: replace this by a direct assignment
    // from x to y
}

void fft1d(complex *x, complex *w, int idir, int n) {
    int i, u, v, inca, incb, incn, j, k, ell;
    complex z;

    incn = n;
    inca = 1;
    // in-place butterfly (Danielson-Lanczos)
    while(incn > 1) {
        incn /= 2;
        incb = 2 * inca;
        i = 0;
        for(j=0; j<incn; j++) {
            k = 0;
            for(ell=0; ell<inca; ell++) {
                u = i + ell;
                v = u + inca;
                z.re = w[k].re * x[v].re - w[k].im * x[v].im;
                z.im = w[k].re * x[v].im + w[k].im * x[v].re;
                x[v].re = x[u].re - z.re;
                x[v].im = x[u].im - z.im;
                x[u].re = x[u].re + z.re;
                x[u].im = x[u].im + z.im;
                k += incn;
                //flops.mults += 4;
                //flops.adds += 6;
            }
            i += incb;
        }
        inca = incb;
    }

    // multiply by 1/n for inverse transform
    if(idir<0) {
        for(i=0; i<n; i++) {
            x[i].re = x[i].re / n;
            x[i].im = x[i].im / n;
            //flops.mults += 2;
        }
    }
#ifdef STATS
    flops.ffts += 1;
#endif
}

void fftrev(complex* x, complex* w, int m) {
    // permute input
    permrev(x, m);

    // perform forward transform
    fft1d(x, w, 1, 1 << m);
}

void fft(complex* x, complex* w, int m) {
    // permute input
    perm(x, m);

    // perform forward transform
    fft1d(x, w, 1, 1 << m);
}


void ifft(complex* x, complex* w, int m) {
    // permute input
    perm(x, m);

    // perform inverse transform
    fft1d(x, w, -1, 1 << m);

}

void ifftr(real* x, complex* w, int m) {

    // TODO: implement

}


void fftcpy(complex* x, complex* y, complex* w, int m) {
    // permute input
    permcpy(x, y, m);

    // perform forward transform
    fft1d(y, w, 1, 1 << m);
}

void ifftcpy(complex* x, complex* y, complex* w, int m) {
    // permute input
    permcpy(x, y, m);

    // perform inverse transform
    fft1d(y, w, -1, 1 << m);
}

/************************ convolution *************************/

void fconv(complex* x, complex* h, complex* y, complex* wf, complex* wi, int m) {
    complex *xspec, *hspec;
    int n = 1 << m, i;

    xspec = (complex*) malloc(n * sizeof(complex));
    hspec = (complex*) malloc(n * sizeof(complex));

    fftcpy(x, xspec, wf, m);
    fftcpy(h, hspec, wf, m);

    for(i = 0; i<n; i++) {
         xspec[i] = cmult(xspec[i], hspec[i]);
    }

    ifftcpy(xspec, y, wi, m);

    free(xspec);
    free(hspec);
}

void fwconv(complex* x, complex* h, complex* y, int m) {
    complex *wf, *wi;
    int n = 1 << m;

    wf = (complex*) malloc((n/2) * sizeof(complex));
    wi = (complex*) malloc((n/2) * sizeof(complex));

    // calculate phase factors for forward and inverse transform
    ffw(wf,1,n);
    ffw(wi,-1,n);

    fconv(x, h, y, wf, wi, m);

    free(wf);
    free(wi);
}

void tconv(complex* x, int xlen, complex* h, int hlen, complex* y) {
    int i, j;
    int ylen = xlen + hlen - 1;

    for (i = 0; i < ylen; i++) {
        y[i].re = 0.;
        y[i].im = 0.;
    }

    // for all signal samples
    for (i = 0; i < xlen; i++) {
        // for all impulse response samples
        for (j = 0; j < hlen; j++) {
            y[i + j] = cadd(y[i + j], cmult(x[i], h[j]));
        }
    }
}

#ifdef STATS
void tconvFlops(int xlen, int hlen, int complex) {
    if (complex) {
        flops.adds += xlen * hlen * (2 + 5);
        flops.mults += xlen * hlen * 3;
    } else {
        flops.adds += xlen * hlen;
        flops.mults += xlen * hlen;
    }
}
#endif

/************** vector operations ******************/

void vadd(real* x, real* y, int dim, real* z) {
    int i;
    for (i = 0; i < dim; ++i) {
        z[i] = x[i] + y[i];
    }
#ifdef STATS
    flops.adds += dim; 
#endif
}

void vsub(real* x, real* y, int dim, real* z) {
    int i;
    for (i = 0; i < dim; ++i) {
        z[i] = x[i] - y[i];
    }
#ifdef STATS
    flops.adds += dim;   
#endif
}

real vdotprod(real* x, int dim, real* y) {
    int i;
    real z = 0;
    for (i = 0; i < dim; ++i) {
        z += x[i] * y[i];
    }
#ifdef STATS
    flops.adds += dim;
    flops.mults += dim;
#endif
    return z;
}

void vcrossprod(real* x, real* y, int dim, real* z) {
    if (dim != 3) {
        return;
    }
    // TODO: for higher dimensions (via determinant?)
    z[0] = x[1] * y[2] - x[2] * y[1];
    z[1] = x[2] * y[0] - x[0] * y[2];
    z[2] = x[0] * y[1] - x[1] * y[0];
#ifdef STATS
    flops.adds += 6;
    flops.mults += 3;  
#endif
}

void vsmult(real* x, real a, int dim, real* z) {
    int i;
    for (i = 0; i < dim; ++i) {
        z[i] = x[i] * a;
    }
#ifdef STATS
    flops.mults += dim;    
#endif
}

real vmag(real* x, int dim) {
    int i;
    real mag = 0;
    for (i = 0; i < dim; ++i) {
        mag += x[i] * x[i];
    }
#ifdef STATS
    flops.mults += dim;
    flops.adds += dim;
    flops.tfuns += 1;  
#endif
    return sqrt(mag);
}


/********************* utilities ************************/

void zeroCplxVec(complex* x, int xlen) {
    int i;
    for (i = 0; i < xlen; i++) {
        x[i].re = 0.;
        x[i].im = 0.;
    }
}

void zeroRealVec(real* x, int xlen) {
    int i;

    // Note: memset does not work because IEEE-754, in which bit-0 in
    // floating point numbers maps to 0., is not part of the ANSI-C specification.
    for (i = 0; i < xlen; i++) {
        x[i] = 0.;
    }
}

complex** callocCplxArr(int M, int N) {
    int i;
    complex** aa;
    aa = (complex**) malloc(M * sizeof(complex*));
    for (i = 0; i < M; i++) {
        aa[i] = (complex*) calloc(N, sizeof(complex));
    }
    return aa;
}

real** callocRealArr(int M, int N) {
    int i;
    real** aa;
    aa = (real**) malloc(M * sizeof(real*));
    for (i = 0; i < M; i++) {
        aa[i] = (real*) calloc(N, sizeof(real));
    }
    return aa;
}

void freeCplxArr(complex** aa, int M) {
    int i;
    for (i = 0; i < M; i++) {
        free(aa[i]);
    }
    free(aa);
}

void freeRealArr(real** aa, int M) {
    int i;
    for (i = 0; i < M; i++) {
        free(aa[i]);
    }
    free(aa);
}


void printCplxVec(complex* x, int n) {
    int i;
    for(i=0;i<n;i++) {
        printf(" %5d %10.5f %10.5f\n",i,x[i].re,x[i].im);
    }
    printf("\n");
}

void printRealVec(real* x, int n) {
    int i;
    for(i=0;i<n;i++) {
        printf(" %5d %10.5f\n",i,x[i]);
    }
    printf("\n");
}

void printBits(int n) {
    int u, i;
    n = n & 0xFF;
    for (i = 1; i <= 8; i++) {
        u = n & (1 << (8 - i));
        printf("%i", u ? 1 : 0);
    }
    printf("\n");
}

/** Vector section */
real vmag2d(Vector2d v)
{
	real mag;
	mag = v.x * v.x + v.y * v.y;
#ifdef STATS
	flops.adds +=1;
	flops.mults += 2;
	flops.tfuns += 1;
#endif

	return sqrt(mag);

}

real varg2d(Vector2d v)
{
	real arg;
	arg = atan2(v.y, v.x);
#ifdef STATS
	flops.tfuns += 1;
#endif
	return arg;
}
real vmult2d(Vector2d v1, Vector2d v2)
{
	real mult;
	mult = v1.x * v2.x + v1.y * v2.y;
#ifdef STATS
	flops.adds += 1;
	flops.mults += 2;
#endif
	return mult;
}

Vector2d vsmult2d(Vector2d v1, real a)
{
	Vector2d v2;
	v2.x = a * v1.x;
	v2.y = a * v1.y;
#ifdef STATS
	flops.mults += 2;
#endif
	return v2;
}

Vector2d vadd2d(Vector2d v1, Vector2d v2)
{
	Vector2d v;
	v.x = v1.x + v2.x;
	v.y = v1.y + v2.y;
#ifdef STATS
	flops.adds += 2;
#endif
	return v;
}
Vector2d vsub2d(Vector2d v1, Vector2d v2)
{
	Vector2d v;
	v.x = v1.x - v2.x;
	v.y = v1.y - v2.y;
#ifdef STATS
	flops.adds += 2;
#endif
	return v;
}
real vcos2d(Vector2d v1, Vector2d v2)
{
	real cos;
	cos = vmult2d(v1, v2) / (vmag2d(v1) * vmag2d(v2));
#ifdef STATS
	flops.mults += 2;
#endif
	return cos;
}

real vsin2d(Vector2d v1, Vector2d v2)
{
	real sin;
	sin = ( (v1.x * v2.y) - (v1.y * v2.x) ) / ( vmag2d(v1) * vmag2d(v2) );
#ifdef STATS
	flops.mults += 4;
	flops.adds += 1;
#endif
	return sin;
}

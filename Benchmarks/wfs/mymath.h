/*
 *
 * "hArtes Reference/Benchmarking Application implementing matrix filtering (Tolstoy2)"
 *
 */
/**
 * @author      Gregor Heinrich (Arbylon) for<br>
 *              Fraunhofer Institute for Computer Graphics Research IGD<br>
 *              Cognitive Computing & Medical Imaging (A7)<br>
 *              Fraunhoferstr. 5, 64283 Darmstadt, Germany.
 *
 * @copyright   Copyright (c) 2006/2007 by Gregor Heinrich and Fraunhofer IGD.<br>
 *              All rights reserved.<br>
 *              Fraunhofer IGD provides this product without warranty of
 *              any kind and shall not be liable for any damages caused by
 *              the use of this product.
 *
 * @filename    mymath.h
 *
 * @file        mymath.h
 *
 *              Simple implementation of complex binary operations, FFT and
 *              convolution algorithms.
 *
 */

#ifndef MYMATH_H
#define MYMATH_H

// evaluate statistics
//#define STATS

/********** statistics ********************/


/** count the number of multiplications */
#ifdef STATS
struct _flops {
    /** real multiplications */
    unsigned long mults, multsDL, multsFLTR, multsFFT, multsSoFar;
    /** real additions */
    unsigned long adds, addsDL, addsFLTR, addsFFT, addsSoFar;
    /** transcendental functions (sin, cos, exp, sqrt) */
    unsigned long tfuns, tfunsSoFar;
    /** ffts (also included in the flop count) */
    unsigned long ffts;
	/** memory accesses */
	unsigned long memcpybytes, memcpys;
	/** number of complex multiplications */
	unsigned long numberOfCmults, numberOfCmultsSoFar;
} flops;

unsigned int memory;
#endif
/** reset flops */
void initflops();



/********** type definitions **************/

/**
 * real data type (float or double)
 */
//typedef double real;
typedef float real;

/**
 * complex data type
 */
typedef struct _cplx {
    real re;
    real im;
} complex;

/**
 * half complex data type
 */
//typedef real hcomplex;

/************* miscellaneous ****************/

/**
 * integer dual logarithm (aka next power of 2)
 *
 * @param n
 * @return dual logarithm (rounding up)
 */
 int ldint(int n);

/********** complex operations **************/

/**
 * complex multiplication
 *
 * @param x
 * @param y
 * @return x * y
 */
complex cadd(complex x, complex y);

/**
 * complex subtraction
 *
 * @param x
 * @param y
 * @return x * y
 */
complex csub(complex x, complex y);

/**
 * complex multiplication
 *
 * @param x
 * @param y
 * @return x * y
 */
complex cmult(complex x, complex y);

/**
 * complex division
 *
 * @param x
 * @param y
 * @return x * y
 */
complex cdiv(complex x, complex y);

/**
 * complex-scalar multiplication
 *
 * @param x
 * @param a
 * @return x * a
 */
complex csmult(complex x, real a);

/**
 * complex-scalar division
 *
 * @param x
 * @param a
 * @return x / y
 */
complex csdiv(complex x, real a);

/**
 * magnitude of a complex number
 *
 * @param x
 * @return |x|
 */
real cmag(complex x);

/**
 * phase of a complex number (using 4-quadrant arctan)
 *
 * @param x
 * @return arg(x)
 */
real _carg(complex x);

/**
 * complex number from magnitude and phase
 *
 * @param mag magnitude
 * @return mag * exp(j arg)
 */
complex _cexp(real mag, real arg);

/**
 * conversion from real to complex
 *
 * @param in real input
 * @param out complex output
 * @param len buffer lengths
 * @return error code <0 or 0.
 */
int r2c(real* in, complex* out, int len);

/**
 * conversion from complex to real
 *
 * @param in complex input
 * @param out real output
 * @param len buffer lengths
 * @param mode uses Re(z) if 0, Im(z) if 1, |z| if 2, arg(z) if 3
 * @return error code <0 or 0.
 */
int c2r(complex* in, real* out, int len, int mode);

/********** fft interface **************/

/**
 * bit reversal
 *
 * @param i number with bits
 * @param m number of total bits (=ld of size of fft n=2^m).
 */
int bitrev(int i,int m);

/**
 * calculate phase factors
 *
 * @param w [out] array of phase factors (fft size / 2)
 * @param idir direction (forward = 1, backward = -1)
 * @param size of fft
 */
void ffw(complex *w,int idir,int n);

/**
 * permutation from data order to butterfly order,
 *
 * @param x [in/out] data
 * @param m ld of fft size
 */
void perm(complex* x, int m);

/**
 * permutation from data order to butterfly order using reversed half-
 * frames
 *
 * @param x [in/out] data whose actual order is
 *        x[2^(m-1):2^m-1]x[0:2^(m-1)]
 * @param m ld of fft size
 */
void permrev(complex* x, int m);

/**
 * permutation from data order to butterfly order into
 * provided array.
 *
 * @param x [in] data
 * @param y [out] data
 * @param m ld of fft size
 */
void permcpy(complex* x, complex* y, int m);

/**
 * permutation from data order to butterfly order using reversed half-
 * frames, copies into the provided array.
 *
 * @param x [in/out] data whose actual order is
 *        x[2^(m-1):2^m-1]x[0:2^(m-1)]
 * @param m ld of fft size
 */
void permrevcpy(complex* x, complex* y, int m);

/**
 * fft core routine.
 * (must be prepended by a permutation)
 *
 * @param [in/out] time/freq domain vector
 * @param direction (forward = 1, backward = -1)
 * @param size of fft (should be 2^N)
 */
void fft1d(complex *x,complex *w,int idir,int n);

/**
 * complete in-place fft
 *
 * @param x [in/out] time/freq
 * @param w phase factors for transformation
 */
void fft(complex* x, complex* w, int m);

/**
 * complete in-place fft with reversed half-frame order
 *
 * @param x [in/out] time (with reversed half-frame order)/freq
 * @param w phase factors for transformation
 */
void fftrev(complex* x, complex* w, int m);

/**
 * complete in-place ifft
 *
 * @param x [in/out] freq/time
 * @param w phase factors for inverse transformation
 */
void ifft(complex* x, complex* w, int m);

/**
 * complete fft preserving input
 *
 * @param x [in] time
 * @param y [out] freq
 * @param w phase factors for transformation
 */
void fftcpy(complex* x, complex* y, complex* w, int m);

/**
 * complete ifft preserving input
 *
 * @param x [in] freq
 * @param y [out] time
 * @param w phase factors for transformation
 */
void ifftcpy(complex* x, complex* y, complex* w, int m);


/********** convolution interface **************/

/**
 * frequency-domain convolution
 *
 * @param x [in] time-domain signal x, length 2^(m-1)
 * @param h [in] impulse response h, length 2^(m-1)
 * @param y [out] convolved time-domain signal y = x ** h, length 2^m
 * @param wf phase factors for fft
 * @param wi phase factors for inverse fft
 * @param m ld of fft size
 */
void fconv(complex* x, complex* h, complex* y, complex* wf, complex* wi, int m);

/**
 * frequency-domain convolution with internal weights calculation
 *
 * @param x [in] time-domain signal x, length 2^(m-1) plus zero padding to length 2^m
 * @param h [in] impulse response h, length 2^(m-1) plus zero padding to length 2^m
 * @param y [out] convolved time-domain signal y = x ** h, length 2^m
 * @param m ld of fft size
 */
void fwconv(complex* x, complex* h, complex* y, int m);

/**
 * time-domain convolution
 *
 * @param x [in] time-domain signal x
 * @param xlen length of x
 * @param h [in] impulse response h
 * @param hlen length of h
 * @param y [out] convolved time-domain signal y = x ** h,
 *        length ylen = xlen + hlen - 1
 */
void tconv(complex* x, int xlen, complex* h, int hlen, complex* y);

/**
 * estimate the number of operations for tconv
 */
void tconvFlops(int xlen, int hlen, int complex);

/*********** vector operations **************/

/**
 * vector addition
 *
 * @param x
 * @param y
 * @param z = x + y
 */
void vadd(real* x, real* y, int dim, real* z);

/**
 * vector subtraction
 *
 * @param x
 * @param y
 * @param z = x - y
 */
void vsub(real* x, real* y, int dim, real* z);


/**
 * vector dot product
 *
 * @param x
 * @param y
 * @param z = x * y
 */
real vdotprod(real* x, int dim, real* y);

/**
 * vector cross product (implemented only in 3 dimensions)
 *
 * @param x
 * @param y
 * @param z = x X y
 */
void vcrossprod(real* x, real* y, int dim, real* z);

/**
 * vector-scalar multiplication
 *
 * @param x
 * @param y
 * @param z = x * a
 */
void vsmult(real* x, real a, int dim, real* z);

/**
 * vector magnitude
 *
 * @param x
 * @return |x|
 */
real vmag(real* x, int dim);

/*********** vector reset *******************/
/**
 * set vector to zero
 */
void zeroCplxVec(complex* x, int xlen);

/**
 * set vector to zero
 */
void zeroRealVec(real* x, int xlen);

/**
 * allocate a complex array of M rows and N columns
 * using calloc.
 *
 * @param M number of rows
 * @param N number of cols
 * @return array
 */
complex** callocCplxArr(int M, int N);

/**
 * allocate a real array of M rows and N columns
 * using calloc.
 *
 * @param M number of rows
 * @param N number of cols
 * @return array
 */
real** callocRealArr(int M, int N);

/**
 * free a complex array.
 *
 * @param aa array
 * @param M number of rows
 */
void freeCplxArr(complex** aa, int M);

/**
 * free a real array.
 *
 * @param aa array
 * @param M number of rows
 */
void freeRealArr(real** aa, int M);


/********** debug output **************/

/**
 * print complex vector of length n
 */
void printCplxVec(complex* x, int n);

/**
 * print real vector of length n
 */
void printRealVec(real* x, int n);

/**
 * print 8 lowest significant bits
 */
void printbits(int n);

/** Vector section */
typedef struct {
    real x;
    real y;
} Vector2d;

real vmag2d (Vector2d v);
real varg2d (Vector2d v);
real vmult2d (Vector2d v1, Vector2d v2);
Vector2d vsmult2d (Vector2d v, real a);
Vector2d vadd2d (Vector2d v1, Vector2d v2);
Vector2d vsub2d (Vector2d v1, Vector2d v2);
real vcos2d (Vector2d v1, Vector2d v2);
real vsin2d (Vector2d v1, Vector2d v2);
/** End of vector section */

#endif // MYMATH_H

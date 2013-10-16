CXX=gcc
CXXFLAGS= -Wall -pg

OBJS = Video_in.o DCT.o Q.o VLE.o Video_out.o mjpeg.o

PRG = mjpeg

all: ${PRG}


mjpeg:  ${OBJS}
	${CXX} ${CXXFLAGS} -o $@ ${OBJS}

Video_in.o: Video_in.c
	${CXX} ${CXXFLAGS} -c  $?

DCT.o: DCT.c
	${CXX} ${CXXFLAGS} -c  $?

Q.o: Q.c
	${CXX} ${CXXFLAGS} -c  $?

VLE.o: VLE.c
	${CXX} ${CXXFLAGS} -c  $?

Video_out.o: Video_out.c
	${CXX} ${CXXFLAGS} -c  $?

mjpeg.o: mjpeg.c
	${CXX} ${CXXFLAGS} -c  $?

run:
	./${PRG}
	gimp my_*.jpg &

tar:
	tar czvf mjpeg.tgz ./*


clean:
	rm -rf *~ *.o core *.jpg mjpeg *.tgz

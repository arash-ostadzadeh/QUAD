#ifndef CTIMEMEASUREMENT_H
#define CTIMEMEASUREMENT_H

#include <windows.h>


typedef struct TimeStruct {

	LARGE_INTEGER Freq;
	LARGE_INTEGER StartTime, EndTime;
	double ElapsedTime, ElapsedMilliseconds;

} TimeStruct;

    void CTimeMeasurement_start();
    void CTimeMeasurement_stop();
    double CTimeMeasurement_getMilliseconds();


#endif // #ifndef CTIMEMEASUREMENT_H

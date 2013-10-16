#include <windows.h>

#include "CtimeMeasurement.h"


TimeStruct timeData;
/*!
 * \brief
 * Starts the time measurement.
 */
void CTimeMeasurement_start() {

	QueryPerformanceFrequency(&timeData.Freq);
	QueryPerformanceCounter(&timeData.StartTime);

}


/*!
 * \brief
 * Returns the previously measured time.
 * 
 * \returns
 * The recorded time in millisecconds.
 * 
 */
double CTimeMeasurement_getMilliseconds() {

	return timeData.ElapsedMilliseconds; 

}



/*!
 * \brief
 * Stops the time measurement.
 * 
 */
void CTimeMeasurement_stop() {

	QueryPerformanceCounter(&timeData.EndTime);
	timeData.ElapsedTime = (double) ( timeData.EndTime.QuadPart - timeData.StartTime.QuadPart );
	timeData.ElapsedMilliseconds = (1000.0 * (double) timeData.ElapsedTime) / (double) timeData.Freq.QuadPart;

}
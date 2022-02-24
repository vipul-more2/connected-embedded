
//============================================================================
// Name        : ConnectedEmbeddedAssignment_1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "RTCDS3231.h"

using namespace std;

int main() {

	RTC_DS3231 rtcobj;
	rtcobj.getRTCtime();
        rtcobj.getRTCdate();
//	rtcobj.setRTCdate(4,16,2,22);
	rtcobj.getRTCdate();
//	rtcobj.setRTCtime(50,10,11);
	rtcobj.getRTCtemperature();
	rtcobj.getsquarewave(3);
	rtcobj.setAlarmClock(7,8,52,05,14,1);
	rtcobj.setAlarmClock_2(25,11,4,21,0);
	return 0;
}


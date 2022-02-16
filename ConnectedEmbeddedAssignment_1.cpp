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


	return 0;
}


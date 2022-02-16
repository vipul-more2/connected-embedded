/*
 * RTCDS3231.h
 *
 *  Created on: 13-Feb-2022
 *      Author: vipul
 */

#ifndef RTCDS3231_H_
#define RTCDS3231_H_





class RTC_DS3231 {

private :
	int file;
public:
	RTC_DS3231();

	void readRTCFile();
	void getRTCtime();
        int bcdToDec(char b);
	virtual ~RTC_DS3231();
};

#endif /* RTCDS3231_H_ */


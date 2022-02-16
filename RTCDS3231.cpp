/*
 * RTCDS3231.cpp
 *
 *  Created on: 13-Feb-2022
 *      Author: vipul
 */

#include "RTCDS3231.h"
#include<stdio.h>
#include<fcntl.h>
#include<sys/ioctl.h>
#include<linux/i2c.h>
#include<linux/i2c-dev.h>
#define BUFFER_SIZE 19
#include <iostream>
#include <string>
#include <unistd.h>
#include <csignal>


RTC_DS3231::RTC_DS3231() {
	// TODO Auto-generated constructor stub

}


void RTC_DS3231 :: readRTCFile(){

	   file=open("/dev/i2c-1", O_RDWR);

}

int RTC_DS3231 :: bcdToDec(char b){
	return (b/16)*10 + (b%16);
}



void RTC_DS3231 :: getRTCtime(){

	   readRTCFile();
	   ioctl(file, I2C_SLAVE, 0x68);
	   char writeBuffer[1] = {0x00};   //Creating buffer array to store the fetched data
	   write(file, writeBuffer, 1);
	   char buf[BUFFER_SIZE];          //write function stores the register values in the buffer
	   read(file, buf, BUFFER_SIZE);
	   printf("The RTC time is %02d:%02d:%02d\n", bcdToDec(buf[2]),   //from datasheet sec min and hours are in address
	         bcdToDec(buf[1]), bcdToDec(buf[0]));                     // 0x00, 0x01, 0x02 respectively
	   close(file);


}


RTC_DS3231::~RTC_DS3231() {
	// TODO Auto-generated destructor stub
}



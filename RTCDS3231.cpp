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

int RTC_DS3231 :: Dectobcd(char b){
return (b/10)*16 + (b%10);
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

void RTC_DS3231 :: getRTCdate(){


	readRTCFile();
		   ioctl(file, I2C_SLAVE, 0x68);
		   char writeBuffer[1] = {0x00};   //Creating buffer array to store the fetched data
		   write(file, writeBuffer, 1);
		   char buf[BUFFER_SIZE];          //write function stores the register values in the buffer
		   read(file, buf, BUFFER_SIZE);
		   printf("The RTC date is %02d:%02d:%02d\n", bcdToDec(buf[4]),   //from datasheet sec min and hours are in address
		         bcdToDec(buf[5]), bcdToDec(buf[6]));                     // 0x00, 0x01, 0x02 respectively
		   close(file);

}


void RTC_DS3231 :: setRTCdate(char day, char date, char month, char year){
			readRTCFile();
			ioctl(file,I2C_SLAVE, 0x68);
			char BufferforUpdate[19];
			BufferforUpdate[0]=0x3;
			BufferforUpdate[0]=Dectobcd(day);
			BufferforUpdate[1]=Dectobcd(date);
			BufferforUpdate[2]=Dectobcd(month);
			BufferforUpdate[3]=Dectobcd(year);
			write(file,BufferforUpdate,4);
			printf("Date successfully updated using setRTCdate function \n ");
			close(file);

}

void RTC_DS3231 :: setRTCtime(int seconds, int minute, int hours){
			readRTCFile();
			ioctl(file,I2C_SLAVE, 0x68);
			char BufferforUpdate[19];
			BufferforUpdate[0]=0x0;
			BufferforUpdate[1]=Dectobcd(seconds);
			BufferforUpdate[2]=Dectobcd(minute);
			BufferforUpdate[3]=Dectobcd(hours);
			write(file,BufferforUpdate,4);
			close(file);
			printf("Time updated successfully");
			getRTCtime();

}

void RTC_DS3231 :: getRTCtemperature(){
           readRTCFile();
           ioctl(file, I2C_SLAVE, 0x68);
           char temperatureBuffer[1] = {0x00};
           	   write(file, temperatureBuffer, 1);
           	   char tempbuf[BUFFER_SIZE];
           	   read(file, tempbuf, BUFFER_SIZE);
           	   printf("The surrounding temperature reading is %02d:%02d\n", bcdToDec(tempbuf[17]),
           	   bcdToDec(tempbuf[18]));
           	   close(file);

}

void RTC_DS3231 :: getsquarewave( int frequencyselector){

	readRTCFile();
	ioctl(file, I2C_SLAVE, 0x68);
	char squarewavegenbuffer[19];
	squarewavegenbuffer[0] = 0x0e;
	if (frequencyselector == 1){
		squarewavegenbuffer[1] = 0b00000100;
	}
	if (frequencyselector == 2){
		squarewavegenbuffer[1] = 0b00001100;
	}
	if (frequencyselector == 3){
		squarewavegenbuffer[1] = 0b00010100;
	}
	if (frequencyselector == 4){
		squarewavegenbuffer[1] = 0b00011100;
	}

	write(file, squarewavegenbuffer, 2);
	close(file);

}

void RTC_DS3231 :: setAlarmClock(int hours, int minutes, int seconds, int day, int date, int modeselector){
	readRTCFile();
	ioctl(file, I2C_SLAVE, 0x68);
        char alarmClockBuffer[19];
 	alarmClockBuffer[0] = 0x07;
    	alarmClockBuffer[1] = Dectobcd(seconds);
    	alarmClockBuffer[2] = Dectobcd(minutes);
    	alarmClockBuffer[3] = Dectobcd(hours);


   	 if (modeselector == 1){
    		alarmClockBuffer[4] = Dectobcd(5);
    			}

         else if (modeselector == 0){
    		alarmClockBuffer[4] = Dectobcd(4);
          }
         alarmClockBuffer[8] = 0b00000000;

    write(file,alarmClockBuffer, 5);
 close(file);
    
    readRTCFile();
ioctl(file,I2C_SLAVE,0x68);

           
  char tempbuf2[1]={0x00};
write(file, tempbuf2,1);
char buf[19];
               	   read(file,buf, 19);
               	   printf("Alarm 1 is set at  %02d:%02d:%02d:%02d\n", bcdToDec(buf[9]),
               	   bcdToDec(buf[8]),bcdToDec(buf[7]),bcdToDec(buf[10]));
               	  printf("Value of register is %02d:%02d\n",bcdToDec(buf[15]),buf[15]);
printf("Value of buf 14 is %02d:%02d\n",bcdToDec(buf[14]),buf[14]);	        
	 close(file);
}


      void RTC_DS3231 :: setAlarmClock_2(int hours, int minutes, int day, int date, int modeselector){
        readRTCFile();
        ioctl(file, I2C_SLAVE, 0x68);
        char alarmClockBuffer[19];
        alarmClockBuffer[0] = 0x0B;
        alarmClockBuffer[1] = Dectobcd(minutes);
        alarmClockBuffer[2] = Dectobcd(hours);

         if (modeselector == 1){
                alarmClockBuffer[3] = Dectobcd(5);
                        }

    else if (modeselector == 0){
                alarmClockBuffer[3] = Dectobcd(8);
                  }
 
alarmClockBuffer[4] = 0b00000011;

    write(file,alarmClockBuffer, 5);
 close(file);
    
    readRTCFile();
ioctl(file,I2C_SLAVE,0x68);

        char tempbuf2[1]={0x00};
write(file, tempbuf2,1);
char buf[19];


                   read(file, buf, 19);
                   printf("Alarm 2 is set at  %02d:%02d:%02d\n", bcdToDec(buf[13]),
                   bcdToDec(buf[12]),bcdToDec(buf[14]));
                   close(file);


}









RTC_DS3231::~RTC_DS3231() {
	// TODO Auto-generated destructor stub
}



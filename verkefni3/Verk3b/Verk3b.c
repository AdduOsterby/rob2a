#pragma config(Sensor, in4,    middleLine,     sensorLineFollower)
#pragma config(Sensor, in5,    rightLine,      sensorLineFollower)
#pragma config(Sensor, in6,    leftLine,       sensorLineFollower)
#pragma config(Sensor, in7,    lightSensor,    sensorReflection)
#pragma config(Sensor, in8,    petentiometer,  sensorPotentiometer)
#pragma config(Sensor, dgtl1,  sonar,          sensorSONAR_cm)
#pragma config(Sensor, dgtl3,  frontTouch,     sensorTouch)
#pragma config(Sensor, dgtl4,  leftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl6,  rightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl8,  clawTouch,      sensorTouch)
#pragma config(Motor,  port2,           leftMotor,     tmotorVex269, openLoop, reversed)
#pragma config(Motor,  port3,           rightMotor,    tmotorVex269, openLoop)
#pragma config(Motor,  port6,           clawMotor,     tmotorVex269, openLoop)
#pragma config(Motor,  port7,           armMotor,      tmotorVex269, openLoop)

/*----------------------------------------------------------------------------------------------------*\
|*                                         			- verkefni 3b -          	                            *|
|*                                      												                                      *|
|*										 The robot is coded to follow a guide of 14, 90 degree, turns 					 	     	*|
|* 						 					 			by setting the encoders to the correct value 														*|
|*										 A button coded for the controller to stop the robot mid program								*|
|*																																																		*|
\*-----------------------------------------------------------------------------------------------4246-*/
#include "../../includes/headers/myheader.h"
#include "../../includes/functions/motorFunctions.inc"
//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++
bool turnArray[14]={0,1,1,0,0,1,0,0,1,0,0,1,1,0};

task main()
{
	StartTask(battery);
	StartTask(stopMyTasksC);
	StartTask(stopMyTasksR);
		wait1Msec(2000);
		for(int i=0;i<15;i++){
			stopMotors();
			resetEncoder();
			driveEncoder(BASEDIST, true);
			stopMotors();
			resetEncoder();
			turn(BASETURN, turnArray[i]);
		}
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

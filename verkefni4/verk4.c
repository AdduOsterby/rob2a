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
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*----------------------------------------------------------------------------------------------------*\
|*                                 						- Verkefni 4 - 					                                *|
|*                                      												                                      *|
|*                     Robot is made to drive nonstop and turn when the sonar sensor                  *|
|*                     senses an object in close proximity to itself and then turns. 									*|
|*                        When light sensor stops sensing light the robot will stop										*|
|* 														and then continue again after light is turned on.												*|
\*-----------------------------------------------------------------------------------------------4246-*/
#include "../includes/headers/myheader.h"
#include "../includes/functions/motorFunctions.inc"
//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++
task main()
{
	StartTask(battery);
	StartTask(stopMyTasksC);
	wait1Msec(2000);
	while(1 == 1) {
		while(SensorValue(sonar) > 30  || SensorValue(sonar) == -1)
		{
			motor[rightMotor] = 63;
			motor[leftMotor]  = 63;
			light();
		}
		stopMotors();
		turn(BASETURN, 1);
		stopMotors();
		light();
	}
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

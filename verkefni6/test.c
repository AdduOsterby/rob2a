#pragma config(I2C_Usage, I2C1, i2cSensors)
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
#pragma config(Sensor, I2C_1,  rightEncoder,   sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  leftEncoder,    sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port1,           rightMotor,    tmotorVex393, openLoop, reversed, encoder, encoderPort, I2C_1, 1000)
#pragma config(Motor,  port2,            ,             tmotorVex393, openLoop)
#pragma config(Motor,  port3,            ,             tmotorVex393, openLoop)
#pragma config(Motor,  port6,           clawMotor,     tmotorVex269, openLoop)
#pragma config(Motor,  port7,           armMotor,      tmotorVex269, openLoop)
#pragma config(Motor,  port10,          leftMotor,     tmotorVex393, openLoop, reversed, encoder, encoderPort, I2C_2, 1000)

#include "../includes/headers/myheader.h"
#include "../includes/functions/motorFunctions.inc"

task main()
{
	StartTask(stopRobot);
	StartTask(followLine);
	int bottleCount = 0;
	int counter = 1;
	bool turnArray[3] = {0,1,0};
	while(bottleCount != 3){
		//turn(BASETURN*2, true);

		for(int i = 0; i < 2; i++){
			openClaw();
			turnGiro(900*2,true);
			resetEncoder();

			driveEncoder(BASEDIST, true);

			stopMotors();
			resetEncoder();
			//turn(BASEDIST, true);
			turnGiro(900,true);
			stopMotors();
			resetEncoder();
			for(int x = 0; x < counter; x++) {
				driveEncoder(BASEDIST, true);
				stopMotors();
				resetEncoder();
			}
			turnGiro(900, turnArray[bottleCount]);
			stopMotors();
			resetEncoder();

			driveEncoder(BASEDIST, true);
			stopMotors();
			wait1Msec(500);
			StartTask(closeClaw);
			wait1Msec(1000);
			if(i==0){
				StartTask(liftArm);
			}
			else {
				StopTask(liftArm);
				releaseArm();
			}

			/*turnGiro(900*2, );
			stopMotors();
			resetEncoder();

			driveEncoder(BASEDIST,true);
			stopMotors();*/
		}
		bottleCount++;
		counter--;
	}
}

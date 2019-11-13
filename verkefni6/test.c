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

bool right = false;
bool left = false;
bool middle = false;

void find()
{
	while(middle < 1530){
		if(right){
			motor[leftMotor]  = 7;
	    motor[rightMotor] = 60;
		}
		else if(left){
			motor[leftMotor]  = 60;
      motor[rightMotor] = 7;
		}
	}
}

task main()
{
	while(true){
		if(SensorValue(middleLine) > 2000){
			middle = true;
			right = false;
			left = false;
		}
		else if(SensorValue(leftLine) > 2000){
			right = true;
			left = false;
			middle = false;
		}
		else if(SensorValue(rightLine) > 2000){
			left = true;
			right = false;
			middle = false;
		}
	}
}

void driveTime(int counter, bool b_f) {
		int dir = (b_f)? (1):(-1);
		motor[rightMotor] = dir*127;
		motor[leftMotor]  = dir*127;
		wait1Msec(counter);
}

void resetEncoder() {
	nMotorEncoder[rightMotor] = 0;
	nMotorEncoder[leftMotor] = 0;
}

void driveEncoder(int dist, bool b_f) {
	int dir = (b_f)? (1):(-1);
	while(dist > abs(nMotorEncoder[leftMotor])) {
		if(abs(nMotorEncoder[rightMotor]) == abs(nMotorEncoder[leftMotor]))
			{
				// Move Forward
				motor[rightMotor] = 80 * dir;
				motor[leftMotor]  = 80 * dir;
			}
			else if(abs(nMotorEncoder[rightMotor]) > abs(nMotorEncoder[leftMotor]))
			{
				if(dir == -1) {
					// Turn slightly right
					motor[rightMotor] = 70 * dir;
					motor[leftMotor]  = 80 * dir;
				}
				else {
					motor[rightMotor] = 90 * dir;
					motor[leftMotor]  = 60 * dir;
				}
			}
			else
			{
				// Turn slightly left
				motor[rightMotor] = 80 * dir;
				motor[leftMotor]  = 60 * dir;
			}
		}
	}

void stopMotors(){
  motor[rightMotor] = 0;
  motor[leftMotor] = 0;
  wait1Msec(1000);
}

void turn(int dist, bool l_r)
{
  resetEncoder();

  while(abs(nMotorEncoder[rightMotor]) < dist)
  {
	if(l_r == false){
      motor[rightMotor] = -63;
      motor[leftMotor]  = 63;
	}
	else{
	  motor[rightMotor] = 63;
      motor[leftMotor]  = -63;
	}
  }
}

task stopRobot() {
	while(1==1) {
		if(vexRT[Btn8L]==1) {
			StopAllTasks();
		}
		else if(SensorValue[frontTouch]==1) {
			StopAllTasks();
		}
	}
}

task battery()
{
	bLCDBacklight = true;									// Turn on LCD Backlight
	string mainBattery, backupBattery;

	while(true)														// An infinite loop to keep the program running until you terminate it
	{
		clearLCDLine(0);											// Clear line 1 (0) of the LCD
		clearLCDLine(1);											// Clear line 2 (1) of the LCD

		//Display the Primary Robot battery voltage
		displayLCDString(0, 0, "Primary: ");
		sprintf(mainBattery, "%1.2f%c", nImmediateBatteryLevel/1000.0,'V'); //Build the value to be displayed
		displayNextLCDString(mainBattery);

		//Display the Backup battery voltage
		displayLCDString(1, 0, "Backup: ");
		sprintf(backupBattery, "%1.2f%c", BackupBatteryLevel/1000.0, 'V');	//Build the value to be displayed
		displayNextLCDString(backupBattery);

		//Short delay for the LCD refresh rate
		wait1Msec(100);
	}
}
void light() {
	while(SensorValue(lightSensor) > 500)
	{

		motor[rightMotor] = 0;
		motor[leftMotor]  = 0;
	}
}


task verk2c()
{
	bool turnArray[14]={0,1,1,0,0,1,0,0,1,0,0,1,1,0};
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

void find(string last)
{
		while(SensorValue(middleLine) < 2000){
			if(last == "right"){
				motor[leftMotor]  = 10;
				motor[rightMotor] = 60;
			}
			else if(last == "left"){
				motor[leftMotor]  = 60;
				motor[rightMotor] = 10;
			}
			else if(last == "middle") {
				motor[leftMotor]  = -60;
				motor[rightMotor] = -60;
			}
		}
		stopMotors();
	}
task followLine()
{
	bool right = false;
	bool left = false;
	bool middle = false;
	string last;
	while(true){
		if(!middle && !left && !right) {
			find(last);
		}
		if(SensorValue(middleLine) > 2000){
			middle = true;
			right = false;
			left = false;
			last = "middle";
		}
		else if(SensorValue(leftLine) > 2000){
			right = true;
			left = false;
			middle = false;
			last = "right";
		}
		else if(SensorValue(rightLine) > 2000){
			left = true;
			right = false;
			middle = false;
			last = "left";
		}
		else if((SensorValue(middleLine) > 2000 && SensorValue(rightLine) > 2000) || (SensorValue(middleLine) > 2000 && SensorValue(leftLine))) {
			middle = true;
			right = false;
			left = false;
			last = "middle";
		}

		else if(SensorValue(rightLine) < 2000 && SensorValue(leftLine) < 2000 && SensorValue(middleLine) < 2000)
			left = false;
			right = false;
			middle = false;
		}
}

void turnGiro(int degrees10,bool counterclock){
	//Completely clear out any previous sensor readings by setting the port to "sensorNone"
	SensorType[in3] = sensorNone;
  wait1Msec(1000);
  //Reconfigure Analog Port 7 as a Gyro sensor and allow time for ROBOTC to calibrate it
  SensorType[in3] = sensorGyro;
  wait1Msec(2000);

  while(abs(SensorValue[in3]) < degrees10)
  {
		if (counterclock){
		motor[rightMotor] = 70;
		motor[leftMotor] = -70;
		}
		else{
		motor[rightMotor] = -70;
		motor[leftMotor] = 70;
		}
  }

  //Brief brake to stop some drift
  motor[rightMotor] = -5;
  motor[leftMotor] = 5;
  wait1Msec(250);
}

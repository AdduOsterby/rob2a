void driveTime(int counter, bool b_f) {
		int dir = (b_f)? (1):(-1);
		motor[rightMotor] = dir*127;
		motor[leftMotor]  = dir*127;
		wait1Msec(counter);
}

void resetEncoder() {
	SensorValue[rightEncoder] = 0;
	SensorValue[leftEncoder] = 0;
}

void driveEncoder(int dist, bool b_f) {
	int dir = (b_f)? (1):(-1);
	while(dist > abs(SensorValue[leftEncoder])) {
		if(abs(SensorValue[rightEncoder]) == abs(SensorValue[leftEncoder])) 
			{
				// Move Forward
				motor[rightMotor] = 80 * dir;		   
				motor[leftMotor]  = 80 * dir;		    
			}
			else if(abs(SensorValue[rightEncoder]) > abs(SensorValue[leftEncoder]))	
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
				motor[rightMotor] = 60 * dir;		    
				motor[leftMotor]  = 80 * dir;		    
			}
		}
	}
	
void stopMotors(){
  motor(rightMotor) = 0;
  motor(leftMotor) = 0;
  wait1Msec(1000);
}
	
void turn(int dist, bool l_r)
{ 
  resetEncoder();
  
  while(abs(SensorValue[rightEncoder]) < dist)
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
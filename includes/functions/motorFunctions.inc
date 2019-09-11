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
		if(abs(SensorValue[rightEncoder]) == abs(SensorValue[leftEncoder])) // If rightEncoder has counted the same amount as leftEncoder:
			{
				// Move Forward
				motor[rightMotor] = 80 * dir;		    // Right Motor is run at power level 80
				motor[leftMotor]  = 80 * dir;		    // Left Motor is run at power level 80
			}
			else if(abs(SensorValue[rightEncoder]) > abs(SensorValue[leftEncoder]))	// If rightEncoder has counted more encoder counts
			{
				if(dir == false) {
					// Turn slightly right
					motor[rightMotor] = 60 * dir;		    // Right Motor is run at power level 60
					motor[leftMotor]  = 80 * dir;		    // Left Motor is run at power level 80
				}
				else {
					motor[rightMotor] = 90 * dir;		    // Right Motor is run at power level 60
					motor[leftMotor]  = 60 * dir;
				}
			}
			else	// Only runs if leftEncoder has counted more encoder counts
			{
				// Turn slightly left
				motor[rightMotor] = 60 * dir;		    // Right Motor is run at power level 80
				motor[leftMotor]  = 80 * dir;		    // Left Motor is run at power level 60
			}
		}
	}

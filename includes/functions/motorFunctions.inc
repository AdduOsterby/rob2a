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

task stopMyTasks(){
	while(vexRT[Btn8L]!=1){
	}
	StopAllTasks();
}
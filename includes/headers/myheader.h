

#define BASETIME 1500
#define BASEDIST 560 //er 540
#define BASETURN 250
#define MAXSPEED 60
#define MINSPEED 10

void driveTime(int counter, bool b_f);

void resetEncoder();

void stopMotors();

void driveEncoder(int dist, bool b_f);

void turn(int dist, bool l_r);

void light();

void find(string last);

void turnGiro(int degrees10,bool counterclock);

void releaseArm();

void openClaw();
#include <NewPing.h>

#define S1Trig A4
#define S1Echo A5
#define S2Trig A2
#define S2Echo A3
#define S3Trig A0
#define S3Echo A1


//Create objects for the motors
#define motor1F 4
#define motor1B 5
#define motor2F 6
#define motor2B 7


#define ENBa 3
#define ENBb 11

#define Bump 13
#define Flame 2


int distance=0, t=0;

int i= 1;

void setup() {
	Serial.begin(9600);
	//Set the Trig pins as output pins
	pinMode(S1Trig, OUTPUT);
	pinMode(S2Trig, OUTPUT);
	pinMode(S3Trig, OUTPUT);
	//Set the Echo pins as input pins
	pinMode(S1Echo, INPUT);
	pinMode(S2Echo, INPUT);
	pinMode(S3Echo, INPUT);
	
	pinMode(Bump, OUTPUT);
	pinMode(Flame, INPUT);

	analogWrite (ENBa, 100) ;
	analogWrite (ENBb, 100) ;
}

void loop() {

	MOVE();
	

}

//Get the sensor values
int sensorOne() 
{
	//pulse output
	digitalWrite(S1Trig, LOW);
	delayMicroseconds(5);
	digitalWrite(S1Trig, HIGH);
	delayMicroseconds(10);
	digitalWrite(S1Trig, LOW);

	t = pulseIn(S1Echo, HIGH);//Get the pulse
	distance = t /57; // Distance = (Speed of Sound * Time/ 2) = t / (1/(350 * 0.0001/2 ))   0.0001 ---> conver to cm
	return distance; // Return the values from the sensor
}//end sensor 1

//Get the sensor values
int sensorTwo() {
	//pulse output
	digitalWrite(S2Trig, LOW);
	delayMicroseconds(5);
	digitalWrite(S2Trig, HIGH);
	delayMicroseconds(10);
	digitalWrite(S2Trig, LOW);

	t = pulseIn(S2Echo, HIGH);
	distance = t /57;
	return distance;
}


int sensorThree() {
	//pulse output
	digitalWrite(S3Trig, LOW);
	delayMicroseconds(5);
	digitalWrite(S3Trig, HIGH);
	delayMicroseconds(10);
	digitalWrite(S3Trig, LOW);

	t = pulseIn(S3Echo, HIGH);
	distance = t /57;
	return distance;
}

/*******************Motor functions**********************/
void forward() {
	analogWrite (ENBa, 150) ;
	analogWrite (ENBb, 150) ;
	digitalWrite (motor1F, HIGH) ;
	digitalWrite (motor1B, LOW) ;
	digitalWrite (motor2F, HIGH) ;
	digitalWrite (motor2B, LOW) ;
}
void back() {
	analogWrite (ENBa, 130) ;
	analogWrite (ENBb, 130) ;
	digitalWrite (motor1F, LOW) ;
	digitalWrite (motor1B, HIGH) ;
	digitalWrite (motor2F, LOW) ;
	digitalWrite (motor2B, HIGH);
}
void left() {
	analogWrite (ENBa, 130) ;
	analogWrite (ENBb, 110) ;
	digitalWrite (motor1F, HIGH) ;
	digitalWrite (motor1B, LOW) ;
	digitalWrite (motor2F, LOW) ;
	digitalWrite (motor2B, HIGH) ;
}
void right() {
	analogWrite (ENBa, 110) ;
	analogWrite (ENBb, 130) ;
	digitalWrite (motor1F, LOW) ;
	digitalWrite (motor1B, HIGH) ;
	digitalWrite (motor2F, HIGH) ;
	digitalWrite (motor2B, LOW) ;
}
void Stop() {
	digitalWrite (motor1F, LOW) ;
	digitalWrite (motor1B, LOW) ;
	digitalWrite (motor2F, LOW) ;
	digitalWrite (motor2B, LOW) ;
}



void offFire()
{
	//int Fire = analogRead(Flame); //AO pin
	//if (Fire >= 500)

	int Fire = digitalRead(Flame); //DO pin

	if (Fire == LOW)
	{
		Serial.println("Fire! Fire! Fire! Fire! ");
		digitalWrite(Bump , HIGH);
		Stop();
	}
	else
	{
		digitalWrite(Bump, LOW);
		Serial.println(" Forward");
		forward();
	}
	delay(300);
}//end offfire
////////////////////////////////////////////////////////////////////////////
void MOVE()
{

	int centerSensor = sensorTwo();
	int leftSensor = sensorOne();
	int rightSensor = sensorThree();

	// Check the distance using the IF condition
	if ( 15 >= centerSensor) 
	{
		Stop();
		Serial.println("Stop");
		delay(50);

		back();
		Serial.println("BACK");
		delay(100);

		if (leftSensor > rightSensor) 
		{
			left();
			Serial.println("Left");
			delay(300);
			
		}//end if left > right
		else
	   {
			right();
			Serial.println("Right");
			delay(300);
		}//end if left < right
	}//end if
	offFire();
}//end move
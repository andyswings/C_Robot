#include <iostream>
#include <wiringPi.h>
#include <softPwm.h>
#include "libSonar.h"

using namespace std;

// Give names to LED pins
#define RED_LEDs 10
#define GREEN_LEDs 11

// Give names to Drive and Direction pins
#define RightDrive 15
#define RightDirection 16
#define LeftDrive 26
#define LeftDirection 31

// Give names to Sonar pins
#define trigger 22
#define echo 23


int setup()
{
    wiringPiSetup();

    // Setup pins as outputs
    pinMode(RED_LEDs, OUTPUT);
    pinMode(GREEN_LEDs, OUTPUT);
    pinMode(RightDrive, OUTPUT);
    pinMode(RightDirection, OUTPUT);
    pinMode(LeftDrive, OUTPUT);
    pinMode(LeftDirection, OUTPUT);

    // Set initial values for drive pins
    softPwmCreate(RightDrive, 0, 100);
    digitalWrite(RightDirection, 1);
    softPwmCreate(LeftDrive, 0, 100);
    digitalWrite(LeftDirection, 1);
return 0;
}


int motorKill() // Only to be used at the end as it will
{               // cleanup the motor pins
    softPwmStop(RightDrive);
    softPwmStop(LeftDrive);
return 0;
}


int allStop()
{
    digitalWrite(GREEN_LEDs, 0);
    digitalWrite(RED_LEDs, 0);
    softPwmWrite(RightDrive, 0);
    softPwmWrite(LeftDrive, 0);
return 0;
}


int forwardDrive(int Lspeed, int Rspeed, int t)
{
    digitalWrite(GREEN_LEDs, 1);
    digitalWrite(RED_LEDs, 1);
    digitalWrite(RightDirection, 1);
    digitalWrite(LeftDirection, 1);
    softPwmWrite(RightDrive, Rspeed);
    softPwmWrite(LeftDrive, Lspeed);
    delay(t*1000);
    allStop();
return 0;
}


int spinLeft(int t)
{
    digitalWrite(GREEN_LEDs, 1);
    digitalWrite(RED_LEDs, 1);
    digitalWrite(RightDirection, 1);
    digitalWrite(LeftDirection, 0);
    softPwmWrite(RightDrive, 40);
    softPwmWrite(LeftDrive, 45);
    delay(t*1000);
    allStop();
return 0;
}


int spinRight(int t)
{
    digitalWrite(GREEN_LEDs, 1);
    digitalWrite(RED_LEDs, 1);
    digitalWrite(RightDirection, 0);
    digitalWrite(LeftDirection, 1);
    softPwmWrite(RightDrive, 40);
    softPwmWrite(LeftDrive, 45);
    delay(t*1000);
    allStop();
return 0;
}


int reverseDrive(int Lspeed, int Rspeed, int t)
{
    digitalWrite(GREEN_LEDs, 1);
    digitalWrite(RED_LEDs, 1);
    digitalWrite(RightDirection, 0);
    digitalWrite(LeftDirection, 0);
    softPwmWrite(RightDrive, Rspeed);
    softPwmWrite(LeftDrive, Lspeed);
    delay(t*1000);
    allStop();
return 0;
}


int getRange()
{
    // Initiallize sonar
    Sonar sonar;
    sonar.init(trigger,echo);

    // Print the read distance
    cout << "Distance is: " << sonar.distance(30000) << " cm." << endl;
return 0;
}


// This is where the main code resides
int main()
{
    setup();  // Leave this here otherwise we will have some errors

    // This is the section that is meant to be changed...
    forwardDrive(45, 40, 4);
    spinLeft(2);
    spinRight(2);
    reverseDrive(45, 40, 3);
    getRange();

    // This line is needed at the end; otherwise the robot sometimes runs away.
    motorKill(); // Only use as your final instruction
return 0;
}

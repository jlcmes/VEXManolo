#pragma config(Motor,  port2,           leftMotor,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           rightMotor,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           chain,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           claw,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           upMotor,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           downMotor,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           gearbox,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          pusher,        tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//CONSTANTS FOR MOVEMENT MANAGEMENT
// Controller 1/2, Stick L/R, Axis X/Y
#define C1LX vexRT[Ch4]
#define C1LY vexRT[Ch3]
#define C1RX vexRT[Ch1]
//#define FL upMotor
//#define FR rightMotor
//#define BL leftMotor
//#define BR downMotor

#define FR upMotor
#define BR rightMotor
#define FL leftMotor
#define BL downMotor

#define SPEED_MOTORS 60
#define SUPER_SPEED_MOTORS 127

//CONSTANTS FOR AUTONOMOUS MODE
int AUTO_FORWARD_DISTANCE = 1491;
int AUTO_RIGHT_TIME = 3200; //TODO: Adjust values on a real game field


task goForward()
{
  // ..........................................................................
	startMotor(leftMotor, SPEED_MOTORS);
  startMotor(rightMotor, -SPEED_MOTORS);
}

task goBackwards()
{
  // ..........................................................................
	startMotor(leftMotor, -SPEED_MOTORS);
  startMotor(rightMotor, SPEED_MOTORS);
}


task main() //usercontrol
{
  // User control code here, inside the loop

  while (true)
  {
		// SOURCE CODE: https://www.vexforum.com/index.php/12370-holonomic-drives-2-0-a-video-tutorial-by-cody/0

		// MOVEMENT
		// Y component, X component, Rotation
		motor[FL] = -C1LY - C1LX - C1RX;
		motor[FR] =  C1LY - C1LX - C1RX;
		motor[BR] =  C1LY + C1LX - C1RX;
		motor[BL] = -C1LY + C1LX - C1RX;


		// INTAKE
		if (vexRT[Btn6U] == 1)
			motor[claw] = -SPEED_MOTORS-40;//20
		else if (vexRT[Btn6D] == 1)
			motor[claw] = SPEED_MOTORS+40;//20
		else
			motor[claw] = 0;

		// LIFT
		if (vexRT[Btn5U] == 1)
			motor[gearbox] = SUPER_SPEED_MOTORS; //SPEED_MOTORS+20;
		else if (vexRT[Btn5D] == 1)
			motor[gearbox] = -SUPER_SPEED_MOTORS; //-SPEED_MOTORS;
		else
			motor[gearbox] = 0;

		// DEPLOY SYSTEM
		if (vexRT[Btn8U] == 1)
			motor[chain] = SUPER_SPEED_MOTORS; //SPEED_MOTORS+60;//40
		else if (vexRT[Btn8D] == 1)
			motor[chain] = -SUPER_SPEED_MOTORS; //-SPEED_MOTORS-60;//-40
		else
			motor[chain] = 0;

		// TEST AUTONOMOUS MODE
		//if (vexRT[Btn7L] == 1)
		//	startTask(autonomous);

		// TEST BUTTON
		if (vexRT[Btn7R] == 1)
	{
	startMotor(upMotor, SPEED_MOTORS);
	startMotor(downMotor, -SPEED_MOTORS);
	}

		// GO FORWARD AND BACKWARDS
		if (vexRT[Btn7U] == 1)
			startTask(goForward);
		else if (vexRT[Btn7D] == 1)
			startTask(goBackwards);
		else
		{
			stopMotor(leftMotor);
			stopMotor(rightMotor);
		}

		// Motor values can only be updated every 20ms
		wait1Msec(20);
  }
}

#ifndef SHS2605_AUTONOMOUSBEHAVIOR_H
#define SHS2605_AUTONOMOUSBEHAVIOR_H

#include <Behaviors/IBehavior.h>
#include <Actions/ActionController.h>

#include <Hardware/Drive/MecanumDriveTrain.h>

#include <Sensing/IAngularInput.h>

#include "AutonomousActions/TurnAction.h"
#include "AutonomousActions/DriveAction.h"
#include "AutonomousActions/WinchPositionAction.h"

#define AUTOBEHAVIOR_BID "autonomous"

class AutonomousBehavior : public IBehavior
{
public:
	
	AutonomousBehavior ( MecanumDriveTrain * Drive, LinearSlide * Winch, IAngularInput * RobotYaw );
	~AutonomousBehavior ();
	
	void Init ( BehaviorController * Controller, const char * AppliedID );
	void Destroy ();
	
	void Start ();
	void Stop ();
	
	void Update ();
	
	static const char * GetDefaultBehaviorID ();
	
private:
	
	MecanumDriveTrain * Drive;
	LinearSlide * Winch;
	
	DriveAction Drive1;
	WinchPositionAction WinchPos1;
	TurnAction Turn1;
	DriveAction Drive2;
	WinchPositionAction WinchPos2;
	
	ActionController Actions;
	
};

#endif

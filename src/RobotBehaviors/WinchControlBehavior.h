#ifndef SHS2605_WINCHCONTROLBEHAVIOR_H
#define SHS2605_WINCHCONTROLBEHAVIOR_H

#include <Behaviors/IBehavior.h>
#include <Behaviors/BehaviorController.h>

#include <Hardware/Drive/LinearSlide.h>

#include <Sensing/IBooleanInput.h>

#include <Indication/IBooleanIndicator.h>
#include <Indication/BooleanIndicatorBlinker.h>

#include <Util/Vector.h>

#define WinchControlBEHAVIOR_BID "winch_control"

class WinchControlBehavior : public IBehavior
{
public:
	
	typedef struct PositionTargetButton_Struct
	{
		
		PositionTargetButton_Struct ( IBooleanInput * Button, IBooleanIndicator * Indicator, double SetPoint );
		~PositionTargetButton_Struct ();
		
		IBooleanInput * Button;
		IBooleanIndicator * Indicator;
		
		double SetPoint;
		
	} PositionTargetButton;
	
	WinchControlBehavior ( LinearSlide * Winch, LinearSlide * Ballast, IBooleanInput * UpButton, IBooleanInput * DownButton, double JogSpeed );
	~WinchControlBehavior ();
	
	void Init ( BehaviorController * Controller, const char * AppliedID );
	void Destroy ();
	
	void Start ();
	void Stop ();
	
	void Update ();
	
	void AddWinchPositionTargetButton ( PositionTargetButton * Target );
	void RemoveWinchPositionTargetButton ( PositionTargetButton * Target );
	
	void AddBallastPositionTargetButton ( PositionTargetButton * Target );
	void RemoveBallastPositionTargetButton ( PositionTargetButton * Target );
	
	static const char * GetDefaultBehaviorID ();
	
private:
	
	LinearSlide * Winch;
	LinearSlide * Ballast;
	
	IBooleanInput * UpButton;
	IBooleanInput * DownButton;
	
	Vector <PositionTargetButton *> WinchPositionTargets;
	Vector <PositionTargetButton *> BallastPositionTargets;
	
	double JogSpeed;
	
	bool Targeting;
	
	BooleanIndicatorBlinker Blinker;
	
};

#endif

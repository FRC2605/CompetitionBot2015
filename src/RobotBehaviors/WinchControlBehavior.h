#ifndef SHS2605_WINCHCONTROLBEHAVIOR_H
#define SHS2605_WINCHCONTROLBEHAVIOR_H

#include <Behaviors/IBehavior.h>
#include <Behaviors/BehaviorController.h>

#include <Hardware/Drive/LinearSlide.h>

#include <Sensing/IBooleanInput.h>

#include <Util/Vector.h>

#define WinchControlBEHAVIOR_BID "winch_control"

class WinchControlBehavior : public IBehavior
{
public:
	
	typedef struct
	{
		
		IBooleanInput * Button;
		
		double SetPoint;
		
	} PositionTargetButton;
	
	WinchControlBehavior ( LinearSlide * Winch, IBooleanInput * UpButton, IBooleanInput * DownButton, double JogSpeed );
	~WinchControlBehavior ();
	
	void Init ( BehaviorController * Controller, const char * AppliedID );
	void Destroy ();
	
	void Start ();
	void Stop ();
	
	void Update ();
	
	void AddPositionTargetButton ( PositionTargetButton * Target );
	void RemovePositionTargetButton ( PositionTargetButton * Target );
	
	static const char * GetDefaultBehaviorID ();
	
private:
	
	LinearSlide * Winch;
	
	IBooleanInput * UpButton;
	IBooleanInput * DownButton;
	
	Vector <PositionTargetButton *> PositionTargets;
	
	double JogSpeed;
	
	bool Targeting;
	
};

#endif

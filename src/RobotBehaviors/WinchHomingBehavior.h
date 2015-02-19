#ifndef SHS2605_WINCHHOMINGBEHAVIOR_H
#define SHS2605_WINCHHOMINGBEHAVIOR_H

#include <Hardware/Drive/LinearSlide.h>
#include <Behaviors/IBehavior.h>
#include <Behaviors/BehaviorController.h>

#define WINCHHOMINGBEHAVIOR_BID "winch_homing"

class WinchHomingBehavior : public IBehavior
{
public:
	
	WinchHomingBehavior ( LinearSlide * Winch, LinearSlide * Ballast, const char * WinchControlBehaviorID, bool StartWinchControl );
	~WinchHomingBehavior ();
	
	void Init ( BehaviorController * Controller, const char * AppliedID );
	void Destroy ();
	
	void Start ();
	void Stop ();
	
	void Update ();
	
	void ResetHomed ();
	void SetStartWinchControl ( bool DoStart );
	
	static const char * GetDefaultBehaviorID ();
	
private:
	
	LinearSlide * Winch;
	LinearSlide * Ballast;
	
	bool Homed;
	
	BehaviorController * Controller;
	const char * AppliedID;
	
	const char * WinchControlID;
	
	bool StartWinchControl;
	
};

#endif

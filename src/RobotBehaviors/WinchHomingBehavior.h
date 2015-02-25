#ifndef SHS2605_WINCHHOMINGBEHAVIOR_H
#define SHS2605_WINCHHOMINGBEHAVIOR_H

#include <Hardware/Drive/LinearSlide.h>
#include <Behaviors/IBehavior.h>
#include <Behaviors/BehaviorController.h>

#define WINCHHOMINGBEHAVIOR_BID "winch_homing"

class WinchHomingBehavior : public IBehavior
{
public:
	
	WinchHomingBehavior ( LinearSlide * Winch, LinearSlide * Ballast );
	~WinchHomingBehavior ();
	
	void Init ( BehaviorController * Controller, const char * AppliedID );
	void Destroy ();
	
	void Start ();
	void Stop ();
	
	void Update ();
	
	void ResetHomed ();
	
	static const char * GetDefaultBehaviorID ();
	
private:
	
	LinearSlide * Winch;
	LinearSlide * Ballast;
	
	bool Homed;
	
	BehaviorController * Controller;
	const char * AppliedID;
	
};

#endif

#ifndef SHS2605_WINCHHOMINGBEHAVIOR_H
#define SHS2605_WINCHHOMINGBEHAVIOR_H

#include <Behaviors/IBehavior.h>

#include <Hardware/Drive/LinearSlide.h>

#define WINCHHOMINGBEHAVIOR_BID "winch_homing"

class WinchHomingBehavior : public IBehavior
{
public:
	
	WinchHomingBehavior ( LinearSlide * Winch );
	~WinchHomingBehavior ();
	
	void Init ();
	void Destroy ();
	
	void Start ();
	void Stop ();
	
	void Update ();
	
	static const char * GetDefaultBehaviorID ();
	
private:
	
	LinearSlide * Winch;
	
};

#endif

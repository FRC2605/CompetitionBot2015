#ifndef LARUL_WAITACTION_H
#define LARUL_WAITACTION_H

#include <Actions/IAction.h>
#include <Timing/IntervalTimer.h>

class WaitAction : public IAction
{
public:
	
	WaitAction ( double Delay );
	~WaitAction ();
	
	void Reset ();
		
	void Start ();
	bool IsComplete ();
	void Stop ();
		
	void Update ();

private:
	
	double Wait;
	
	IntervalTimer Timer;
	
};

#endif

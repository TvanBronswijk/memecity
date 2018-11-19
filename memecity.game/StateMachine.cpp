#include "StateMachine.h"

void StateMachine::start()
{
	while (true)
	{
		switch (state)
		{
		case starting: 
			//_gamemanager.run();
			state = running;
			break;
		case running: break;
		case paused: break;
		case menu: break;
		default: ;
		}
	}
}

#include "features/bhop.h"
#include "util/vfunc_macros.h"
#include "tf2/enums.h"
#include "globals.h"
#include "netvars.h"

void bhop(CUserCmd* pCommand)
{
	void* local_player = GET_LOCAL_PLAYER();

	static bool should_jump = false;
	static bool jump_released;
	unsigned int* m_fFlags = get_netvar(local_player, "CTFPlayer.m_fFlags"); // A member variable of player entities. It can tell us whether the player is on the ground.

	if (pCommand->tick_count != 0) // If the game tick is new:
	{
		if (pCommand->buttons & IN_JUMP)
		{
			if (!jump_released)
			{
				if (*m_fFlags & FL_ONGROUND)
				{
					should_jump = true;
				}
				else should_jump = false;
			}
			else
			{
				should_jump = true; 
			}
			jump_released = false;
		}
		else
		{
			should_jump = false;
			jump_released = true;
		}
	}

	if (should_jump)
	{
		pCommand->buttons |= IN_JUMP;
	}
	else
	{
		pCommand->buttons &= ~IN_JUMP;
	}
	return;
}


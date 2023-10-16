/*
 Visual Studio project config:
 Compile as C
 Set target to DLL
 Add include directories: 'include', 'include/util'
 Set build to 'Release' and 'x86'
 Disable warnings: C6387
*/

/*
 Checklist for adding features:

  1. Look on Google and UC and work out what to do.
  2. Add relevant class headers to include/tf2/classes. This will involve finding function signatures and vfunc indexes.
  3. (If needed) add interface pointers to globals.h and globals.c.
  4. Create a module in src/hooks and include/hooks for the class whose vtable you will be hooking. Write the hook function which will handle a certain cheat feature (e.g. the CreateMove hook runs the b-hop).
  5. Add the hooks to init_hooks() and release_hooks() in hooks.c.

A b-hop is already implemented. Try implementing chams next.
*/


#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "hooks.h"
#include "globals.h"
#include "netvars.h"
#include "features/chams/chams_data.h"

BOOL WINAPI main_thread(LPVOID* hinstDLL)
{
	init_interfaces();
	init_func_ptrs();
	init_netvar_offsets();
	init_chams_mats();
	init_hooks(); 

	PRINTF("INJECTED\n");

	while (!(GetAsyncKeyState(VK_DELETE) & 0x8000)) // Check if uninject key is pressed.
		Sleep(50);									

	PRINTF("UNINJECTING\n");

	release_hooks();
	free_chams_mats();
	free_netvar_offsets();

	// If you allocate any resources that the game can access, you need to free them here.
	// Otherwise the game will try to access them and crash because the memory will become out of bounds when you unload the DLL.

	FreeLibraryAndExitThread((HMODULE)hinstDLL, 0);
	return TRUE;
}


// The entry point. Only serves to create a new thread running the above function.
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		HANDLE hMain;
		if (hMain = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&main_thread, hinstDLL, 0, NULL)) CloseHandle(hMain);
		break;
	default:
		break;
	}
	return TRUE;
}
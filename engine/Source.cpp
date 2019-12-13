#include "core.h"

int main() 
{
	core::Startup();
	while (running)
	{
		core::Update();
	}
	core::Shutdown();
	return 0;
}
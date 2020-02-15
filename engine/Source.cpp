#include "TESTSAMPLEFILE.h"

int main() {
	Game::Startup();

	while (running)
		Game::Update();

	Game::Shutdown();
	return 0;
}

#include <ARK2D/Core/GameContainer.h>
#include <ARK2D/Tests/GamepadsTest.h>
#include <ARK2D/Tests/ShaderTest.h>
#include "DefaultGame.h"

int main(int argc, char** argv) {

	//ARK2D::getLog()->setFilter(ARK::Core::Log::TYPE_INFORMATION);
	//ARK2D::getLog()->setFilter(ARK::Core::Log::TYPE_VERBOSE);
	//ARK::Tests::NetTest::start();
	//ARK::Tests::GamepadsTest::start();
	//ARK::Tests::ShaderTest::start();
	//return 0;

	DefaultGame* game = new DefaultGame("The Butterfly Effect");
	//GameContainer* container = new GameContainer(*game, 120, 80, 32, false);
	GameContainer* container = new GameContainer(*game, 140, 100, 32, false);
	container->setShowingFPS(false);
	container->setClearColor(Color::black);
	container->setIcon("data/icon.ico");
	container->setCursorVisible(true);
	container->start();

	return 0;
}


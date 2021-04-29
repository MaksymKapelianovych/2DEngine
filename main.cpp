#include <iostream>
#include <Components/location.h>

#include "Engine/Engine.h"
#include "Engine/game_object.h"
#include "Map.h"
#include "Engine/window.h"

int levelWidthCount = 19;
int levelHeightCount = 22;
std::string level1 = "                   "
					"                   "
					"                   "
					"                   "
					"                   "
					"                   "
	 			    "                   "
	 			    "                   "
	 			    "                   "
	 			    "                   "
	 			    "                   "
	 			    "                   "
	 			    "                   "
	 			    "                   "
	 			    "                   "
	 			    "   pb              "
	 			    "                   "
	 			    "                   "
					"                   "
					"                   "
					"                   "
					"                   ";

std::string level = "bbbbbbbbbbbbbbbbbbb"
					"b       tbt       b"
					"b bbgbbbtbtbbb bb b"
					"btbb bbbtbtbbb bb b"
					"b                 b"
					"b bb b bbbbb b bb b"
					"b    b   b  tb    b"
					"bbbb bbb b bbb bbbb"
					"   b b   b  tb b   "
					"bbbb b bbbbbtb bbbb"
					"b   p tb   bt     b"
					"bbbb btbbbbbtb bbbb"
					"   b bttt   tb b   "
					"bbbb btbbbbbtb bbbb"
					"bt       b        b"
					"b bb bbb btbbb bb b"
					"b  b           b  b"
					"bbtb btbbbbb b b bb"
					"bt   b   b   b    b"
					"b bbbbbb b bbbbbb b"
					"b   t         t   b"
					"bbbbbbbbbbbbbbbbbbb";

int main() {
	std::cout << " starting\n";
	Engine::createWindow<Window>(800, 800, "GL Engine");
	Engine::init();
	//loadLevel(Engine::getWindow().lock());
	auto map = GameObject::create(std::weak_ptr<GameObject>(), glm::vec2{0.f, 0.f});
	Engine::getWindow()->addToScene(map);

	auto m = map->addComponent<Map>();
	m->loadMap(level, levelWidthCount, levelHeightCount);


    Engine::run();

    return 0;
}
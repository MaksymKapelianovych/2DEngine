#include <iostream>

#include "Engine/Engine.h"
#include "Gui/game_object.h"
#include "Components/location.h"
#include "Components/image.h"
#include "Gui/window.h"

int levelWidthCount = 15;
int levelHeightCount = 15;
//std::string level = "wwwwwwwwwwwwwww"
//					"wx  b  x  b  xw"
//					"wbb b b b b bbw"
//					"w b b b b b b w"
//					"w b b bsb b b w"
//					"w b b b b b b w"
//					"w b b     b b w"
//					"w     b b     w"
//					"ws bb     bb sw"
//					"w     bbb     w"
//					"w b b b b b b w"
//					"w b b     b b w"
//					"w b b bbb b b w"
//					"w    pbhb     w"
//					"wwwwwwwwwwwwwww";

std::string level = "wwwwwwwwwwwwwww"
					"wb           bw"
					"w             w"
					"w             w"
					"w             w"
					"w             w"
					"w             w"
					"w             w"
					"w             w"
					"w             w"
					"w             w"
					"w             w"
					"w             w"
					"w             w"
					"wwwwwwwwwwwwwww";

void loadLevel(std::shared_ptr<Window> window){
	int slideX, slideY, screenW = 800, screenH = 800, wallW = 40, wallH = 40;
	auto object = std::make_shared<GameObject>(nullptr);
	auto q = object->addComponent<Location>();
	if (auto s = object->addComponent<Image>())
	{
		s->setTexture("../resources/textures/brick.png");
		wallW = s->getWidth();
		wallH = s->getHeight();
	}

	slideX = (- levelWidthCount * wallW) / 2;
	slideY = (- levelHeightCount * wallH) / 2;

	//levelWidth = wallW * levelWidthCount;
	//levelHeight = wallH * levelHeightCount;

	for(int row = 0; row < levelHeightCount; ++row){
		for(int column = 0; column < levelWidthCount; ++column){
			switch (level[row * levelWidthCount + column])
			{
			case 'b':
			{
				auto object = std::make_shared<GameObject>(nullptr);
				auto q = object->addComponent<Location>();
				q->setPosition({slideX + wallW * column + wallW / 2, slideY + wallH * row + wallH / 2});
				if (auto s = object->addComponent<Image>())
				{
					s->setTexture("../resources/textures/brick.png");
				}
				window->addToScene(object);
			}
				break;
			default:
				break;
			}
		}
	}
}

int main() {
	std::cout << " starting\n";
    Engine::init();
	loadLevel(Engine::getWindow().lock());
//    auto window = Engine::getWindow().lock();
//	auto object = std::make_shared<GameObject>(nullptr);
//	auto q = object->addComponent<Location>();
//	if(auto s = object->addComponent<Image>()){
//		s->setTexture("../resources/textures/brick.png");
//	}
//
////	auto s = object->addComponent<Sprite>();
////	s->SetWidth(10);
////	s->SetHeight(10);
////	s->SetColor({1.f, 0.5f, 0.3f});
//
//	window->addToScene(object);


    Engine::run();

    return 0;
}
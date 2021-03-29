#include <SFML/Graphics.hpp>
#include <vector>
#include <list>

#include "../storage/storage.h"
#include "../food/food.h"
#include "../player/player.h"

class Engine
{
public:
	Engine();
	~Engine();
	void run();
private:
	void LoadAssets();
	Storage storage;
	Player pikachu;
	Food food;
	const std::vector<std::string_view>
		  filenames = { "background","pikachu","food" };
	std::map<std::string_view, sf::Sprite> sprites;

	std::vector<sf::Sprite*> spritesEntity;
	std::vector<sf::Sprite>* spritesFood;

	std::map<std::string_view, sf::Texture> textures;

	std::map<std::string_view, std::tuple<int, int, int, int>>
	spitesRectangle = { {"pikachu",{0,80,160,155}},
						{"mushroom",{0,0,50,45}},
						{"food",{0,55,50,45}},
						{"background",{0,0,960,720}}
	};




};

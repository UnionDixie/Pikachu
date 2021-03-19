#include "storage.h"


Storage::Storage()
{
	//Init
}

Storage::Storage(std::string_view pathToDirectory) : Storage()
{
	directory = pathToDirectory;
}

Storage::~Storage()
{
}

std::unique_ptr<sf::Texture> Storage::getTexture(const std::string_view filename)
{
	if (textures[filename] != nullptr) {
		//return std::make_unique<sf::Texture>(textures[filename]);
	}
	
	//std::unique_ptr<sf::Texture> texture(new sf::Texture);

	//std::string path{ directory }, name{ filename };
	//if (!texture->loadFromFile(path + name + ".png")) //||!texture->loadFromFile(path + name + ".jpg")) 
	//{
	//	sf::Image image;
	//	image.create(50u, 50u, sf::Color::Red);
	//	//assert(*texture == nullptr && "nullptr");
	//	texture->loadFromImage(image);
	//}
	//else {
	//	sf::Image img(texture->copyToImage());
	//	img.createMaskFromColor(sf::Color::White);
	//	texture->loadFromImage(img);
	//	//name += "flip";
	//	//img.flipHorizontally();
	//	//textures[name].get()->loadFromImage(img);
	//}
	//textures.emplace(name, texture.get());
	//if (textures[filename] == nullptr)
		//std::make_unique<sf::Texture>(nullptr);
	//return std::make_unique<sf::Texture>(textures[filename]);
	return nullptr;
	//return std::unique_ptr<sf::Texture>();
}

bool Storage::removeTexture(const std::string_view filename)
{
	if (textures[filename] != nullptr)
	{
		textures.erase(filename);
		return true;
	}
	return false;
}

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <optional>
#include <string_view>
#include <string>
#include <filesystem>
#include <memory>
#include <cassert>

class Storage
{
public:
	Storage();
	Storage(std::string_view);// "../../data/"
	~Storage();
	std::unique_ptr<sf::Texture> getTexture(const std::string_view);
	bool removeTexture(const std::string_view);
private:
	std::unordered_map<std::string_view, std::unique_ptr<sf::Texture>> textures;
	std::string_view directory = "../../data/";
};

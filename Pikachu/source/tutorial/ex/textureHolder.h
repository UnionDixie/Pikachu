#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <cassert>
#include <optional>
#include <exception>

class TextureHolder
{
public:
	TextureHolder();
	void load(const std::string& name);
	std::optional<std::reference_wrapper<const sf::Texture>> get(const std::string&) const;
	~TextureHolder();

private:
	std::map<std::string, std::unique_ptr<sf::Texture>> textureMap;
};


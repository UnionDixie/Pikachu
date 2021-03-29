#include "textureHolder.h"

TextureHolder::TextureHolder()
{
}

void TextureHolder::load(const std::string& name)
{
	std::unique_ptr<sf::Texture> texture(new sf::Texture());
	if (!texture->loadFromFile("data/" + name + ".png")) {
		assert(0 && "error load");
		/*throw std::runtime_error("TextureHolder::load - Failed to load "
			+ name);*/
	}
	auto&& ok = textureMap.try_emplace(name, std::move(texture)).second;
	if (!ok) {//condt and action
		throw std::logic_error("Error try_emplace");
	}
}

std::optional<std::reference_wrapper<const sf::Texture>> TextureHolder::get(const std::string& name) const
{
	if (auto&& found = textureMap.find(name); found != textureMap.end()) {
		return { *found->second };
	}
	return std::nullopt;
}

TextureHolder::~TextureHolder()
{
}
#include <SFML/Graphics.hpp>
#include <map>
#include <functional>
#include <SFML/Audio.hpp>
#include <iostream>

class Player
{
public:
	Player();
	Player(sf::Texture,sf::IntRect);
	Player(sf::Sprite, sf::IntRect);
	void set(sf::Texture, sf::IntRect);
	void update(std::pair<int, int>,std::string);
	sf::Sprite* drawS();
	const std::pair<sf::Sprite, std::pair<int, bool>>& get() const;
	~Player();
private:
	sf::Texture texture;
	sf::IntRect rect;
	sf::Sprite sprite;
	sf::Vector2f pos;
	std::pair<int, bool> info;
	int foods;
	std::map<std::string, std::function<void()>> events;

	sf::SoundBuffer buffer;
	sf::Sound sound;

};

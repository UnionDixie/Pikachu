#include "Engine.h"

Engine::Engine() : storage("data/")//../../data/
{
	//for (const auto& name : filenames) {
	//	if (auto texture = storage.getTexture(name).get(); texture != nullptr) {
	//		auto& [x, y, w, h] = spitesRectangle[name];
	//		sf::IntRect rect(x,y,w,h);
	//		sprites.try_emplace(name,*texture,rect);//!!!
	//		if (name == filenames.front()) {//addedflip pikachu
	//			std::string flip{ name };
	//			flip += "flip";
	//			sprites.try_emplace(flip, *texture, rect);
	//		}
	//	}
	//}	
    for (const auto& name : filenames) {
        sf::Texture tmp;
        std::string str{ name };
        tmp.loadFromFile("data/" + str + ".png");
        auto& it = spitesRectangle[name];
        if (str == "food") {
            it = spitesRectangle["mushroom"];
        }
        //sf::Image img(tmp.copyToImage());
        //img.createMaskFromColor(sf::Color::White);
        //tmp.loadFromImage(img);

        textures[name] = tmp;
        sprites[name].setTexture(textures[name]);
        auto& [x, y, w, h] = it;
        sprites[name].setTextureRect(sf::IntRect(x, y, w, h));
        sprites2.push_back(sprites[name]);
    }
    //sprites.begin()->second.setPosition(180, 180);
}

Engine::~Engine()
{
}

void Engine::run()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        //window.draw(shape);
        for (const auto& v : sprites2)
            window.draw(v);
        window.display();
    }
}

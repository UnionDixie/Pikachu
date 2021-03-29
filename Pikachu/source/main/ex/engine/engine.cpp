#include "Engine.h"

Engine::Engine() : storage("data/")//../../data/
{
    LoadAssets();
}

void Engine::LoadAssets()
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
        //auto& it = spitesRectangle[name];
        /*if (str == "food") {
            it = spitesRectangle["mushroom"];
        }*/
        //sf::Image img(tmp.copyToImage());
        //img.createMaskFromColor(sf::Color::White);
        //tmp.loadFromImage(img);
        textures.try_emplace(name, tmp);
        //textures[name] = tmp;
        if (str == "background") {
            auto& [x, y, w, h] = spitesRectangle[name];
            sf::Sprite t(textures[name], sf::IntRect(x, y, w, h));
            sprites.try_emplace(name, t);
            //sprites[name].setTexture(textures[name]);

            //sprites[name].setTextureRect();
            spritesEntity.push_back(&sprites[name]);
        }
    }
    {
        auto pikachuName = "pikachu";
        auto [x, y, w, h] = spitesRectangle[pikachuName];
        pikachu.set(textures[pikachuName], sf::IntRect(x, y, w, h));
        //auto t = const_cast<sf::Sprite*> (&pikachu.get().first);

        spritesEntity.push_back(&*pikachu.drawS());
    }
    {
        auto foodName = "food";
        auto [x, y, w, h] = spitesRectangle[foodName];
        food.set(textures[foodName], sf::IntRect(x, y, w, h));
        spritesFood = food.getFood();
    }
}



void Engine::run()
{
    sf::RenderWindow window(sf::VideoMode(960, 720), "SFML works!");//,sf::Style::Fullscreen
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    bool jump = false, gr = false;
    int cnt = 0;
    int dist = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
          /*  if (event.type == sf::Event::Closed)
                window.close();*/
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                pikachu.update({ -8,0 }, "move");
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                pikachu.update({ 8,0 }, "move");
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !jump) {
                jump = true;
                //pikachu.update({ 0,-25 }, "move");
            }
        }
        food.update(1);
        if (jump) {
            if (cnt < 50 && !gr) {
                cnt++;
                dist = 5 * cnt;
                pikachu.update({ 0,-5 }, "move");
            }
            else {
                gr = true;
                //cnt--;
                dist--;
               pikachu.update({ 0, 1 }, "move");
                if (dist <= 0) {
                    jump = false;
                    gr = false;
                    cnt = 0;
                    dist = 0;
                }
                
            }
            
        }

        window.clear();
        //window.draw(shape);
        for (const auto& it : spritesEntity) {
            
            if (it != nullptr) {
                //assert(it == nullptr && "Error");
                window.draw(*it);
            }
        }
        for (const auto& it : *spritesFood) {
            if (it.getGlobalBounds().intersects(spritesEntity[1]->getGlobalBounds())) {
                pikachu.update({ 0,0 }, "food");
                std::cout << pikachu.get().second.first << "\n";
            }
            else {
                window.draw(it);
            }
        }
        window.display();
    }
}



Engine::~Engine()
{
}
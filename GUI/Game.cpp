//
// Created by Samuel on 16/11/2023.
//

#include "Game.h"

Game::Game(const int &wd, const int &hg) {
    width = wd;
    height = hg;
    observer = new Observer();
    world = observer->getWorld();

    assert(this->getHeight() % world->getHeight() == 0);
    assert(this->getWidth() % world->getWidth() == 0);

    pixelHeight = int(this->getHeight() / world->getHeight());
    pixelWidth = int(this->getWidth() / world->getWidth());

    sf::RenderWindow window(sf::VideoMode(this->getWidth(), this->getHeight()), "My window");

    sf::RectangleShape rectangle1(sf::Vector2f(50, 50));
    rectangle1.setPosition(50, 50);
    rectangle1.setFillColor(sf::Color::Green);
    window.draw(rectangle1);

    sf::RectangleShape rectangle2(sf::Vector2f(50, 50));
    rectangle2.setFillColor(sf::Color::Red);
    window.draw(rectangle2);

    while (window.isOpen()){
        sf::Event event{};
        while(window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }
        window.clear();
        window.draw(rectangle1);
        window.draw(rectangle2);
        window.display();
    }
}

int Game::getWidth() const {
    return width;
}

void Game::setWidth(int wd) {
    Game::width = wd;
}

int Game::getHeight() const {
    return height;
}

void Game::setHeight(int hg) {
    Game::height = hg;
}

pair<int, int> Game::calculatePixel(const int &row, const int &column) {
    int wd = row * pixelWidth;
    int hg = column * pixelHeight;
    return make_pair(wd, hg);
}

World *Game::getWorld() const {
    return world;
}

void Game::setWorld(World *world) {
    Game::world = world;
}

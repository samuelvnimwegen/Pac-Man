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

    factory = new ConcreteFactory(observer, world);

    this->generateMap();

    sf::RenderWindow window(sf::VideoMode(this->getWidth(), this->getHeight()), "Pac-Man");

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
        for (int r = 0; r < this->getWorld()->getHeight(); ++r){
            for (int k = 0; k < this->getWorld()->getWidth(); ++k){
                if (viewMap[r][k] != nullptr){
                    auto name = viewMap[r][k]->getSpriteFileName();
                    auto pos = this->calculatePixel(r, k);
                    sf::Texture texture;
                    texture.loadFromFile(name);
                    sf::Sprite sprite(texture);
                    sprite.setPosition(float(pos.first), float(pos.second));
                    window.draw(sprite);
                }
            }
        }
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

pair<int, int> Game::calculatePixel(const int &row, const int &column) const {
    int wd = column * pixelWidth;
    int hg = row * pixelHeight;
    return make_pair(wd, hg);
}

World *Game::getWorld() const {
    return world;
}

void Game::setWorld(World *world) {
    Game::world = world;
}

vector<sf::Sprite> Game::collectSprites() {
    vector<sf::Sprite> sprites;

    return sprites;
}

void Game::generateMap() {
    for (int i = 0; i < this->getWorld()->getHeight(); ++i){
        for (int j = 0; j < this->getWorld()->getWidth(); ++j){
            // Als het een muur is deze plaatsen.
            if (this->getWorld()->getItem(i, j) == nullptr){
                this->viewMap[i][j] = nullptr;
            }
            else if (this->getWorld()->getItem(i, j)->getTag() == "Wall"){
                this->viewMap[i][j] = factory->makeViewEntity(i, j, "Wall");
            }
        }
    }
}
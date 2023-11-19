//
// Created by Samuel on 16/11/2023.
//

#include "Game.h"

Game::Game(const int &wd, const int &hg) {
    width = wd;
    height = hg;
    stopwatch = new Stopwatch();

    world = new World();
    this->generateMap();
    factory = new ConcreteFactory(world, this);
    this->getWorld()->setFactory(factory);
    world->buildWorld();

    assert(this->getHeight() % world->getHeight() == 0);
    assert(this->getWidth() % world->getWidth() == 0);


    sf::RenderWindow window(sf::VideoMode(this->getWidth(), this->getHeight()), "Pac-Man");

    while (window.isOpen()){
        sf::Event event{};
        while(window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }
        int steps = stopwatch->getSteps();
        string direction = getDirection();
        this->getWorld()->getPacMan()->setCurrentDirection(direction);
        this->getWorld()->getPacMan()->move(steps);
        window.clear();
        for (int r = 0; r < this->getWorld()->getHeight(); ++r){
            for (int k = 0; k < this->getWorld()->getWidth(); ++k){
                auto viewEntity = viewMap[r][k];
                if (viewEntity != nullptr){
                    auto pos = this->cameraToPixels(viewEntity->getSubject()->getCameraX(), viewEntity->getSubject()->getCameraY());
                    sf::Sprite sprite = viewEntity->getSprite();
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



World *Game::getWorld() const {
    return world;
}

void Game::setWorld(World *sWorld) {
    Game::world = sWorld;
}



void Game::generateMap() {
    for (int i = 0; i < this->getWorld()->getHeight(); ++i){
        for (int j = 0; j < this->getWorld()->getWidth(); ++j){
            this->viewMap[i][j] = nullptr;
        }
    }
}

void Game::setViewItem(EntityView *entity, const int &row, const int &col) {
    viewMap[row][col] = entity;
    viewEntities.push_back(entity);
}

Game::~Game() {
    int entitySize = int(this->viewEntities.size());
    for (int i = 0; i < entitySize; ++i){
        delete viewEntities[i];
    }
    delete factory;
    delete world;

}

string Game::getDirection() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
        return "UP";
    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
        return "LEFT";
    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        return "RIGHT";
    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        return "DOWN";
    }
    return "NONE";
}

pair<int, int> Game::cameraToPixels(double xCamera, double yCamera) const {
    int x = int((xCamera + 1) / 2 * float(this->getWidth()));
    int y = int((yCamera + 1) / 2 * float(this->getHeight()));
    return make_pair(x, y);
}


EntityModel *ConcreteFactory::createEntity(const string &tag, const int &row, const int &col) {
    EntityModel* model = AbstractFactory::createEntity(tag, row, col);
    if (tag == "Wall"){
        game->setViewItem(new GUIWall(model), row, col);
    }
    if (tag == "PacMan"){
        game->setViewItem(new GUIPacMan(model), row, col);
    }
    return model;
}

ConcreteFactory::ConcreteFactory(World *world, Game *game) : AbstractFactory(world), game(game) {}

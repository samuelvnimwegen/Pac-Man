//
// Created by Samuel on 16/11/2023.
//

#include "Game.h"
#include "ConcreteFactory.h"



Game::Game(const int &wd, const int &hg) {
    width = wd;
    height = hg;
    stopwatch = new Stopwatch();

    world = new World();
    this->generateMap();
    factory = new ConcreteFactory(world, this);
    this->getWorld()->setFactory(factory);
    world->buildWorld();
    stateManager = new StateManager();

    assert(this->getHeight() % world->getHeight() == 0);
    assert(this->getWidth() % world->getWidth() == 0);


    sf::RenderWindow window(sf::VideoMode(this->getWidth(), this->getHeight() + 50), "Pac-Man");

    // Score voor level:
    sf::Font font;
    assert(font.loadFromFile("ScoreFont.ttf"));
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(15);
    text.setFillColor(sf::Color::White);
    text.setPosition(20, float(this->getHeight()) + 20);

    // Text voor start:
    sf::Font font1;
    assert(font1.loadFromFile("IntroFont.ttf"));
    sf::Text introText;
    introText.setFont(font1);
    introText.setCharacterSize(20);
    introText.setFillColor(sf::Color::White);
    introText.setPosition(200 , 450);
    introText.setString("press space to begin");
    sf::Text introText2;
    introText2.setFont(font1);
    introText2.setCharacterSize(80);
    introText2.setFillColor(sf::Color::White);
    introText2.setPosition(150 , 300);
    introText2.setString("pacman");

    // Intro image:
    sf::Texture image;
    image.loadFromFile("Intro.png");
    sf::Sprite introSprite;
    introSprite.setTexture(image);
    introSprite.setPosition(250, 50);

    // Text voor pauze:
    sf::Text pauzeText;
    pauzeText.setFont(font1);
    pauzeText.setCharacterSize(30);
    pauzeText.setFillColor(sf::Color::White);
    pauzeText.setPosition(70, 250);
    pauzeText.setString("press space to unpause");

    while (window.isOpen()){
        sf::Event event{};
        while(window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }
        if (this->getStateManager()->getCurrentState()->getTag() == "MenuState"){
            string input = getInput();
            if (input == "SPACE"){
                this->getStateManager()->push();
            }
            window.clear();
            window.draw(introSprite);
            window.draw(introText);
            window.draw(introText2);
            window.display();
        }
        else if (this->getStateManager()->getCurrentState()->getTag() == "LevelState"){
            string input = getInput();
            if (input == "ESCAPE"){
                this->getStateManager()->pauze();
            }
            int steps = stopwatch->getSteps();
            string direction = getDirection();
            this->getWorld()->getPacMan()->moveDirection(direction);
            this->getWorld()->getPacMan()->move(steps);
            text.setString("score " + to_string(this->getWorld()->getPacMan()->getScore()));
            window.clear();
            for (int r = 0; r < this->getWorld()->getHeight(); ++r){
                for (int k = 0; k < this->getWorld()->getWidth(); ++k){
                    auto viewEntity = viewMap[r][k];
                    if (viewEntity != nullptr and !viewEntity->getSubject()->isConsumed()){
                        auto pos = this->cameraToPixels(viewEntity->getSubject()->getCameraX(), viewEntity->getSubject()->getCameraY());
                        sf::Sprite sprite = viewEntity->getSprite();
                        sprite.setPosition(float(pos.first), float(pos.second));
                        window.draw(sprite);
                    }
                }
            }
            if (this->getWorld()->getCoinsLeft() == 0){
                this->getStateManager()->push();
            }
            window.draw(text);
            window.display();
        }
        else if (this->getStateManager()->getCurrentState()->getTag() == "PausedState"){
            string input = getInput();
            if (input == "SPACE"){
                this->getStateManager()->pop();
                this->stopwatch->getSteps();
            }
            else if (input == "BACKSPACE"){
                window.clear();
                window.draw(pauzeText);
                window.display();
                this->getStateManager()->push();

                stopwatch = new Stopwatch();
                delete world;
                for (auto entity: this->viewEntities){
                    delete entity;
                }

                world = new World();
                this->generateMap();
                this->getWorld()->setFactory(factory);
                world->buildWorld();
            }
            window.clear();
            window.draw(pauzeText);
            window.display();
        }
        else if (this->getStateManager()->getCurrentState()->getTag() == "VictoryState"){
            string input = getInput();
            if (input == "ESCAPE"){
                this->getStateManager()->push();

                stopwatch = new Stopwatch();
                delete world;
                for (auto entity: this->viewEntities){
                    delete entity;
                }

                world = new World();
                this->generateMap();
                this->getWorld()->setFactory(factory);
                world->buildWorld();
            }
            sf::Text introText3;
            introText3.setFont(font1);
            introText3.setCharacterSize(80);
            introText3.setFillColor(sf::Color::White);
            introText3.setPosition(150 , 300);
            introText3.setString("Victory");
            window.clear();
            window.draw(introText3);
            window.display();
        }
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) or sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        return "UP";
    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q) or sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        return "LEFT";
    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) or sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        return "RIGHT";
    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) or sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        return "DOWN";
    }
    return "NONE";
}

pair<int, int> Game::cameraToPixels(double xCamera, double yCamera) const {
    int x = int((xCamera + 1) / 2 * float(this->getWidth()));
    int y = int((yCamera + 1) / 2 * float(this->getHeight()));
    return make_pair(x, y);
}

StateManager *Game::getStateManager() const {
    return stateManager;
}

void Game::setStateManager(StateManager *state) {
    Game::stateManager = state;
}

string Game::getInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
        return "ESCAPE";
    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        return "SPACE";
    }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)){
        return "BACKSPACE";
    }
    return "NONE";
}

ConcreteFactory::ConcreteFactory(World *world, Game *game) : AbstractFactory(world), game(game) {}

PacMan *ConcreteFactory::createPacMan(const int &row, const int &col) {
    PacMan* subject = AbstractFactory::createPacMan(row, col);
    game->setViewItem(new GUIPacMan(subject), row, col);
    return subject;
}

Wall *ConcreteFactory::createWall(const int &row, const int &col) {
    Wall* subject = AbstractFactory::createWall(row, col);
    game->setViewItem(new GUIWall(subject), row, col);
    return subject;
}

Coin *ConcreteFactory::createCoin(const int &row, const int &col) {
    Coin* subject = AbstractFactory::createCoin(row, col);
    game->setViewItem(new GUICoin(subject), row, col);
    return subject;
}

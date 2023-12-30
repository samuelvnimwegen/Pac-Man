//
// Created by Samuel on 16/11/2023.
//

#include "Game.h"

#include <memory>
#include "ConcreteFactory.h"
#include "MenuState.h"
using namespace std;


GUI::Game::Game(const int &wd, const int &hg) {
    width = wd;
    height = hg;
    auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode(this->getWidth(), this->getHeight() + 50), "Pac-Man");

    world = std::make_shared<Model::World>();
    auto score = std::make_shared<Model::Score>(world);
    world->setScore(score);
    auto concreteFactory = std::make_shared<GUI::ConcreteFactory>(world, window);
    world->setFactory(concreteFactory);
    camera = GUI::Camera::instance();
    camera->setScreenHeight(this->getHeight());
    camera->setScreenWidth(this->getWidth());
    this->getCamera()->setModelHeight(this->getWorld()->getHeight());
    this->getCamera()->setModelWidth(this->getWorld()->getWidth());
    world->buildWorld();

    auto stopwatch = Model::Stopwatch::instance();

    stateManager = std::make_shared<GUI::StateManager>();
    stateManager->push(std::make_unique<MenuState>(stateManager, world));

    assert(this->getHeight() % world->getHeight() == 0);
    assert(this->getWidth() % world->getWidth() == 0);


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

    while (window->isOpen()){
        sf::Event event{};
        while(window->pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window->close();
            }
        }
        this->getStateManager()->update(getInput());
        if (this->getStateManager()->getCurrentTag() == menu){
            window->clear();
            window->draw(introSprite);
            window->draw(introText);
            window->draw(introText2);
            window->display();
        }
        else if (this->getStateManager()->getCurrentTag() == level){
            double time = Model::Stopwatch::instance()->getDeltaTime();
            direction direction = getDirection();
            if (this->getWorld()->getPacMan()->getCurrentDirection() != direction::none){
                if (!this->getWorld()->isGameStarted()){
                    stopwatch->startLevel();
                }
                this->getWorld()->setGameStarted(true);
            }
            this->getWorld()->getPacMan()->changeDirection(direction);
            text.setString("score " + to_string(this->getWorld()->getScoreClass()->getScore()));
            window->clear();
            this->getWorld()->update(time);
            window->draw(text);
            window->display();
        }
        else if (this->getStateManager()->getCurrentTag() == paused){
            window->clear();
            window->draw(pauzeText);
            window->display();
        }
        else if (this->getStateManager()->getCurrentTag() == victory){
            sf::Text introText3;
            introText3.setFont(font1);
            introText3.setCharacterSize(80);
            introText3.setFillColor(sf::Color::White);
            introText3.setPosition(150 , 300);
            introText3.setString("Victory");
            window->clear();
            window->draw(introText3);
            window->display();
        }
    }
}

int GUI::Game::getWidth() const {
    return width;
}



int GUI::Game::getHeight() const {
    return height;
}

GUI::Game::~Game() = default;

direction GUI::Game::getDirection() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) or sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        return direction::up;
    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q) or sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        return direction::left;
    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) or sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        return direction::right;
    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) or sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        return direction::down;
    }
    return direction::none;
}

pair<int, int> GUI::Game::cameraToPixels(double xCamera, double yCamera) const {
    int x = int((xCamera + 1) / 2 * float(this->getWidth()));
    int y = int((yCamera + 1) / 2 * float(this->getHeight()));
    return make_pair(x, y);
}


key GUI::Game::getInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
        return escape;
    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        return space;
    }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)){
        return backspace;
    }
    return noKey;
}

const shared_ptr<Model::World> &GUI::Game::getWorld() const {
    return world;
}

const shared_ptr<GUI::Camera> &GUI::Game::getCamera() const {
    return camera;
}

const shared_ptr<GUI::StateManager> &GUI::Game::getStateManager() const {
    return stateManager;
}





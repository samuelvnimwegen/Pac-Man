//
// Created by Samuel on 16/11/2023.
//

#include "Game.h"

#include <memory>
#include "ConcreteFactory.h"
#include "MenuState.h"
#include "fstream"
using namespace std;


GUI::Game::Game() {
    screenWidth = 800;
    screenHeight = 440;

    camera = GUI::Camera::instance();
    camera->setScreenHeight(this->getScreenHeight());
    camera->setScreenWidth(this->getScreenWidth());

    world = std::make_shared<Model::World>();
    auto score = std::make_shared<Model::Score>(world);
    world->setScore(score);
    auto concreteFactory = std::make_shared<GUI::ConcreteFactory>(world);
    world->setFactory(concreteFactory);

    auto beginBuffer = make_unique<sf::SoundBuffer>();
    beginBuffer->loadFromFile("../SoundEffects/pacman_beginning.wav");
    auto beginSound = make_unique<sf::Sound>(*beginBuffer);

    this->getCamera()->setModelHeight(this->getWorld()->getHeight());
    this->getCamera()->setModelWidth(this->getWorld()->getWidth());
    world->buildWorld();

    auto stopwatch = Model::Stopwatch::instance();

    stateManager = std::make_shared<GUI::StateManager>();
    stateManager->push(std::make_unique<MenuState>(stateManager, world));

    // Score voor level:
    sf::Font font;
    font.loadFromFile("../Fonts/ScoreFont.ttf");
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(15);
    text.setFillColor(sf::Color::White);
    text.setPosition(20, float(this->getScreenHeight()) + 20);

    // Levens left voor level
    sf::Text livesText;
    livesText.setFont(font);
    livesText.setCharacterSize(15);
    livesText.setFillColor(sf::Color::White);
    livesText.setPosition(575, float(this->getScreenHeight()) + 20);

    // Text voor start:
    sf::Font font1;
    font1.loadFromFile("../Fonts/IntroFont.ttf");

    sf::Text introText2;
    introText2.setFont(font1);
    introText2.setCharacterSize(80);
    introText2.setFillColor(sf::Color::White);
    introText2.setPosition(150 , 300);
    introText2.setString("pacman");

    // Intro image:
    sf::Texture image;
    image.loadFromFile("../Sprites/pacmanIntro.png");
    sf::Sprite introSprite;
    introSprite.setTexture(image);
    sf::Vector2f targetSize(350.0f, 200.0f);
    introSprite.setScale(targetSize.x / introSprite.getLocalBounds().width,targetSize.y / introSprite.getLocalBounds().height);
    introSprite.setPosition(250, 50);

    // Text voor pauze:
    sf::Text pauzeText;
    pauzeText.setFont(font1);
    pauzeText.setCharacterSize(30);
    pauzeText.setFillColor(sf::Color::White);
    pauzeText.setPosition(70, 250);
    pauzeText.setString("press space to unpause");

    // Text voor level waar we nu zijn:
    sf::Text levelText;
    levelText.setFont(font);
    levelText.setCharacterSize(15);
    levelText.setFillColor(sf::Color::White);
    levelText.setPosition(340, float(this->getScreenHeight()) + 20);

    beginSound->play();

    while (Window::instance()->getWindow()->isOpen()){
        sf::Event event{};
        while(Window::instance()->getWindow()->pollEvent(event)){
            if (event.type == sf::Event::Closed){
                Window::instance()->getWindow()->close();
            }
        }
        if (beginSound->getStatus() != sf::SoundSource::Playing){
            this->getStateManager()->update(getInput());
        }
        if (this->getStateManager()->getCurrentTag() == menu){
            Window::instance()->getWindow()->clear();
            Window::instance()->getWindow()->draw(introSprite);
            Window::instance()->getWindow()->draw(introText2);
            if (beginSound->getStatus() != sf::SoundSource::Playing){
                drawStartButton();
                drawScoreboard();
            }
            Window::instance()->getWindow()->display();
        }
        else if (this->getStateManager()->getCurrentTag() == level){
            double time = Model::Stopwatch::instance()->getDeltaTime();
            if (time > 0.3 and this->getWorld()->getPacMan()->getCurrentDirection() != direction::none){
                throw std::runtime_error("Tick-time higher than 0.3 seconds");
            }
            direction direction = getDirection();
            if (this->getWorld()->getPacMan()->getCurrentDirection() != direction::none){
                if (!this->getWorld()->isGameStarted()){
                    stopwatch->startLevel();
                }
                this->getWorld()->setGameStarted(true);
            }
            this->getWorld()->getPacMan()->changeDirection(direction);

            // Text voor score, level en voor levens:
            levelText.setString("level " + to_string(this->getWorld()->getLevelNr() + 1));
            text.setString("score " + to_string(this->getWorld()->getScoreClass()->getScore()));
            livesText.setString("lives left " + to_string(this->getWorld()->getScoreClass()->getLivesLeft()));
            Window::instance()->getWindow()->clear();

            this->getWorld()->update(time);

            Window::instance()->getWindow()->draw(text);
            Window::instance()->getWindow()->draw(levelText);
            this->drawLives();
            Window::instance()->getWindow()->display();
        }
        else if (this->getStateManager()->getCurrentTag() == paused){
            sf::Text pressEscape;
            pressEscape.setFont(font1);
            pressEscape.setCharacterSize(15);
            pressEscape.setFillColor(sf::Color::White);
            pressEscape.setPosition(120 , 450);
            pressEscape.setString("Press escape to go to the main menu");
            Window::instance()->getWindow()->clear();
            Window::instance()->getWindow()->draw(pauzeText);
            Window::instance()->getWindow()->draw(pressEscape);
            Window::instance()->getWindow()->display();
        }
        else if (this->getStateManager()->getCurrentTag() == victory){
            sf::Text introText3;
            introText3.setFont(font1);
            introText3.setCharacterSize(80);
            introText3.setFillColor(sf::Color::White);
            introText3.setPosition(120 , 200);
            introText3.setString("Victory");
            sf::Text pressSpace;
            pressSpace.setFont(font1);
            pressSpace.setCharacterSize(20);
            pressSpace.setFillColor(sf::Color::White);
            pressSpace.setPosition(50 , 400);
            pressSpace.setString("Press space to go to the next level");

            sf::Text pressEscape;
            pressEscape.setFont(font1);
            pressEscape.setCharacterSize(15);
            pressEscape.setFillColor(sf::Color::White);
            pressEscape.setPosition(120 , 450);
            pressEscape.setString("Press escape to go to the main menu");

            Window::instance()->getWindow()->clear();
            Window::instance()->getWindow()->draw(introText3);
            Window::instance()->getWindow()->draw(pressSpace);
            Window::instance()->getWindow()->draw(pressEscape);
            Window::instance()->getWindow()->display();
        }
        else if (this->getStateManager()->getCurrentTag() == gameOver){
            this->getStateManager()->update(getInput());
        sf::Text gameOverText;
        gameOverText.setFont(font1);
        gameOverText.setCharacterSize(70);
        gameOverText.setFillColor(sf::Color::White);
        gameOverText.setPosition(80 , 200);
        gameOverText.setString("Game Over");
        sf::Text pressSpace;
        pressSpace.setFont(font1);
        pressSpace.setCharacterSize(20);
        pressSpace.setFillColor(sf::Color::White);
        pressSpace.setPosition(90 , 400);
        pressSpace.setString("Press space to go back to menu");
        Window::instance()->getWindow()->clear();
        Window::instance()->getWindow()->draw(gameOverText);
        Window::instance()->getWindow()->draw(pressSpace);
        Window::instance()->getWindow()->display();
        }
    }
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


key GUI::Game::getInput() {
    // Er mag elke 0.2 seconden en unieke nieuwe input zijn:
    static double lastInput = Model::Stopwatch::instance()->getTotalSeconds();
    if (lastInput + 0.2 < Model::Stopwatch::instance()->getTotalSeconds()){
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
            lastInput = Model::Stopwatch::instance()->getTotalSeconds();
            return escape;
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
            lastInput = Model::Stopwatch::instance()->getTotalSeconds();
            return space;
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)){
            lastInput = Model::Stopwatch::instance()->getTotalSeconds();
            return backspace;
        }
        else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            auto mouseX = getMousePosition().x;
            auto mouseY = getMousePosition().y;
            if (mouseX < 550 and mouseX > 250 and mouseY < 463 and mouseY > 410){
                return startButton;
            }
            return leftMouseButton;
        }
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

int GUI::Game::getScreenWidth() const {
    return screenWidth;
}

int GUI::Game::getScreenHeight() const {
    return screenHeight;
}

void GUI::Game::drawLives() const {
    auto window = GUI::Window::instance()->getWindow();
    sf::Texture texture;
    texture.loadFromFile("../Sprites/Heart.png");
    sf::Sprite sprite(texture);
    int offset = 0;
    for (int i = 0; i < this->getWorld()->getScoreClass()->getLivesLeft(); ++i){
        sprite.setPosition(float(this->getScreenWidth() - 60 - offset), float(this->getScreenHeight()));
        window->draw(sprite);
        offset += 40;
    }

}

void GUI::Game::drawScoreboard() {
    auto window = GUI::Window::instance()->getWindow();

    sf::RectangleShape rectangle(sf::Vector2f(155, 150));
    rectangle.setOutlineColor(sf::Color::Blue);
    rectangle.setFillColor(sf::Color::Transparent);
    rectangle.setOutlineThickness(5);
    rectangle.setPosition(630, 10);
    window->draw(rectangle);

    sf::Text scoreBoardText;
    sf::Font font;
    font.loadFromFile("../Fonts/IntroFont.ttf");
    scoreBoardText.setFont(font);

    scoreBoardText.setCharacterSize(15);
    scoreBoardText.setFillColor(sf::Color::White);
    scoreBoardText.setPosition(630, 10);
    scoreBoardText.setString("scoreboard");
    window->draw(scoreBoardText);

    ifstream scoreFile("../ScoreBoard.txt");
    string score;
    int counter = 1;
    while (scoreFile >> score){
        scoreBoardText.setString(score);
        scoreBoardText.setPosition(675, float(10 + counter * 25));
        ++counter;
        window->draw(scoreBoardText);
    }
}

sf::Vector2i GUI::Game::getMousePosition() {
    return sf::Mouse::getPosition(*GUI::Window::instance()->getWindow());
}

void GUI::Game::drawStartButton() {
    auto window = Window::instance()->getWindow();
    auto rect = sf::RectangleShape(sf::Vector2f(300, 50));
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineColor(sf::Color::White);
    rect.setOutlineThickness(4);
    rect.setPosition(250 , 407);

    auto rect2 = sf::RectangleShape(sf::Vector2f(300, 50));
    rect2.setFillColor(sf::Color::Transparent);
    rect2.setOutlineColor(sf::Color::White);
    rect2.setOutlineThickness(4);
    rect2.setPosition(250 , 410);

    sf::Font font;
    font.loadFromFile("../Fonts/IntroFont.ttf");
    sf::Text introText;
    introText.setFont(font);
    introText.setCharacterSize(20);
    introText.setFillColor(sf::Color::White);
    introText.setPosition(360 , 428);
    introText.setString("Play");

    auto mouseX = getMousePosition().x;
    auto mouseY = getMousePosition().y;
    if (!(mouseX < 550 and mouseX > 250 and mouseY < 463 and mouseY > 410)){
        window->draw(rect);
        introText.setPosition(360 , 425);
    }
    window->draw(rect2);
    window->draw(introText);
}









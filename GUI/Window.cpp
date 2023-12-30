//
// Created by Samuel on 30/12/2023.
//

#include "Window.h"
#include "../Camera.h"
#include <memory>
std::shared_ptr<GUI::Window> GUI::Window::windowPointer = nullptr;

GUI::Window::~Window() = default;

std::shared_ptr<GUI::Window> GUI::Window::instance() {
    if (windowPointer == nullptr){
        auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode(Camera::instance()->getScreenWidth(), Camera::instance()->getScreenHeight() + 50), "Pac-Man");
        windowPointer = std::shared_ptr<GUI::Window>(new GUI::Window);
        return windowPointer;
    }
    return windowPointer;
}

GUI::Window::Window() {
    window = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 440 + 50), "Pac-Man");
}

const std::shared_ptr<sf::RenderWindow> &GUI::Window::getWindow() const {
    return window;
}





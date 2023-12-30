//
// Created by Samuel on 30/12/2023.
//

#ifndef PAC_MAN_WINDOW_H
#define PAC_MAN_WINDOW_H
#include "../Subject.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

class GUI::Window {
    std::shared_ptr<sf::RenderWindow> window;
    static std::shared_ptr<GUI::Window> windowPointer;
public:
    virtual ~Window();

    static std::shared_ptr<GUI::Window> instance();

    [[nodiscard]] const std::shared_ptr<sf::RenderWindow> &getWindow() const;

protected:
    Window();
};


#endif //PAC_MAN_WINDOW_H

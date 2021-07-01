#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Board.hpp"

class Game {
       public:
           Game(const Game&) = delete;
           Game& operator=(const Game&) = delete;
           Game();
           void run(int frame_per_second);
       private:
           void processEvents();
           void update(sf::Time deltaTime);
           void render();
           sf::ContextSettings settings;
           sf::RenderWindow window;
           Board myBilliardsBoard;
};

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "headers/board.h"
#include "headers/ship.h"
#include <memory>
#include "headers/player.h"

int main() {
  sf::RenderWindow window(sf::VideoMode(1600, 800), "Naval Battle");
  window.setKeyRepeatEnabled(false);

   
  Constants::MakeX();
  Constants::MakePoint();
  Symbol::MakeFont();

  Board board1(10, Point(100, 100), 50);  // поле
  Board board2(10, Point(900, 100), 50);
  Player player1(board1, std::unique_ptr<PlayerState>(new PlacingShips()));
  Player player2(board2, std::unique_ptr<PlayerState>(new Starting()));

  sf::RectangleShape game_background;  // задний фон
  game_background.setFillColor(sf::Color(255, 255, 255));
  game_background.setSize(sf::Vector2f(1600, 800));

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
        break;
      }
      player1.Handle(event, window, player2);
      player2.Handle(event, window, player1);
    }
    window.clear();
    window.draw(game_background);
    board1.Draw(window);
    board2.Draw(window);
    window.display();
  }
}

#include "IosevkaCharonMono-Regular.hpp"
#include "helper.hpp"
#include <SFML/Graphics.hpp>

int main() {
  sf::RenderWindow window(setWindow());

  sf::RectangleShape player(setPlayerPaddle(window));
  sf::RectangleShape opponent(setOpponentPaddle(window));
  sf::RectangleShape ball(setBall(window));

  sf::Vector2f ballSpeed = {5, 5};
  int score[] = {0 /*Player Score*/, 0 /*Opponent Score*/};
  sf::Font font;
  if (!font.openFromMemory(IosevkaCharonMono_Regular, 1443296)) {
    window.close();
    return 0;
  }

  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
    }
    window.clear(backgroundColor);

    courtDivider(window);

    window.draw(player);
    window.draw(opponent);
    window.draw(ball);

    playerMovementControl(player, window);
    ballMovement(window, player, opponent, ball, ballSpeed, score);
    opponentMovementControl(ball, opponent, window);

    displayScore(score, font, window);

    window.display();
  }
}

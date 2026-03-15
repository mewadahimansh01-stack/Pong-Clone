#include "helper.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <sstream>

int main() {
  sf::RenderWindow window(setWindow());

  sf::RectangleShape player(setPlayerPaddle(window));
  sf::RectangleShape opponent(setOpponentPaddle(window));
  sf::RectangleShape ball(setBall(window));

  sf::Vector2f ballSpeed = {5, 5};
  int score[] = {0 /*Player Score*/, 0 /*Opponent Score*/};
  sf::Font font("/home/himansh/Desktop/Pong-Clone/Iosevka_Charon_Mono/IosevkaCharonMono-Italic.ttf");

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

    std::stringstream current{""};
    current << score[0] << "\t\t\t" << score[1];
    sf::Text current_text(font, current.str(), 30);
    current_text.setPosition({static_cast<float>(window.getSize().x / 2.F - current_text.getGlobalBounds().size.x / 2), 20.F});
    window.draw(current_text);

    window.display();
  }
}

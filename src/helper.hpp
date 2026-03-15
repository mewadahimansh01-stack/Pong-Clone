#pragma once
#include "logo.hpp"
#include <SFML/Graphics.hpp>
#include <chrono>
#include <random>
#include <sstream>
#include <thread>

static const inline void displayScore(const int *score, sf::Font &font,
                                      sf::RenderWindow &window) {
  std::stringstream current{""};
  current << score[0] << "\t\t\t" << score[1];
  sf::Text current_text(font, current.str(), 30);
  current_text.setPosition(
      {static_cast<float>(window.getSize().x / 2.F -
                          current_text.getGlobalBounds().size.x / 2),
       20.F});
  window.draw(current_text);
}

constexpr auto backgroundColor(sf::Color(44, 62, 80, 1));
constexpr double speed{5};
constexpr double ballDimension{15};
constexpr int frameRate{60};
constexpr auto up{sf::Vector2f({0, -speed})};
constexpr auto down{sf::Vector2f({0, +speed})};
constexpr double oSpeed{speed / 2 /*Slowpoke*/};
constexpr auto oUp{sf::Vector2f({0, -oSpeed})};
constexpr auto oDown{sf::Vector2f({0, +oSpeed})};
static auto paddle{sf::RectangleShape({10, 80})};
constexpr double taperingFactor{0.25};
constexpr double acceleration{0.5};
constexpr sf::Vector2f ballSpeedDefault = {5, 5};

static const inline void opponentMovementControl(sf::RectangleShape &ball,
                                                 sf::RectangleShape &opponent,
                                                 sf::RenderWindow &window) {
  const auto distance{ball.getPosition().y - opponent.getPosition().y -
                      opponent.getSize().y / 2.F};
  const auto opponentPosition = opponent.getPosition();
  if ((distance < 0.F) && (opponentPosition.y >= 0.F)) {
    if (distance < -oSpeed) {
      opponent.move(oUp);
    } else {
      opponent.move({0.F, distance});
    }
  } else if ((distance > 0.F) && (opponentPosition.y <=
                                  window.getSize().y - opponent.getSize().y)) {
    if (distance > oSpeed) {
      opponent.move(oDown);
    } else {
      opponent.move({0.F, distance});
    }
  }
}

static const inline void ballMovement(sf::RenderWindow &window,
                                      sf::RectangleShape &player,
                                      sf::RectangleShape &opponent,
                                      sf::RectangleShape &ball,
                                      sf::Vector2f &ballSpeed, int *score) {
  const auto ballPosition{ball.getPosition()};
  const auto playerPosition{player.getPosition()};
  const auto opponentPosition{opponent.getPosition()};
  const auto playerSize{player.getSize()};
  const auto ballSize{ball.getSize()};
  const auto opponentSize{opponent.getSize()};
  const auto windowSize{window.getSize()};

  if (ballPosition.y <= 0.F || ballPosition.y + ballSize.y >= windowSize.y) {
    ballSpeed.y = -ballSpeed.y;
  }

  if ((ballPosition.x <= (playerPosition.x + playerSize.x) &&
       ballPosition.x >= playerPosition.x &&
       ballPosition.y + ballSize.y >= playerPosition.y &&
       ballPosition.y <= playerPosition.y + playerSize.y)) {
    ballSpeed.x =
        -ballSpeed.x +
        ((ballSpeed.x < -(speed - 0.51 /*Safety Net*/)) ? acceleration : 0);
    const auto hitpos{(ballPosition.y - playerPosition.y - playerSize.y / 2.F) /
                      playerSize.y};
    ballSpeed.y = speed * hitpos * taperingFactor;
  }

  if ((ballPosition.x + ballSize.x >= opponentPosition.x &&
       ballPosition.x <= opponentPosition.x + opponentSize.x &&
       ballPosition.y + ballSize.y >= opponentPosition.y &&
       ballPosition.y <= opponentPosition.y + opponentSize.y)) {
    ballSpeed.x =
        -ballSpeed.x -
        ((ballSpeed.x < (speed - 0.51 /*Safety Net*/)) ? acceleration : 0);
    const auto hitpos{(ballPosition.y - playerPosition.y - playerSize.y / 2.F) /
                      playerSize.y};
    ballSpeed.y = speed * hitpos * taperingFactor;
  }

  // Scoring area

  if (ballPosition.x < 0.F) {
    score[1] += 1;
    ball.setPosition(
        {static_cast<float>(windowSize.x / 2.F - ballSize.x / 2.F),
         static_cast<float>(windowSize.y / 2.F - ballSize.y / 2.F)});
    static std::random_device rd;
    static std::mt19937 engine(rd());
    std::uniform_real_distribution<float> dist(-1.F, 1.F);
    std::uniform_int_distribution<> distr(-1, 1);
    ballSpeed.y = dist(engine) * ballSpeedDefault.y;
    ballSpeed.x = distr(engine) * ballSpeedDefault.x;
    std::this_thread::sleep_for(std::chrono::microseconds(1));
  }

  if (ballPosition.x > windowSize.x) {
    score[0] += 1;
    ball.setPosition(
        {static_cast<float>(windowSize.x / 2.F - ballSize.x / 2.F),
         static_cast<float>(windowSize.y / 2.F - ballSize.y / 2.F)});
    static std::random_device rd;
    static std::mt19937 engine(rd());
    std::uniform_real_distribution<float> dist(-1.F, 1.F);
    std::uniform_int_distribution<int> distr(-1, 1);
    ballSpeed.y = dist(engine) * ballSpeedDefault.y;
    ballSpeed.x = distr(engine) * ballSpeedDefault.x;
    std::this_thread::sleep_for(std::chrono::microseconds(1));
  }

  if (ballSpeed.x == 0) {
    ballSpeed.x += ballSpeedDefault.x;
  }

  ball.move(ballSpeed);
}

static const inline sf::RectangleShape setBall(sf::RenderWindow &window) {
  sf::RectangleShape ball({ballDimension, ballDimension});
  ball.setFillColor(sf::Color::Cyan);
  const auto windowSize{window.getSize()};
  const auto ballSize{ball.getSize()};
  ball.setPosition({static_cast<float>(windowSize.x / 2.F - ballSize.x / 2.F),
                    static_cast<float>(windowSize.y / 2.F - ballSize.y / 2.F)});
  return ball;
}

static const inline void courtDivider(sf::RenderWindow &window) {
  float divider[] = {2.5F, 20.F};
  auto windowDimensions{window.getSize()};
  for (float i{10.F}; i < windowDimensions.y;) {
    sf::RectangleShape current({divider[0], divider[1]});
    current.setPosition(
        {static_cast<float>(windowDimensions.x / 2.F - divider[0] / 2.F), i});
    current.setFillColor(sf::Color::White);
    window.draw(current);
    i += 2.F * divider[1];
  }
}

static const inline sf::RectangleShape
setPlayerPaddle(sf::RenderWindow &window) {
  paddle.setFillColor(sf::Color::Yellow);
  sf::RectangleShape player(paddle);
  player.setPosition({20.F, static_cast<float>(window.getSize().y / 2.F -
                                               paddle.getSize().y / 2.F)});
  return player;
}

static const inline sf::RectangleShape
setOpponentPaddle(sf::RenderWindow &window) {
  paddle.setFillColor(sf::Color::Yellow);
  const auto windowSize{window.getSize()};
  sf::RectangleShape opponent(paddle);
  opponent.setPosition(
      {static_cast<float>(windowSize.x - 30.F),
       static_cast<float>(windowSize.y / 2.F - paddle.getSize().y / 2.F)});
  return opponent;
}

static const inline sf::RenderWindow setWindow() {
  sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
  sf::RenderWindow window(sf::VideoMode({800U, 600U}), "Pong Clone",
                          sf::Style::Close);
  window.setIcon(sf::Image({LOGO_WIDTH, LOGO_HEIGHT}, logo));
  window.setFramerateLimit(frameRate);
  const sf::Vector2u windowSize{window.getSize()};
  window.setPosition(
      {static_cast<int>(desktopMode.size.x / 2.F - windowSize.x / 2.F),
       static_cast<int>(desktopMode.size.y / 2.F - windowSize.y / 2.F)});
  return window;
}

static const inline void playerMovementControl(sf::RectangleShape &player,
                                               const sf::RenderWindow &window) {
  const sf::Vector2f playerPosition{player.getPosition()};
  if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) ||
       sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) &&
      playerPosition.y > 0.F) {
    player.move(up);
  }
  if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) ||
       sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) &&
      playerPosition.y < window.getSize().y - player.getSize().y) {
    player.move(down);
  }
}

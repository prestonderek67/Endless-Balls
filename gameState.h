#pragma once

#include "game_object.h"
#include "world.h"
#include "bossEnemy.h"


class GameState: public GameObject {
public:
  GameState (World & world, float x, float y) : GameObject{world, x, y} {
    if (!font.loadFromFile("assets/slkscr.ttf")) {
      std::cerr << "Couldn't load font..." << std::endl;
    }

    if (!texture.loadFromFile("assets/background.png")) {
      std::cerr << "Couldn't load font..." << std::endl;
    }
    objectType = TEXT;

    background.setTexture(texture);
    background.setOrigin(400, 400);
    background.setPosition(x + 400, y + 380);

    title.setFont(font);
    title.setString("ENDLESS BALLS");
    title.setCharacterSize(80);
    title.setFillColor(sf::Color::Magenta);
    title.setPosition(x, y);

    menuMessage.setFont(font);
    menuMessage.setString("\nPRESS ENTER TO START");
    menuMessage.setCharacterSize(50);
    menuMessage.setFillColor(sf::Color::Red);
    menuMessage.setPosition(x, y + 200);

    howToPlay.setFont(font);
    howToPlay.setString("Catch all soccer balls.\n"
                        "Don't catch the footballs.\n"
                        "Catch the shoes for a boost.\n"
                        "\nA to go right, D to go left.");
    howToPlay.setCharacterSize(25);
    howToPlay.setFillColor(sf::Color::Black);
    howToPlay.setPosition(x, y + 100);

    loseMessage.setFont(font);
    loseMessage.setString("GAME OVER\n"
                          "PRESS ENTER TO RESTART");
    loseMessage.setCharacterSize(50);
    loseMessage.setFillColor(sf::Color::Black);
    loseMessage.setPosition(x + 50, y + 200);

  }

  void update(float dt) override {
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && state != 1) {
        auto &player = world.addObject<Player>(world.width / 2, .90 * world.height);
        ++state;
        world.lives = 10;
      }

      if (state == 1) {
        elapsed2 = clock2.getElapsedTime();

        if (elapsed2 >= buffEnemy) {
          auto &bEnemy = world.addObject<EnemyBuff>(rand() % world.width, -50);
          clock2.restart();
        }

        elapsed = clock1.getElapsedTime();

        if (elapsed >= regEnemy) {
          auto & rEnemy = world.addObject<Enemy>(rand() % world.width, -40);
          clock1.restart();
        }

        elapsed3 = clock3.getElapsedTime();

        if (elapsed3 >= buffPlayer) {
          auto &bPlayer = world.addObject<PlayerBuff>(rand() % world.width, -20);
          clock3.restart();
        }
        if (world.lives == 0) {
          for (auto & object : world) {
            if (object.getType() == ENEMY || object.getType() == ENEMYBUFF || object.getType() == PLAYERBUFF || object.getType() == BOSS) {
              object.shouldRemove = true;
            }
          }
          state = 2;
        }

        if (world.bossCounter == 10) {
          auto & boss = world.addObject<BossEnemy>(rand() % world.width, -10);
          world.bossCounter = 0;
        }
      }
  }

  void render(sf::RenderWindow & window) override {
    window.draw(background);
    if (state == 0) {
      window.draw(menuMessage);
      window.draw(title);
      window.draw(howToPlay);
    }
    if (state == 2) {
      window.draw(loseMessage);
    }
    if (state > 2) {
      state = 1;
    }
  }

private:
  sf::Text title;
  sf::Text menuMessage;
  sf::Text howToPlay;
  sf::Text loseMessage;
  sf::Font font;
  sf::Sprite background;
  size_t state{0};
  sf::Clock clock1;
  sf::Clock clock2;
  sf::Clock clock3;
  sf::Time elapsed;
  sf::Time elapsed2;
  sf::Time elapsed3;
  sf::Time regEnemy{sf::seconds(1.0f)};
  sf::Time buffEnemy{sf::seconds(10.0f)};
  sf::Time buffPlayer{sf::seconds(12.0f)};
};
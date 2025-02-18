#pragma once

#include "game_object.h"
#include "world.h"

class Player : public GameObject {
public:
    Player (World & world, float x, float y) : GameObject{world, x, y} {
        if (!texture.loadFromFile("assets/finalPlayer.png")) {
            std::cerr << "Couldn't load player..." << std::endl;
        }
        pos.x = x;
        pos.y = y;
        sprite.setPosition(pos);
        sprite.setTexture(texture);
        sprite.setOrigin(16,16);
        sprite.setScale(myScale);
        objectType = PLAYER;

    }

    void update(float dt) override {

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            pos.x -= playerSpeed*dt;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            pos.x += playerSpeed*dt;
        }

        if (pos.x + 16 >= world.width) {
            pos.x  = world.width - 16;
        }
        if (pos.x - 16 <= 0) {
            pos.x = 0 + 16;
        }
        sf::Vector2<float> curScale{sprite.getScale()};
        if (curScale.x > myScale.x && curScale.y > myScale.y) {
          if (!timing) {
            clock.restart();
            timing = true;
          }
          elapsed = clock.getElapsedTime();
          if (elapsed >= time) {
            timing = false;
            sprite.setScale(myScale);
          }
        }

        if (world.lives == 0) {
          shouldRemove = true;
        }
    }

    void render(sf::RenderWindow & window) override {
        sprite.setPosition(pos);
        window.draw(sprite);
    }

private:
  sf::Vector2<float> myScale{1.5, 1.5};
  sf::Clock clock;
  sf::Time time{sf::seconds(10.f)};
  sf::Time elapsed{};
  bool timing{false};
};
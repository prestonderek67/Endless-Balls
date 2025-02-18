#pragma once

#include "game_object.h"
#include "world.h"
#include <cmath>

class BossEnemy : public GameObject {
public:
  BossEnemy(World & world, float x, float y) : GameObject{world, x, y} {
    if (!texture.loadFromFile("assets/tennisBall.png")) {
      std::cerr << "Couldn't load boss enemy..." << std::endl;
    }

    objectType = BOSS;

    pos.x = x;
    pos.y = y;

    sprite.setTexture(texture);
    sprite.setPosition(pos);
    sprite.setOrigin(16, 16);
    sprite.setScale(2, 2);

  }

  void update(float dt) override {
    if (health == 0) {
      dead = true;
    }
    pos = sprite.getPosition();

    if (down) {
      pos.y += mySpeed * dt;
    }

    if (!down) {
      pos.y -= mySpeed * dt;
    }
    for (auto &object : world) {
      if (object.getType() == PLAYER) {
        if (checkCollision(object, getBounds())) {
          down = false;
          hit = true;
          if (hit) {
            --health;
            hit = false;
          }
        }
      }
    }


    if (sprite.getPosition().y <= swap) {
      //pos.y += mySpeed * dt;
      down = true;
    }

    if (pos.y >= (world.height + 30) ) {
      shouldRemove = true;
    }

    if (dead) {
      shouldRemove = true;
    }
    sprite.setPosition(pos);

  }

  void render(sf::RenderWindow & window) override {
    sprite.setPosition(pos);
    window.draw(sprite);
  }

private:
  float angle;
  int mySpeed{300};
  int health{3};
  const float swap{100};
  bool down{true};
  bool dead{false};
  bool hit{false};
};
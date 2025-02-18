#pragma once

#include "game_object.h"
#include "world.h"

class PlayerBuff : public GameObject {
public:
 PlayerBuff(World & world, float x, float y) : GameObject{world, x, y} {
  if (!texture.loadFromFile("assets/shoePU.png")) {
   std::cerr << "Couldn't load enemy buff..." << std::endl;
  }

  objectType = PLAYERBUFF;
  sprite.setTexture(texture);
  sprite.setOrigin(16, 16);

  pos.x = x;
  pos.y = y;
 }

 void update(float dt) override {
  pos.y += speed*dt;

  if (pos.y > world.height) {
   shouldRemove = true;
   --lives;
  }

  for (auto &object : world) {
   if (object.getType() == PLAYER) {
    if (checkCollision(object, getBounds())) {
     shouldRemove = true;
     object.setScale();
    }
   }
  }
 }

 void render(sf::RenderWindow & window) override {
  sprite.setPosition(pos);
  window.draw(sprite);
 }
private:
};

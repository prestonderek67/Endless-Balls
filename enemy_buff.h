#pragma once

#include "game_object.h"
#include "world.h"

class EnemyBuff : public GameObject {
public:
    EnemyBuff(World & world, float x, float y) : GameObject{world, x, y} {
        if (!texture.loadFromFile("assets/football.png")) {
            std::cerr << "Couldn't load enemy buff..." << std::endl;
        }

        objectType = ENEMYBUFF;
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
                   for (size_t i{}; i < enemyBuffMax; ++i) {
                     auto & enemy = world.addObject<Enemy>(rand() % world.width, rand() % -100);
                   }
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
#pragma once

#include "game_object.h"
#include "world.h"

class Enemy : public GameObject {
public:
    Enemy (World & world, float x, float y) : GameObject{world, x, y} {
        if (!texture.loadFromFile("assets/soccerBall.png")) {
            std::cerr << "Couldn't load general enemy..." << std::endl;
        }
        objectType = ENEMY;
        pos.x = x;
        pos.y = y;

        sprite.setTexture(texture);
        sprite.setOrigin(16, 16);
        sprite.setPosition(pos);
    }

    void update(float dt) override {
        pos.y += speed*dt;

        if (pos.y > world.height) {
            shouldRemove = true;
            --world.lives;
        }

        for (auto &object : world) {
            if (object.getType() == PLAYER) {
                if (checkCollision(object, getBounds())) {
                    shouldRemove = true;
                    ++world.bossCounter;
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
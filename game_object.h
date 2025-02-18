#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>

class World;

class GameObject {
public:
  GameObject(World & w, float x = 0, float y = 0);
  virtual ~GameObject() = default;
  virtual void update(float dt);
  virtual void render(sf::RenderWindow & window);
  bool checkCollision(GameObject& object, sf::FloatRect myBounds);
  void resetPos(sf::Vector2f& position);

protected:
  World & world;
  float x, y;
  int lives{20};
  sf::FloatRect myBounds;
  bool playerCheck{false};

protected:
  sf::Texture texture;
  sf::Sprite sprite;
  sf::Vector2f pos;
  int speed{200};
  const int playerSpeed{500};
  int enemyBuffMax{5};

public:
  bool shouldRemove{};

  enum obj{PLAYER, PLAYERBUFF, ENEMY, ENEMYBUFF, TEXT, BOSS};

  obj getType() const {
      return objectType;
  }

  sf::Sprite& getSprite() {
      return sprite;
  }

  sf::FloatRect getBounds() {
      myBounds = sprite.getGlobalBounds();
      return myBounds;
  }

  sf::Vector2f getPos() const{
      return sprite.getPosition();
  }

  void setScale() {
   sprite.setScale(2, 2);
  }

  int getLives() {
    return lives;
  }

protected:
    obj objectType;
};

#include "game_object.h"
#include "world.h"
#include <cmath>

GameObject::GameObject(World & w, float x, float y) : world{w}, x{x}, y{y} {

}

void GameObject::update(float dt) {

}

void GameObject::render(sf::RenderWindow & window) {
  sf::CircleShape shape{15};
  shape.setFillColor(sf::Color::Blue);
  shape.setPosition(x, y);
  window.draw(shape);
}

bool GameObject::checkCollision(GameObject &object, sf::FloatRect myBounds) {
   sf::FloatRect objBounds = object.getSprite().getGlobalBounds();
   return myBounds.intersects(objBounds);
}

void GameObject::resetPos(sf::Vector2f& position) {
  if (position.x > world.width) { position.x = 0; }
  if (position.x < 0) { position.x = world.width; }
  if (position.y > world.height) { position.y = 0; }
  if (position.y < 0) { position.y = world.height; }
}



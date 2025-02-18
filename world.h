#pragma once

#include <memory>
#include <functional>
#include <SFML/Graphics.hpp>

#include "vector.h"
#include "game_object.h"

class World {
public:
  // these are static, meaning they exist on the *class*, not the objects
  // (they're only created once)
  static constexpr auto width{800u};
  static constexpr auto height{800u};
  size_t lives{10};
  size_t bossCounter{0};
  World();
  ~World();

  void run();


  void forEach(std::function<void(GameObject &)> fn);

  // see implementation below (bottom of this file)
  template <typename Object = GameObject, typename... Args>
  auto & addObject(Args&&... args);

  using Container = Vector<std::unique_ptr<GameObject> >;

  class Iterator {
  private:
      size_t index;
      Container & objects;
  public:
      Iterator(Container & objects, size_t index) : objects{objects}, index{index} {
      }

      bool operator!=(const Iterator & other) const {
          return index != other.index;
      }

      Iterator & operator++() {
          ++index;
          return *this;
      }

      GameObject & operator*() {
          return *objects[index];
      }
  };

  Iterator begin() {
      return Iterator{objects, 0};
  }

  Iterator end() {
      return Iterator{objects, objects.size()};
  }

  sf::RenderWindow & getWindow() {
    return window;
  }

  template<typename T>
  void windowDraw(T item) {
    window.clear();
    window.draw(item);
    window.display();
  }

private:
  void processEvents();
  void update(float dt);
  void render();

  sf::RenderWindow window{sf::VideoMode{width, height}, "MyProject"};
  Vector<std::unique_ptr<GameObject> > objects;
};

// this has to be in this file because of how templating works
// we'll go over this next class
template <typename Object, typename... Args>
auto & World::addObject(Args&&... args) {
  auto obj = std::make_unique<Object>(*this, args...);
  return *objects.append(std::move(obj));
}



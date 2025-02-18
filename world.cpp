#include "world.h"
#include "enemy.h"
#include "enemy_buff.h"
#include "player_buff.h"

World::World(){
  window.setVerticalSyncEnabled(true);
}

World::~World() {

}
void World::run() {
  sf::Clock clock;
  sf::Time t{sf::Time::Zero}; // time
  sf::Time dt{sf::seconds(1.0f / 60.0f)}; // delta time (fixed to 60fps)


  while (window.isOpen()) {
    processEvents();
    t += clock.restart();

    while (t > dt) {
      t -= dt;
      processEvents();
      update(dt.asSeconds());
    }

    objects.removeIf([](std::unique_ptr<GameObject> & object) {
      return object->shouldRemove;
    });

    render();
  }
}

void World::forEach(std::function<void(GameObject &)> fn) {
  objects.forEach([&](std::unique_ptr<GameObject> & object) {
    fn(*object);
  });
}

// you can handle global type events in here (e.g. settings or UI type things)
// for movement, see player.h for an example
void World::processEvents() {
  for (sf::Event event; window.pollEvent(event);) {
    if (event.type == sf::Event::Closed) {
      window.close();
    }
  }
}

// this logic should not change
void World::render() {
  // always clear
  window.clear();

  for (auto & object : *this) {
      object.render(window);
  }

  // swap the buffer
  window.display();
}

// this logic should not change
void World::update(float dt) {
    for (auto & object : *this) {
        object.update(dt);
    }
}

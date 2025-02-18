#include <iostream>
#include <SFML/Graphics.hpp>

#include "world.h"
#include "player.h"
#include "enemy.h"
#include "enemy_buff.h"
#include "player_buff.h"
#include "gameState.h"
#include "bossEnemy.h"
#include "game_object.h"

void gameRun();

int main() {
  //World world;

  //auto & player = world.addObject<Player>(world.width / 2, .90 * world.height);
  //auto & enemy = world.addObject<Enemy>(world.width / 2, world.height - 600);
  //auto & enemyBuff = world.addObject<EnemyBuff>(world.width / 3, world.height - 600);
  //auto & playerBuff = world.addObject<PlayerBuff>(world.width / 4, world.height - 600);

  //auto & boss = world.addObject<BossEnemy>(world.width / 2, world.height - 800);
  gameRun();
  //world.run();
}

void gameRun() {
  World world;
  auto & start = world.addObject<GameState>(0, 20);
  world.run();

}
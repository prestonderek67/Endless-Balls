#pragma once

#include <random>

const float pi {3.14159265};

float randInRangeFloat(float min, float max) {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  std::uniform_real_distribution<float> dis(min, max);
  return dis(gen);
}
#include "Physics.h"

const float GRAVITY = -9.8f;

Vector Physics::ProjectilePosition(Vector& initialVelocity, float deltaTime) {

  float y = initialVelocity.GetY() * deltaTime + 0.5 * GRAVITY * deltaTime * deltaTime;
  return Vector(initialVelocity.GetX() * deltaTime * (y != 0),
      y, initialVelocity.GetZ() * deltaTime * (y != 0)); 
}

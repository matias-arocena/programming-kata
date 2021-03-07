#include "Vector.h"
#include <cmath>

Vector::Vector(float x, float y, float z) {
  this->x = x;
  this->y = y;
  this->z = z;
}

float Vector::GetX() {
  return this->x;
}

float Vector::GetY() {
  return this->y;
}

float Vector::GetZ() {
  return this->z;
}

Vector Vector::operator+(Vector& other) {
  return Vector(this->x + other.GetX(),
    this->y + other.GetY(), this->z + other.GetZ());
} 

Vector Vector::operator-(Vector& other) {
  return Vector(this->x - other.GetX(),
    this->y - other.GetY(), this->z - other.GetZ()); 
}

bool Vector::Equal(Vector& other, float tolerance) {
  return std::abs(this->x - other.GetX()) < tolerance &&
    std::abs(this->y - other.GetY()) < tolerance &&
    std::abs(this->z - other.GetZ()) < tolerance;
}

Vector Vector::Scale(float scalar) {
  return Vector(this->x * scalar, this->y * scalar, this->z * scalar);
}

Vector Vector::DivideByScalar(float scalar) {
  return Vector(this->x / scalar, this->y / scalar, this->z / scalar);
}

Vector Vector::CrossProduct(Vector& other) {
  float iComponent = this->y * other.GetZ() - this->z * other.GetY();
  float jComponent = this->z * other.GetX() - this->x * other.GetZ();
  float kComponent = this->x * other.GetY() - this->y * other.GetX();
  
  return Vector(iComponent, jComponent, kComponent);
}

float Vector::DotProduct(Vector& other) {
  return this->x * other.GetX() +
    this->y * other.GetY() +
    this->z * other.GetZ();
}

float Vector::GetAngle(Vector& other) {
  return acos(this->DotProduct(other) / (this->Norm() * other.Norm()));  
}

float Vector::Norm() {
  return sqrt(this->NormSquared());  
}

float Vector::NormSquared(){
  return this->x * this->x +
    this->y * this->y +
    this->z * this->z;
}

Vector Vector::Negative() {
  return this->Scale(-1);
}

Vector Vector::Normalize() {
  float norm = this->Norm();
  return Vector(this->x / norm, this->y / norm, this->z / norm);
}

Vector Vector::Symmetric(Vector& other) {
  Vector normalized = other.Normalize();
  return normalized.Scale(2 * normalized.DotProduct(*this)) - *this;
}


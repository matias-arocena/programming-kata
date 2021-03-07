#ifndef _VECTOR_H
#define _VECTOR_H

class Vector 
{
  float x;
  float y;
  float z;

public:
  Vector(float x, float y, float z);
  float GetX();
  float GetY();
  float GetZ();
  
  Vector Scale(float scalar);
  Vector DivideByScalar(float scalar);

  Vector operator+(Vector& other);
  Vector operator-(Vector& other);
  Vector Symmetric(Vector& other);
  Vector CrossProduct(Vector& other);

  bool Equal(Vector& other, float tolerance=0.00001f);
  float DotProduct(Vector& other);
  float GetAngle(Vector& other);

  float Norm();
  float NormSquared();
  Vector Negative();
  Vector Normalize();
};

#endif

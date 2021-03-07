#define BOOST_TEST_MODULE test_computer_graphics

#define _USE_MATH_DEFINES

#include <cmath>
#include <boost/test/included/unit_test.hpp>

#include "../computer-graphics/Vector.h"

const float TOLERANCE 0.00001f

BOOST_AUTO_TEST_CASE( test_vector_getters )
{
  Vector a = Vector(-1.4f, 13.4f, 0.0f);
  Vector b = Vector(-3.3f, -132.99f, 15.7f);
 
  BOOST_TEST(std::abs(-1.4f - a.GetX()) < TOLERANCE);
  BOOST_TEST(std::abs(13.4f - a.GetY()) < TOLERANCE);
  BOOST_TEST(std::abs(0.0f - a.GetZ()) < TOLERANCE);
  BOOST_TEST(std::abs(-3.3f - b.GetX()) < TOLERANCE);
  BOOST_TEST(std::abs(-132.99f - b.GetY()) < TOLERANCE);
  BOOST_TEST(std::abs(15.7f - b.GetZ()) < TOLERANCE);
}

BOOST_AUTO_TEST_CASE( test_vector_addition ) {
  Vector a = Vector(-1.4f, 13.4f, 0.0f);
  Vector b = Vector(-3.3f, -132.99f, 15.7f);

  BOOST_TEST(std::abs(-4.7f - (a + b).GetX()) < TOLERANCE);
  BOOST_TEST(std::abs(-119.59 - (a + b).GetY()) < TOLERANCE);
  BOOST_TEST(std::abs(15.7 - (a + b).GetZ()) < TOLERANCE);
}

BOOST_AUTO_TEST_CASE( test_vector_substraction ) {
  Vector a = Vector(-1.4f, 13.4f, 0.0f);
  Vector b = Vector(-3.3f, -132.99f, 15.7f);

  BOOST_TEST(std::abs(1.90f - (a - b).GetX()) < TOLERANCE);
  BOOST_TEST(std::abs(146.39f - (a - b).GetY()) < TOLERANCE);
  BOOST_TEST(std::abs(-15.7f - (a - b).GetZ()) < TOLERANCE);
}

BOOST_AUTO_TEST_CASE( test_vector_scale ) {
  Vector a = Vector(-1.4f, 13.4f, 0.0f);

  Vector expected1 = Vector(0.0f, 0.0f, 0.0f);
  BOOST_TEST(a.Scale(0.0f).Equal(expected1, TOLERANCE));

  Vector expected2 = Vector(2.8f, -26.8f, 0.0f);
  BOOST_TEST(a.Scale(-2.0f).Equal(expected2, TOLERANCE));
}

BOOST_AUTO_TEST_CASE( test_vector_cross_product ) {
  Vector a = Vector(3, 1, 4);
  Vector b = Vector(2, 2, 1);
  Vector aLinearDependent = Vector(3 * 2, 1 * 2, 4 * 2);

  Vector expected1 = Vector(0, 0, 0);
  BOOST_TEST(a.CrossProduct(aLinearDependent).Equal(expected1));

  Vector expected2 = Vector(-7, 5, 4);
  BOOST_TEST(a.CrossProduct(b).Equal(expected2));
} 


BOOST_AUTO_TEST_CASE( test_vector_dot_product ) {
  Vector a = Vector(3, 1, 4);
  Vector b = Vector(2, 2, 1);

  BOOST_TEST(std::abs(12 - a.DotProduct(b)) < TOLERANCE);
}


BOOST_AUTO_TEST_CASE( test_vector_get_angle ) {
  Vector a = Vector(1, 0, 0);
  Vector b = Vector(0, 1, 0);
  Vector c = Vector(2, 0, 0);

  double expected1 = M_PI_2;
  BOOST_TEST(std::abs(a.GetAngle(b) - expected1) < TOLERANCE);

  float expected2 = 0;
  BOOST_TEST(std::abs(a.GetAngle(c) - expected2) < TOLERANCE);
}

BOOST_AUTO_TEST_CASE( test_vector_divide_by_scalar ) {
  Vector a = Vector(12, 4, 8);

  Vector expected = Vector(6, 2, 4);
  BOOST_TEST(a.DivideByScalar(2).Equal(expected));
} 

BOOST_AUTO_TEST_CASE( test_vector_norm ) {
  Vector a = Vector(1, 2, 1);
  
  BOOST_TEST(std::abs(6 - a.NormSquared()) < TOLERANCE);
  BOOST_TEST(std::abs(sqrt(6) - a.Norm()) < TOLERANCE);
}

BOOST_AUTO_TEST_CASE( test_vector_negative ) {
  Vector a = Vector(1, 0, 2);
  Vector expected = Vector(-1, 0, -2);

  BOOST_TEST(a.Negative().Equal(expected));
}

BOOST_AUTO_TEST_CASE( test_vector_normalize ) {
  Vector a = Vector(3, 1, 9);

  Vector normalized = a.Normalize();

  BOOST_TEST(std::abs(1 - normalized.Norm()) < TOLERANCE);
  BOOST_TEST(std::abs(0 - normalized.GetAngle(a)) < TOLERANCE);
}

// TODO: Create test for ProjectilePosition


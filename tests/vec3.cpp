#include <gtest/gtest.h>
#include "../include/vec3.hpp"

using raytracer::vec3;
using raytracer::dot;
using raytracer::cross;
using raytracer::unit;

TEST(Vec3ConstructorTest, DefaultConstructorInitializesToZero) {
    vec3 v;

    EXPECT_DOUBLE_EQ(v.x, 0.0);
    EXPECT_DOUBLE_EQ(v.y, 0.0);
    EXPECT_DOUBLE_EQ(v.z, 0.0);
}

TEST(Vec3ConstructorTest, ParameterizedConstructorSetsValues) {
    vec3 v(1.0, 2.0, 3.0);

    EXPECT_DOUBLE_EQ(v.x, 1.0);
    EXPECT_DOUBLE_EQ(v.y, 2.0);
    EXPECT_DOUBLE_EQ(v.z, 3.0);
}

TEST(Vec3OperatorTest, AdditionAssignment) {
    vec3 a(1.0, 2.0, 3.0);
    vec3 b(4.0, 5.0, 6.0);

    a += b;

    EXPECT_DOUBLE_EQ(a.x, 5.0);
    EXPECT_DOUBLE_EQ(a.y, 7.0);
    EXPECT_DOUBLE_EQ(a.z, 9.0);
}

TEST(Vec3OperatorTest, MultiplicationAssignment) {
    vec3 v(1.0, -2.0, 3.0);

    v *= 2.0;

    EXPECT_DOUBLE_EQ(v.x, 2.0);
    EXPECT_DOUBLE_EQ(v.y, -4.0);
    EXPECT_DOUBLE_EQ(v.z, 6.0);
}

TEST(Vec3OperatorTest, DivisionAssignment) {
    vec3 v(2.0, 4.0, 6.0);

    v /= 2.0;

    EXPECT_DOUBLE_EQ(v.x, 1.0);
    EXPECT_DOUBLE_EQ(v.y, 2.0);
    EXPECT_DOUBLE_EQ(v.z, 3.0);
}

TEST(Vec3OperatorTest, DivisionAssignmentByZeroResetsVector) {
    vec3 v(1.0, 2.0, 3.0);

    v /= 0.0;

    EXPECT_DOUBLE_EQ(v.x, 0.0);
    EXPECT_DOUBLE_EQ(v.y, 0.0);
    EXPECT_DOUBLE_EQ(v.z, 0.0);
}

TEST(Vec3OperatorTest, UnaryMinus) {
    vec3 v(1.0, -2.0, 3.0);

    vec3 result = -v;

    EXPECT_DOUBLE_EQ(result.x, -1.0);
    EXPECT_DOUBLE_EQ(result.y, 2.0);
    EXPECT_DOUBLE_EQ(result.z, -3.0);
}

TEST(Vec3UtilityTest, VectorAddition) {
    vec3 a(1.0, 2.0, 3.0);
    vec3 b(4.0, 5.0, 6.0);

    vec3 result = a + b;

    EXPECT_DOUBLE_EQ(result.x, 5.0);
    EXPECT_DOUBLE_EQ(result.y, 7.0);
    EXPECT_DOUBLE_EQ(result.z, 9.0);
}

TEST(Vec3UtilityTest, VectorSubtraction) {
    vec3 a(5.0, 7.0, 9.0);
    vec3 b(1.0, 2.0, 3.0);

    vec3 result = a - b;

    EXPECT_DOUBLE_EQ(result.x, 4.0);
    EXPECT_DOUBLE_EQ(result.y, 5.0);
    EXPECT_DOUBLE_EQ(result.z, 6.0);
}

TEST(Vec3UtilityTest, VectorMultiplication) {
    vec3 a(1.0, 2.0, 3.0);
    vec3 b(4.0, 5.0, 6.0);

    vec3 result = a * b;

    EXPECT_DOUBLE_EQ(result.x, 4.0);
    EXPECT_DOUBLE_EQ(result.y, 10.0);
    EXPECT_DOUBLE_EQ(result.z, 18.0);
}

TEST(Vec3UtilityTest, ScalarMultiplicationLeft) {
    vec3 v(1.0, 2.0, 3.0);

    vec3 result = 2.0 * v;

    EXPECT_DOUBLE_EQ(result.x, 2.0);
    EXPECT_DOUBLE_EQ(result.y, 4.0);
    EXPECT_DOUBLE_EQ(result.z, 6.0);
}

TEST(Vec3UtilityTest, ScalarMultiplicationRight) {
    vec3 v(1.0, 2.0, 3.0);

    vec3 result = v * 2.0;

    EXPECT_DOUBLE_EQ(result.x, 2.0);
    EXPECT_DOUBLE_EQ(result.y, 4.0);
    EXPECT_DOUBLE_EQ(result.z, 6.0);
}

TEST(Vec3UtilityTest, VectorDivision) {
    vec3 v(2.0, 4.0, 6.0);

    vec3 result = v / 2.0;

    EXPECT_DOUBLE_EQ(result.x, 1.0);
    EXPECT_DOUBLE_EQ(result.y, 2.0);
    EXPECT_DOUBLE_EQ(result.z, 3.0);
}

TEST(Vec3UtilityTest, VectorDivisionByZeroReturnsZeroVector) {
    vec3 v(1.0, 2.0, 3.0);

    vec3 result = v / 0.0;

    EXPECT_DOUBLE_EQ(result.x, 0.0);
    EXPECT_DOUBLE_EQ(result.y, 0.0);
    EXPECT_DOUBLE_EQ(result.z, 0.0);
}

TEST(Vec3UtilityTest, DotProduct) {
    vec3 a(1.0, 2.0, 3.0);
    vec3 b(4.0, 5.0, 6.0);

    double result = dot(a, b);

    EXPECT_DOUBLE_EQ(result, 32.0);
}

TEST(Vec3UtilityTest, CrossProduct) {
    vec3 a(1.0, 0.0, 0.0);
    vec3 b(0.0, 1.0, 0.0);

    vec3 result = cross(a, b);

    EXPECT_DOUBLE_EQ(result.x, 0.0);
    EXPECT_DOUBLE_EQ(result.y, 0.0);
    EXPECT_DOUBLE_EQ(result.z, 1.0);
}

TEST(Vec3UtilityTest, LengthSquared) {
    vec3 v(1.0, 2.0, 2.0);

    EXPECT_DOUBLE_EQ(v.length_squared(), 9.0);
}

TEST(Vec3UtilityTest, Length) {
    vec3 v(1.0, 2.0, 2.0);

    EXPECT_DOUBLE_EQ(v.length(), 3.0);
}

TEST(Vec3UtilityTest, UnitVector) {
    vec3 v(0.0, 3.0, 4.0);

    vec3 result = unit(v);

    EXPECT_NEAR(result.x, 0.0, 1e-9);
    EXPECT_NEAR(result.y, 0.6, 1e-9);
    EXPECT_NEAR(result.z, 0.8, 1e-9);
}


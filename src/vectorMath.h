
#ifndef VECMATH_H
#define VECMATH_H

#include <SFML/Graphics.hpp>
#include <cmath>

namespace VecMath {

inline static float dotProduct(sf::Vector2f A, sf::Vector2f B) {
	return (A.x * B.x) + (A.y * B.y);
}

inline static float length(sf::Vector2f A) {
	return std::sqrt(std::pow(A.x, 2) + std::pow(A.y, 2));
}

inline static float calculateAngleRad(sf::Vector2f A, sf::Vector2f B) {
	float dot_product = dotProduct(A, B);
	return std::acos(dot_product / (length(A) * length(B)));
}

inline static float calculateAngle(sf::Vector2f A, sf::Vector2f B) {
	return calculateAngleRad(A, B) * 180 / M_PI;
}

inline static float toRadians(float degreeAngle) {
	return degreeAngle * M_PI / 180;
}

inline static float toDegree(float radAngle) {
	return radAngle * 180 / M_PI;
}


}

#endif

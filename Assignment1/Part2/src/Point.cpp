#include "Point.h"

// Default Constructor
Point::Point() : x{ 0 }, y{ 0 }, z{ 0 } {
	cout << "Point Object Created with Default Coordinates x = " << x << ", y = " << y << ", z = " << z << endl;
}

// Constructor
Point::Point(int xVal, int yVal, int zVal) : x{ xVal }, y{ yVal }, z{ zVal } {
	cout << "Point Object Created with Coordinates x = " << x << ", y = " << y << ", z = " << z << endl;
}

// Destructor
Point::~Point() {
	cout << "Point Object Destroyed" << endl;
}

// Getters & Setters
int Point::getX() const {
	return x;
}

void Point::setX(int xVal) {
	x = xVal;
}

int Point::getY() const {
	return y;
}

void Point::setY(int yVal) {
	y = yVal;
}

int Point::getZ() const {
	return z;
}

void Point::setZ(int zVal) {
	z = zVal;
}

// Displays the coordinates of tthe Point.
string Point::display() const {
	string coordinates = "(" + to_string(x) + ", " + to_string(y) + ", " + to_string(z) + ")";
	return coordinates;
}

// Moves the Point along a specified axis by distance 'd'.
int Point::translate(int d, char axis) {
	switch (axis) {
	case 'x':
		x += d;
		return 0;
	case 'y':
		y += d;
		return 0;
	case 'z':
		z += d;
		return 0;
	default:
		return -1;
	}
}
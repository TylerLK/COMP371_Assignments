#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <cmath>
#include <iostream>

#include "Point.h"

using namespace std;

class Triangle {
public:
    // Default Constructor
    // Creates an object of type Triangle (No arguments passed).
    Triangle();

    // Constructor
    // Creates an object of type Triangle (Arguments passed).
    Triangle(Point p1, Point p2, Point p3);

    // Copy Constructor
    // Creates an object of type Triangle (Object of type Triangle Passed).
	// The new object of type Triangle is an independent copy of passed object of type Triangle.
    Triangle(const Triangle& other);

    // Copy Assignment Operator
    // Replacing an object of type Triangle with another object of type Triangle.
    Triangle& operator=(const Triangle& other);

    // Destructor
    ~Triangle();

    // Getters & Setters
    Point* getVertex1() const;
    void setVertex1(Point p);

    Point* getVertex2() const;
    void setVertex2(Point p);

    Point* getVertex3() const;
    void setVertex3(Point p);

    // Displays the vertices of the Triangle.
    void display() const;

    // Moves the Traingle's vertices along a specified axis by distance 'd'.
    int translate(int d, char axis);

    double calcArea() const;

private:
    Point *vertex_1, *vertex_2, *vertex_3;
};

#endif
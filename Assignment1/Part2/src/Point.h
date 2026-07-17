#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <string>

using namespace std;

class Point {
public:
    // Default Constructor
    Point();

    // Constructor
    Point(int xVal, int yVal, int zVal);

    // Destructor
    ~Point();

    // Getters & Setters
    int getX() const;
    void setX(int xVal);

    int getY() const;
    void setY(int yVal);

    int getZ() const;
    void setZ(int zVal);

    // Displays the coordinates of tthe Point.
    string display() const;

    // Moves the Point along a specified axis by distance 'd'.
    int translate(int d, char axis);

private:
    int x, y, z;
};

#endif
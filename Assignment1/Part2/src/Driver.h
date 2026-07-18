#include "Triangle.h"
#include <iostream>
using namespace std;

class Driver {
public:
    // Constructor
    Driver();

    // Copy Constuctor
	// Creates an object of Type Driver (Object of type Driver Passed).
	// The new object of type Driver is an independent copy of passed object of type Driver.
    Driver(const Driver& other);

    // Copy Assignment Operator
    // Replacing an object of type Driver with another object of type Driver.
	Driver& operator=(const Driver& other);

    // Destructor
    ~Driver();

    // Getters and Setters
    Triangle* getTriangle() const;
    void setTriangle(const Triangle& t);

    // Creates a Triangle object that can be manipulated by the user.
    void createTriangle(const Point& p1, const Point& p2, const Point& p3);

    // Translates the triangle by distance 'd' along a provided axis.
    void translate(int d, char axis);

    // Displays the triangle's vertices.
    void display() const;

    // Calculates the triangle's area.
	double calcTriangleArea() const;

    // Prints the Driver Menu
    int showMenu() const;

    // Runs whichever action the choice maps to.
    // Cancels loop when user enters 'Exit' option
    bool executeChoice(int choice);

private:
    Triangle* triangle;
};
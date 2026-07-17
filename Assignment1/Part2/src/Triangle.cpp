#include "Triangle.h"

// Default Constructor
Triangle::Triangle() {
    vertex_1 = nullptr;
    vertex_2 = nullptr;
    vertex_3 = nullptr;
}

// Constructor
Triangle::Triangle(Point p1, Point p2, Point p3) : vertex_1(nullptr), vertex_2(nullptr), vertex_3(nullptr) {
    setVertex1(p1);
    setVertex2(p2);
    setVertex3(p3);
}

// Copy Constructor
Triangle::Triangle(const Triangle& other) : vertex_1(nullptr), vertex_2(nullptr), vertex_3(nullptr) {
    if (other.vertex_1) {
        vertex_1 = new Point(*other.vertex_1);
    }
    if (other.vertex_2) {
        vertex_2 = new Point(*other.vertex_2);
    }
    if (other.vertex_3) {
        vertex_3 = new Point(*other.vertex_3);
    }
}

// Copy Assignment Operator
Triangle& Triangle::operator=(const Triangle& other) {
    if (this != &other) {
        // Delete any pre-allocated memory associated to the current object's vertices.
        delete vertex_1;
        delete vertex_2;
        delete vertex_3;

        // Allocate memory for the current object's vertices with another object's vertices.
        if (other.vertex_1) {
            vertex_1 = new Point(*other.vertex_1);
        }
        if (other.vertex_2) {
            vertex_2 = new Point(*other.vertex_2);
        }
        if (other.vertex_3) {
            vertex_3 = new Point(*other.vertex_3);
        }
    }

    return *this;
}

// Destructor
Triangle::~Triangle() {
    // De-allocate memory for the triangle's vertices.
    delete vertex_1;
    delete vertex_2;
    delete vertex_3;

    cout << "Triangle Object Destroyed" << endl;
}

// Getters & Setters
Point* Triangle::getVertex1() const {
    return vertex_1;
}

void Triangle::setVertex1(Point p) {
    // Delete any pre-allocated memory associated to vertex_1.
    delete vertex_1;

    // Allocate memory for vertex_1 associated to the input Point.
    vertex_1 = new Point(p.getX(), p.getY(), p.getZ());
}

Point* Triangle::getVertex2() const {
    return vertex_2;
}

void Triangle::setVertex2(Point p) {
    // Delete any pre-allocated memory associated to vertex_2.
    delete vertex_2;

    // Allocate memory for vertex_2 associated to the input Point.
    vertex_2 = new Point(p.getX(), p.getY(), p.getZ());
}

Point* Triangle::getVertex3() const {
    return vertex_3;
}

void Triangle::setVertex3(Point p) {
    // Delete any pre-allocated memory associated to vertex_3.
    delete vertex_3;

    // Allocate memory for vertex_3 associated to the input Point.
    vertex_3 = new Point(p.getX(), p.getY(), p.getZ());
}

// Displays the vertices of the Triangle.
void Triangle::display() const {
    // Check for null pointers before attempting to display the triangle's vertices.
    if (vertex_1 == nullptr || vertex_2 == nullptr || vertex_3 == nullptr) {
        return;
    }
    
    cout << "Vertex 1: " << (*vertex_1).display() << endl;
    cout << "Vertex 2: " << (*vertex_2).display() << endl;
    cout << "Vertex 3: " << (*vertex_3).display() << endl;
}

// Moves the Traingle's vertices along a specified axis by distance 'd'.
int Triangle::translate(int d, char axis) {
    // Check for null pointers before attemption to translate the triangle's vertices.
    if (vertex_1 == nullptr || vertex_2 == nullptr || vertex_3 == nullptr) {
        return -1;
    }

    vertex_1->translate(d, axis);
    vertex_2->translate(d, axis);
    vertex_3->translate(d, axis);
    return 0;
}

double Triangle::calcArea() const {
    // Check for null pointers before attempting to calculate the area of the triangle.
    if (vertex_1 == nullptr || vertex_2 == nullptr || vertex_3 == nullptr) {
        return -1;
    }

    // Two vectors can be calculated from the three vertices of the triangle.
    // vector_1 = vertex_2 - vertex_1
    Point vector_1 = Point((vertex_2->getX() - vertex_1->getX()), (vertex_2->getY() - vertex_1->getY()), (vertex_2->getZ() - vertex_1->getZ()));
    // vector_2 = vertex_3 - vertex_1
    Point vector_2 = Point((vertex_3->getX() - vertex_1->getX()), (vertex_3->getY() - vertex_1->getY()), (vertex_3->getZ() - vertex_1->getZ()));

    // Store the cross product of vector_1 & vector_2 in vector_3.
    Point vector_3 = Point(((vector_1.getY() * vector_2.getZ()) - (vector_1.getZ() * vector_2.getY())), ((vector_1.getZ() * vector_2.getX()) - (vector_1.getX() * vector_2.getZ())), ((vector_1.getX() * vector_2.getY()) - (vector_1.getY() * vector_2.getX())));

    // Calculate the area of the Triangle.
    // This is expressed as half the magnitude of vector_3.
    double area = 0.5 * sqrt(pow(vector_3.getX(), 2) + pow(vector_3.getY(), 2) + pow(vector_3.getZ(), 2));

    return area;
}
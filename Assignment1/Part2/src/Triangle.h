#include <cmath>

#include "Point.h"

class Triangle {
public:
    // Default Constructor
    Triangle() {
        vertex_1 = nullptr;
        vertex_2 = nullptr;
        vertex_3 = nullptr;
    }

    // Constructor
    Triangle(Point p1, Point p2, Point p3) {
        setVertex1(p1);
        setVertex2(p2);
        setVertex3(p3);
    }

    // Destructor
    ~Triangle() {
        // De-allocate memory for the triangle's vertices.
        if (vertex_1 != nullptr) {
            delete vertex_1;
        }
        if (vertex_2 != nullptr) {
            delete vertex_2;
        }
        if (vertex_3 != nullptr) {
            delete vertex_3;
        }

        cout << "Triangle Object Destroyed" << endl;
    }

    // Getters & Setters
    Point* getVertex1() { return vertex_1; }
    void setVertex1(Point p) {
        // Delete any pre-allocated memory associated to vertex_1.
        if (vertex_1 != nullptr) {
            //delete vertex_1;
        }

        // Allocate memory for vertex_1 associated to the input Point.
        vertex_1 = new Point(p.getX(), p.getY(), p.getZ());
    }

    Point* getVertex2() { return vertex_2; }
    void setVertex2(Point p) {
        if (vertex_2 != nullptr) {
            //delete vertex_2;
        }
        vertex_2 = new Point(p.getX(), p.getY(), p.getZ());
    }

    Point* getVertex3() { return vertex_3; }
    void setVertex3(Point p) {
        if (vertex_3 != nullptr) {
            //delete vertex_3;
        }
        vertex_3 = new Point(p.getX(), p.getY(), p.getZ());
    }

    // Displays the vertices of the Triangle.
    void display() {
        cout << "Vertex 1: " << (*vertex_1).display() << endl;
        cout << "Vertex 2: " << (*vertex_2).display() << endl;
        cout << "Vertex 3: " << (*vertex_3).display() << endl;
    }

    // Moves the Traingle's vertices along a specified axis by distance 'd'.
    int translate(int d, char axis) {

        // Moves the Traingle's vertices along a specified axis by distance 'd'.
        int translate(int d, char axis) {
            // Check for null pointers before attemption to translate the triangle's vertices.
			if(vertex_1 == nullptr || vertex_2 == nullptr || vertex_3 == nullptr) {
				return -1;
			}
            
            vertex_1->translate(d, axis);
            vertex_2->translate(d, axis);
            vertex_3->translate(d, axis);
            return 0;
        }

        double calcArea() {
			// Check for null pointers before attempting to calculate the area of the triangle.
            if(vertex_1 == nullptr || vertex_2 == nullptr || vertex_3 == nullptr) {
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
    }

    double calcArea() {
        // TODO: Implement a method that calculates the area of the triangle using the coordinates of its vertices.
        return 0;
    }

    private:
        Point *vertex_1, *vertex_2, *vertex_3;
};

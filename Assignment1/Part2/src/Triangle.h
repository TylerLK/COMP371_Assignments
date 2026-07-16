#include "Point.h"

using namespace std;

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
                delete vertex_1;
            }

            // Allocate memory for vertex_1 associated to the input Point.
            vertex_1 = new Point(p.getX(), p.getY(), p.getZ());
        }

		Point* getVertex2() { return vertex_2; }
		void setVertex2(Point p) { 
            if (vertex_2 != nullptr) {
                delete vertex_2;
            }
            vertex_2 = new Point(p.getX(), p.getY(), p.getZ());
        }

		Point* getVertex3() { return vertex_3; }
		void setVertex3(Point p) {
            if (vertex_3 != nullptr) {
                delete vertex_3;
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
            vertex_1->translate(d, axis);
            vertex_2->translate(d, axis);
            vertex_3->translate(d, axis);
            return 0;
        }

        double calcArea() {
			// TODO: Implement a method that calculates the area of the triangle using the coordinates of its vertices.
        }

    private:
        Point *vertex_1, *vertex_2, *vertex_3;
}
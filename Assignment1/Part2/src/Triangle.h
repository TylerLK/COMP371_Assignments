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
            cout << "Triangle Object Destroyed" << endl;
        }

        // Getters & Setters
		Point* getVertex1() { return vertex_1; }
		void setVertex1(Point p) { *vertex_1 = new Point(p->getX(), p->getY(), p->getZ()); }

		Point* getVertex2() { return vertex_2; }
		void setVertex2(Point p) { *vertex_2 = new Point(p->getX(), p->getY(), p->getZ()); }

		Point* getVertex3() { return vertex_3; }
		void setVertex3(Point p) { *vertex_3 = new Point(p->getX(), p->getY(), p->getZ()); }

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
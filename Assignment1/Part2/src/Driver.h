#include "Triangle.h"
using namespace std;

class Driver {
public:
	// Constructor
	Driver() : triangle(nullptr) {}

	void translate(int d, char axis) {
		if (triangle != nullptr) {
			triangle->translate(d, axis);
		}
	}

	~Driver() {
		delete triangle;
	}

	void createTriangle(Point p1, Point p2, Point p3) {
		triangle = new Triangle(p1, p2, p3);
	}

	void display() {
		if (triangle != nullptr) { triangle->display(); }
	}
private:
	Triangle* triangle;
};

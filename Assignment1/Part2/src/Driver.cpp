#include "Driver.h"

// Constructor
Driver::Driver() : triangle(nullptr) { }

//CopyConstructor
Driver::Driver(const Driver& other) : triangle(nullptr) {
    if (other.triangle) {
		triangle = new Triangle(*other.triangle);
    }
}

// Copy Assignment Operator
Driver& Driver::operator=(const Driver& other) {
    if (this != &other) {
        // Delete any pre-allocated memory associated to the current object's triangle.
        delete triangle;

		// Ensure the triangle pointer is not dangling.
		triangle = nullptr;

        // Allocate memory for the current object's triangle with another object's triangle.
        if (other.triangle) {
            triangle = new Triangle(*other.triangle);
        }
    }

    return *this;
}

// Destructor
Driver::~Driver() {
    delete triangle;
}

// Getters & Setters
Triangle* Driver::getTriangle() const {
    return triangle;
}

void Driver::setTriangle(const Triangle& t) {
    // Delete any pre-allocated memory associated to triangle.
    delete triangle;

    // Allocate memory for triangle associated to the input Triangle.
    triangle = new Triangle(t);
}

// Creates a Triangle object that can be manipulated by the user.
void Driver::createTriangle(const Point& p1, const Point& p2, const Point& p3) {
	// Delete the current Triangle object before creating a new one.
	delete triangle;
    
    triangle = new Triangle(p1, p2, p3);

    cout << "\nTriangle created successfully!" << endl << "Vertices:" << endl;

    display();
}

// Translates the triangle by distance 'd' along a provided axis.
void Driver::translate(int d, char axis) {
    if (triangle != nullptr) {
        triangle->translate(d, axis);
        display();
    }
}

// Displays the triangle's vertices.
void Driver::display() const {
    if (triangle != nullptr) {
        triangle->display();
    }
    else {
        cout << "No triangle exists yet. Create one first." << endl;
    }
}

// Calculates the triangle's area.
double Driver::calcTriangleArea() const {
    return triangle->calcArea();
}

// Prints the Driver Menu
int Driver::showMenu() const {
    cout << "\n========= Triangle Menu =========" << endl;
    cout << "1. Create Triangle" << endl;
    if (triangle != nullptr) {
        cout << "2. Translate Triangle" << endl;
        cout << "3. Display Triangle Coordinates" << endl;
        cout << "4. Calculate Triangle Area" << endl;
        cout << "5. Exit" << endl;
    }
    else {
		cout << "2. Exit" << endl;
    }
	cout << "=================================" << endl;
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    return choice;
}

// Runs whichever action the choice maps to.
bool Driver::executeChoice(int choice) {
    switch (choice) {
    case 1: {
        int x1, y1, z1, x2, y2, z2, x3, y3, z3;
        cout << "Vertex 1 (EX: 2 4 6): ";
        cin >> x1 >> y1 >> z1;
        cout << "Vertex 2 (EX: 1 8 5): ";
        cin >> x2 >> y2 >> z2;
        cout << "Vertex 3 (EX: 4 3 9): ";
        cin >> x3 >> y3 >> z3;
        createTriangle(Point(x1, y1, z1), Point(x2, y2, z2), Point(x3, y3, z3));
        break;
    }
    case 2: {
        if (triangle != nullptr) {
            int d; char axis;
            cout << "Distance: ";
            cin >> d;
            cout << "Axis (x/y/z): ";
            cin >> axis;
            translate(d, axis);
        }
        else {
            cout << "Exiting..." << endl;
            return false;
        }
        break;
    }
    case 3:
        display(); // Diplays Coordinates
        break;
    case 4:
        cout << "Area of Triangle: " << calcTriangleArea() << endl;
        break;
    case 5:
        cout << "Exiting..." << endl;
        return false;
    default: // If none of the options
        cout << "Invalid choice, try again" << endl;
    }
    return true;
}
#include "Triangle.h"
#include <iostream>
using namespace std;

class Driver {
public:
    Driver() : triangle(nullptr) {}
    ~Driver() { delete triangle; }

    void createTriangle(Point p1, Point p2, Point p3) {
        triangle = new Triangle(p1, p2, p3);
        display();
    }
    void translate(int d, char axis) {
        if (triangle != nullptr) {
            triangle->translate(d, axis);
            display();
        }
    }
    void display() {
        if (triangle != nullptr) {
            triangle->display();
        }
        else {
            cout << "No triangle exists yet. Create one first." << endl;
        }
    }
    double calcTriangleArea() {
        return triangle->calcArea();
    }

    // Prints the Driver Menu
    int showMenu() {
        cout << "\n===== Triangle Menu =====" << endl;
        cout << "1. Create Triangle" << endl;
        cout << "2. Translate Triangle" << endl;
        cout << "3. Display Triangle Coordinates" << endl;
        cout << "4. Calculate Triangle Area" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        return choice;
    }

    // Runs whichever action the choice maps to.
    // Cancels loop when user enters 'Exit' option
    bool executeChoice(int choice) {
        switch (choice) {
        case 1: {
            int x1, y1, z1, x2, y2, z2, x3, y3, z3;
            cout << "Vertex 1 (x y z): "; 
            cin >> x1 >> y1 >> z1;
            cout << "Vertex 2 (x y z): "; 
            cin >> x2 >> y2 >> z2;
            cout << "Vertex 3 (x y z): "; 
            cin >> x3 >> y3 >> z3;
            createTriangle(Point(x1, y1, z1), Point(x2, y2, z2), Point(x3, y3, z3));
            break;
        }
        case 2: {
            int d; char axis;
            cout << "Distance: "; 
            cin >> d;
            cout << "Axis (x/y/z): "; 
            cin >> axis;
            translate(d, axis);
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

private:
    Triangle* triangle;
};
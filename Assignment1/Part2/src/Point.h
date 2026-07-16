#include <iostream>
#include <string>

using namespace std;

class Point{
    public:
        // Default Constructor
        Point() : x{ 0 }, y{ 0 }, z{ 0 } {
            cout << "Point Object Created with Default Coordinates x = " << x << ", y = " << y << ", z = " << z << endl;
        }

        // Constructor
        Point(int xVal, int yVal, int zVal) : x{ xVal }, y{ yVal }, z{ zVal } {
            cout << "Point Object Created with Coordinates x = " << x << ", y = " << y << ", z = " << z << endl;
        }

        // Destructor
        ~Point() {
            cout << "Point Object Destroyed" << endl;
        }

        // Getters & Setters
		int getX() { return x; }
		void setX(int xVal) { x = xVal; }

		int getY() { return y; }
		void setY(int yVal) { y = yVal; }

		int getZ() { return z; }
		void setZ(int zVal) { z = zVal; }

        // Displays the coordinates of tthe Point.
        string display() {
			string coordinates = "(" + to_string(x) + ", " + to_string(y) + ", " + to_string(z) + ")";
			return coordinates;
        }

        // Moves the Point along a specified axis by distance 'd'.
        int translate(int d, char axis) {
            switch (axis) {
                case 'x':
                    x = x + d;
                    return 0;
                case 'y':
                    y = y + d;
                    return 0;
                case 'z':
                    z = z + d;
                    return 0;
                default:
                    return -1;
            }
        }

    private:
        int x, y, z;
}
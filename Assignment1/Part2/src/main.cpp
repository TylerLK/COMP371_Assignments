#include <iostream>

#include "Driver.h"

using namespace std;

int main() {
    Driver d;
    bool running = true;
    while (running) {
        int choice = d.showMenu();
        running = d.executeChoice(choice);
    }
    return 0;
}
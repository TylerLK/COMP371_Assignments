#ifndef DRIVER_H
#define DRIVER_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Driver {
public:
	// Default Constructor
    Driver();

    // Constructor
    Driver(const glm::vec3 initalPos);

    // Destructor
    ~Driver();

    // Builds the current model matrix from translation/rotation/scale state.
    // Combine translation, rotationAngle, and scaleFactor into a single glm::mat4 (see glm::translate / glm::rotate / glm::scale).
    glm::mat4 getModelMatrix() const;

    void processInput(GLFWwindow* window);

private:
    // ---- state ----
    glm::vec3 translation;
    float rotationAngle;   // degrees
    glm::vec3 scaleFactor;

    // Per Frame, Need a Low Number Scaling Factor
    float d = 0.01f;   // translation distance per key press
    float s = 0.15f;   // scale factor per key press

    // Guards against multiple key pressed for Rotation & Scaling
    bool qWasPressed = false;
    bool eWasPressed = false;
    bool rWasPressed = false;
    bool fWasPressed = false;
};

#endif
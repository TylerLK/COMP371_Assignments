#include "Driver.h"
#include <glm/gtc/matrix_transform.hpp>

// Default Constructor
Driver::Driver() : translation(0.0f, 0.0f, 0.0f), rotationAngle(0.0f), scaleFactor(1.0f, 1.0f, 1.0f) {}

//Constructor
Driver::Driver(const glm::vec3 initalPos, const float initialRotAngle) : translation(initalPos), rotationAngle(initialRotAngle), scaleFactor(1.0f, 1.0f, 1.0f) { }

// Destructor
Driver::~Driver() { }

glm::mat4 Driver::getModelMatrix() const {
    glm::mat4 model = glm::mat4(1.0f);

    // Apply translation, rotation, and scale to `model` here.
    model = glm::translate(model, translation);
	model = glm::rotate(model, glm::radians(rotationAngle), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, scaleFactor);

    return model;
}

void Driver::processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    /*
        W = Translate Up
        S = Translate Down
        A = Translate Left
        D = Translate Right

        These fire every frame the key is held
    */

    // Translate up by d
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        translation.y += d;

    }

    // Translate down by d
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        translation.y -= d;
    }

    // Translate left by d
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
       translation.x -= d;
    }

    // Translate right by d
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        translation.x += d;
    }

/*  
    Q = Rotate Counter Clockwise Around Z Axis-- 30 degrees
    E = Rotate Clockwise Around Z Axis -- 30 degrees
    R = Scale Up by factor S in +z direction
    F = Scale Down by factor S in -z direction

    These apply ONCE per press, not every frame while held
*/
    bool qIsPressed = glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS;
    if (qIsPressed && !qWasPressed) {
        // Rotate 30 degrees anticlockwise
		rotationAngle += r;
    }
    qWasPressed = qIsPressed;

    bool eIsPressed = glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS;
    if (eIsPressed && !eWasPressed) {
        // Rotate 30 degrees clockwise
		rotationAngle -= r;
    }
    eWasPressed = eIsPressed;

    bool rIsPressed = glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS;
    if (rIsPressed && !rWasPressed) {
        // Scale up direction by factor s
		scaleFactor *= s;
    }
    rWasPressed = rIsPressed;

    bool fIsPressed = glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS;
    if (fIsPressed && !fWasPressed) {
        // Scale down direction by factor s
		scaleFactor /= s;
    }
    fWasPressed = fIsPressed;
}
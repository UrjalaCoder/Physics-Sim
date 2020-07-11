#ifndef CAMERA
#define CAMERA


#include <iostream>
#include "../../lib/glm/glm/gtc/type_ptr.hpp"
#include "../../lib/glm/glm/glm.hpp"

enum MOVE_DIRECTION {
    FORWARD,
    LEFT,
    RIGHT,
    BACKWARD
};

class Camera
{
private:
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 front = glm::vec3(0, 0, -1);
    glm::vec3 up = glm::vec3(0, 1, 0);
    float yaw = -90.0f;
    float pitch = 0;
    glm::vec3 direction;
    bool firstMove = true;
public:
    glm::mat4 getView();
    void handleInput(MOVE_DIRECTION direction, double delta);
    void updateDirection(double xoff, double yoff);
};

#endif
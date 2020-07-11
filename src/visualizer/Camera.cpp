#include "./Camera.h"

glm::mat4 Camera::getView()
{
    return glm::lookAt(this->position, this->position + this->front, this->up);
};

void Camera::handleInput(MOVE_DIRECTION direction, double delta)
{   
    std::cout << delta << std::endl;
    const float speed = 0.1 * delta;
    glm::vec3 right = glm::normalize(glm::cross(this->front, this->up));
    switch (direction)
    {
    case FORWARD:
        this->position += speed * this->front;
        break;
    case BACKWARD:
        this->position -= speed * this->front;
        break;
    case LEFT:
        this->position -= speed * right;
        break;
    case RIGHT:
        this->position += speed * right;
    default:
        break;
    }
}
#include "./Camera.h"

glm::mat4 Camera::getView()
{
    return glm::lookAt(this->position, this->position + this->front, this->up);
};

void Camera::updateDirection(double xoff, double yoff)
{
    double xoffset = xoff;
    double yoffset = -yoff;
    if(firstMove)
    {
        xoffset = 0;
        yoffset = 0;
        firstMove = false;
    }

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    pitch = pitch > 89.0f ? 89.0f : pitch;
    pitch = pitch < -89.0f ? -89.0f : pitch;

    direction.x = glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
    direction.y = glm::sin(glm::radians(pitch));
    direction.z = glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
    this->front = glm::normalize(direction);
}

void Camera::handleInput(MOVE_DIRECTION direction, double delta)
{   
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
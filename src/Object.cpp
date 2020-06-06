#include "./Object.h"

Object::Object(glm::vec3 pos, glm::dquat rot, OBJECT_SHAPE shape)
{
    this->position = pos;
    this->rotation = rot;

    // Initialize the vertex vector.
    switch (shape)
    {
    case CUBE:
        this->initCube(1.0);
        break;
    
    default:
        break;
    }
}

// Function for initializing the vertices for shape CUBE:
// Scale each vertex by 'scale'.
void Object::initCube(double scale)
{
    double centerX = this->position.x;
    double centerY = this->position.y;
    double centerZ = this->position.z;

    std::vector<glm::vec3> vertices;
    vertices.reserve(8);

    // Start from top layer on the top left and then clockwise.
    double halfScale = scale / 2.0;
    double upperZ = halfScale + centerZ;
    vertices[0] = glm::vec3(centerX - halfScale, centerY + halfScale, upperZ);
    vertices[1] = glm::vec3(centerX + halfScale, centerY + halfScale, upperZ);
    vertices[2] = glm::vec3(centerX + halfScale, centerY - halfScale, upperZ);
    vertices[3] = glm::vec3(centerX - halfScale, centerY - halfScale, upperZ);

    // The bottom
    double lowerZ = centerZ - halfScale;
    vertices[4] = glm::vec3(centerX - halfScale, centerY + halfScale, lowerZ);
    vertices[5] = glm::vec3(centerX + halfScale, centerY + halfScale, lowerZ);
    vertices[6] = glm::vec3(centerX + halfScale, centerY - halfScale, lowerZ);
    vertices[7] = glm::vec3(centerX - halfScale, centerY - halfScale, lowerZ);

    // Assert that the vertices have not been initialized yet.
    assert(this->vertices.size() == 0);
    // Now we have the required vertices, now we just copy them
    for(int i = 0; i < 8; ++i)
    {
        this->vertices.push_back(vertices[i]);
    }
}

// Get a string representation of an object.
std::string Object::toString()
{
    
}
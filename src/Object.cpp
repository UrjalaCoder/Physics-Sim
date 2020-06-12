#include "./Object.h"

// Initialize the static variables.
unsigned int Object::ObjectCount = 0;

Object::Object(glm::vec3 pos, glm::dquat rot, OBJECT_SHAPE shape)
{
  this->position = pos;
  this->rotation = rot;
  this->id = Object::ObjectCount + 1;
  Object::ObjectCount += 1;

  this->shape = shape;
  // Initialize the vertex vector.
  switch (shape)
  {
  case CUBE:
    this->vertexCount = 8;
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
  vertices.reserve(this->vertexCount);

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

  // Initialize the vertices to be 0-vectors:
  for(int i = 0; i < this->vertexCount; ++i)
  {
    this->vertices.push_back(glm::vec3());
  }
  // Now we have the required vertices, now we just copy them
  for(int i = 0; i < this->vertexCount; ++i)
  {
    this->vertices[i] = vertices[i];
  }
}

// Get a string representation of an object.
std::string Object::toString()
{
  std::string resultStr = "";
  // Basic info
  std::string shapeStr = "";
  switch (this->shape)
  {
  case CUBE:
    shapeStr = "CUBE";
    break;
  default:
    shapeStr = "GENERAL";
    break;
  }
  resultStr += ("ID: " + std::to_string(this->id) + " SHAPE: " + shapeStr + "\n");

  // Vertices
  resultStr += "VERTICES\n";
  for(auto &v : this->vertices)
  {
    double x = v.x, y = v.y, z = v.z;
    resultStr += "X: " + std::to_string(x) + " ";
    resultStr += "Y: " + std::to_string(y) + " ";
    resultStr += "Z: " + std::to_string(z) + "\n";
  }

  return resultStr;
}
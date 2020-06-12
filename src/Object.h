#ifndef OBJECT
#define OBJECT

#include <iostream>
#include <vector>
#include <string>

#include "../lib/glm/glm/glm.hpp"
#include "../lib/glm/glm/gtc/quaternion.hpp"

/*
* Simple class for an object.
*/

enum OBJECT_SHAPE
{
  CUBE,
  RECT
};

class Object
{
private:
  void initCube(double scale);
  unsigned int id;
  int vertexCount;
public:
  OBJECT_SHAPE shape;
  Object(
    glm::vec3 initialPosition = glm::vec3(0, 0, 0),
    glm::dquat initialRotation = glm::dquat(),
    OBJECT_SHAPE shape = CUBE
  );
  glm::vec3 position;
  glm::dquat rotation;
  std::vector<glm::vec3> vertices;
  std::string toString();
  static unsigned int ObjectCount;
};

#endif

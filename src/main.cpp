#include <iostream>
#include <vector>

#include "./Object.h"
#include "./visualizer/Visualizer.h"

int main(int argvc, const char** argv)
{
  Object myObj(glm::vec3(0, 0, 0));
  Object myObj2(glm::vec3(0, 2, 0));
  Visualizer vis(1280, 720);
  std::vector<Object> entities;
  entities.push_back(myObj);
  entities.push_back(myObj2);
  vis.setEntities(entities);
  vis.start();

  return 0;
}

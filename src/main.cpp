#include <iostream>
#include <vector>

#include "./Object.h"
#include "./visualizer/Visualizer.h"

int main(int argvc, const char** argv)
{
  Object myObj(glm::vec3(0, 0, 0));
  Visualizer vis(1280, 720);
  std::vector<Object> entities;
  entities.push_back(myObj);
  vis.setEntities(entities);
  vis.start();

  return 0;
}

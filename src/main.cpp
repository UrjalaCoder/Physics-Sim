#include <iostream>
#include <vector>

#include "./Object.h"
#include "./visualizer/Visualizer.h"

int main(int argvc, const char** argv)
{
  std::cout << "Hello, world!" << std::endl;
  Object myObj(glm::vec3(0, -1, 1));
  std::string s = myObj.toString();
  std::cout << myObj.toString() << std::endl;

  Visualizer vis(640, 480);
  vis.start();
  return 0;
}

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

  std::vector<Object> entities;
  entities.push_back(myObj);

  MeshData mesh = vis.calculateMeshVertices(myObj);

  std::vector<int> vertexIndices = mesh.second;

  for(int i = 0; i < vertexIndices.size() / 3; ++i)
  {
    std::cout << vertexIndices[i * 3] << " " << vertexIndices[(i * 3) + 1] << " " << vertexIndices[(i * 3) + 2] << std::endl;
  }

  return 0;
}

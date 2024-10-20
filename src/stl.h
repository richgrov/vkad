#ifndef VKAD_STL_H_
#define VKAD_STL_H_

#include "math/vec3.h"
#include <ostream>
#include <vector>

namespace vkad {

struct Triangle {
   Vec3 points[3];
   Vec3 normal;
};

void write_stl(const std::string &name, const std::vector<Triangle> triangles, std::ostream &out);

} // namespace vkad

#endif // !VKAD_STL_H_

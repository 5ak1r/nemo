#include "../math/transform.hpp"

namespace graphics {

class Camera {
public:
  Camera() : fov(0) {}
  Camera(float f) : fov(f) {}

  float fov;
  float speed = 1.5f;

  math::Transform transform;
};

} // namespace graphics
#include "../math/transform.hpp"

namespace graphics {

class Camera {
public:
  Camera() : fov(0) {}
  Camera(float f) : fov(f) {}

  float getFov() const { return fov; }
  float getSens() const { return sens; }
  float getSpeed() const { return speed; }

  void setFov(float f) { fov = f; }
  void setSens(float s) { sens = s; }
  void setSpeed(float sp) { speed = sp; }

  math::Transform& getTransform() { return transform; }
  const math::Transform& getTransform() const { return transform; }

private:
  float fov;
  float sens = 2.0f;
  float speed = 1.5f;

  math::Transform transform;
};

} // namespace graphics
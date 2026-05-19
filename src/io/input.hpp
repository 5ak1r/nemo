#ifndef INPUT_H
#define INPUT_H

#include <algorithm>

#include "../graphics/scene.hpp"
#include "../graphics/window.hpp"
#include "../math/constants_conversions.hpp"
#include "../math/double2.hpp"
#include "../math/transform.hpp"

namespace io {
namespace input {

void Update(const graphics::window::Window& window);
math::double2 GetMouseDelta();
void ProcessInput(const graphics::window::Window& window, graphics::scene::Scene& scene, float deltaTime);

} // namespace input
} // namespace io


#endif // INPUT_H
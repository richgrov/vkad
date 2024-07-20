#ifndef VKAD_APP_H_
#define VKAD_APP_H_

#include <chrono>

#include "entity/player.h"
#include "gpu/buffer.h"
#include "gpu/descriptor_pool.h"
#include "gpu/instance.h"
#include "gpu/pipeline.h"
#include "math/angle.h"
#include "math/mat4.h"
#include "renderer.h"
#include "sound.h"
#include "ui/font.h"
#include "window/window.h" // IWYU pragma: export

namespace vkad {

class App {
   using Clock = std::chrono::high_resolution_clock;

public:
   App();

   ~App();

   bool poll();

   void draw();

   inline Renderer &renderer() {
      return renderer_;
   }

   inline int width() const {
      return window_.width();
   }

   inline int height() const {
      return window_.height();
   }

   inline int mouse_x() const {
      return window_.mouse_x();
   }

   inline int mouse_y() const {
      return window_.mouse_y();
   }

   inline int delta_mouse_x() const {
      return window_.delta_mouse_x();
   }

   inline int delta_mouse_y() const {
      return window_.delta_mouse_y();
   }

   inline bool left_clicking() const {
      return window_.left_clicking();
   }

   inline bool left_clicked_now() const {
      return !was_left_clicking_ && left_clicking();
   }

   inline bool is_key_down(uint8_t key_code) const {
      return window_.is_key_down(key_code);
   }

   inline float delta() const {
      return delta_.count();
   }

   inline Player &player() {
      return player_;
   }

   Sound create_sound(const char *path) {
      return Sound(sound_system_, path);
   }

   inline Mat4 perspective_matrix() const {
      float aspect = static_cast<float>(window_.height()) / static_cast<float>(window_.width());
      return Mat4::perspective(aspect, deg_to_rad(70), 0.01, 100);
   }

   inline Font &font() {
      return font_;
   }

private:
   Instance vk_instance_;
   Window window_;
   Renderer renderer_;

   Font font_;
   UniformBuffer ui_uniforms_;
   DescriptorPool ui_descriptor_pool_;
   VkDescriptorSet ui_descriptor_set_;
   Pipeline ui_pipeline_;
   std::vector<VertexIndexBuffer> text_meshes_;

   int last_width_;
   int last_height_;

   FMOD_SYSTEM *sound_system_;

   Clock::time_point last_frame_time_;
   std::chrono::duration<float> delta_;
   bool was_left_clicking_;

   Player player_;
};

} // namespace vkad

#endif // !VKAD_APP_H_
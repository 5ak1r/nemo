#include "draw.hpp"

namespace draw
{
  namespace BMP {
    void write(const std::vector<std::vector<maths::float3>>& image, const std::string& name) {
      std::ofstream bmp(name + ".bmp", std::ios::binary);
      
      if (!bmp) {
          throw std::runtime_error("failed to open file");
      }

      uint32_t width = image.size();
      uint32_t height = image[0].size();
      uint32_t byteCounts[3] = {14, 40, width * height * 4};
      
      // thanks sebastian lague
      // BMP header
      bmp.write("BM", 2); // BMP header start
      helpers::binaries::writeLE(bmp, byteCounts[0] + byteCounts[1] + byteCounts[2]); //total file size
      helpers::binaries::writeLE(bmp, (uint32_t)0); // unused
      helpers::binaries::writeLE(bmp, byteCounts[0] + byteCounts[1]); // data offset

      // DIP header
      helpers::binaries::writeLE(bmp, byteCounts[1]); // DIP header size
      helpers::binaries::writeLE(bmp, width); // image width
      helpers::binaries::writeLE(bmp, height); //image height
      helpers::binaries::writeLE(bmp, (uint16_t)1); // num color planes
      helpers::binaries::writeLE(bmp, (uint16_t)32); // bits per pixel (RGBA)
      helpers::binaries::writeLE(bmp, (uint32_t)0); // RGB format no compression
      helpers::binaries::writeLE(bmp, byteCounts[2]); // data size

      char zeros[16] = {};
      bmp.write(zeros, 16); // print resolution and palette info

      // draw using the data
      for (int y = 0; y < image[0].size(); y++) {
        for (int x = 0; x < image.size(); x++) {
          maths::float3 col = image[x][y];
          bmp.put(static_cast<char>(col.b * 255));
          bmp.put(static_cast<char>(col.g * 255));
          bmp.put(static_cast<char>(col.r * 255));
          bmp.put(0);
        }
      }

    }
  }
}

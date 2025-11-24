#include "draw.hpp"

namespace draw
{
  void writeLittleEndian(std::ofstream& out, uint16_t value) {
    char bytes[2];

    bytes[0] = value & 0xFF;
    bytes[1] = (value >> 8) & 0xFF;

    out.write(bytes, 2);
  }
  
  void writeLittleEndian(std::ofstream& out, uint32_t value) {
    char bytes[4];

    bytes[0] = value & 0xFF;
    bytes[1] = (value >> 8) & 0xFF;
    bytes[2] = (value >> 16) & 0xFF;
    bytes[3] = (value >> 24) & 0xFF;

    out.write(bytes, 4);
  }

  void toBMP(const std::vector<std::vector<math::float3>>& image, const std::string& name) {
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
    draw::writeLittleEndian(bmp, byteCounts[0] + byteCounts[1] + byteCounts[2]); //total file size
    draw::writeLittleEndian(bmp, (uint32_t)0); // unused
    draw::writeLittleEndian(bmp, byteCounts[0] + byteCounts[1]); // data offset

    // DIP header
    draw::writeLittleEndian(bmp, byteCounts[1]); // DIP header size
    draw::writeLittleEndian(bmp, width); // image width
    draw::writeLittleEndian(bmp, height); //image height
    draw::writeLittleEndian(bmp, (uint16_t)1); // num color planes
    draw::writeLittleEndian(bmp, (uint16_t)32); // bits per pixel (RGBA)
    draw::writeLittleEndian(bmp, (uint32_t)0); // RGB format no compression
    draw::writeLittleEndian(bmp, byteCounts[2]); // data size

    char zeros[16] = {};
    bmp.write(zeros, 16); // print resolution and palette info

    // draw using the data
    for (int y = 0; y < image[0].size(); y++) {
      for (int x = 0; x < image.size(); x++) {
        math::float3 col = image[x][y];
        bmp.put(static_cast<char>(col.b * 255));
        bmp.put(static_cast<char>(col.g * 255));
        bmp.put(static_cast<char>(col.r * 255));
        bmp.put(0);
      }
    }

  }
}

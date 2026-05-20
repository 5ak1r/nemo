  #include "bmp.hpp"

  namespace io {
  namespace bmp {

  void Write(const graphics::render::RenderTarget& image, const std::string& name) {
    std::ofstream bmp(name + ".bmp", std::ios::binary);

    // extract important info from render target
    const std::vector<graphics::Color>& data = image.getColorBuffer();
    uint32_t width = image.getWidth();
    uint32_t height = image.getHeight();

    if (!bmp) {
        throw std::runtime_error("failed to open file");
    }

    uint32_t byteCounts[3] = {14, 40, width * height * 4};

    // thanks sebastian lague
    // BMP header
    bmp.write("BM", 2); // BMP header start
    utils::binary::WriteLE(bmp, byteCounts[0] + byteCounts[1] + byteCounts[2]); //total file size
    utils::binary::WriteLE(bmp, (uint32_t)0); // unused
    utils::binary::WriteLE(bmp, byteCounts[0] + byteCounts[1]); // data offset

    // DIP header
    utils::binary::WriteLE(bmp, byteCounts[1]); // DIP header size
    utils::binary::WriteLE(bmp, width); // image width
    utils::binary::WriteLE(bmp, height); //image height
    utils::binary::WriteLE(bmp, (uint16_t)1); // num color planes
    utils::binary::WriteLE(bmp, (uint16_t)32); // bits per pixel (RGBA)
    utils::binary::WriteLE(bmp, (uint32_t)0); // RGB format no compression
    utils::binary::WriteLE(bmp, byteCounts[2]); // data size

    char zeros[16] = {};
    bmp.write(zeros, 16); // print resolution and palette info

    // draw using the data
    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
        graphics::Color col = data[y * width + x];
        bmp.put(static_cast<char>(col.b));
        bmp.put(static_cast<char>(col.g));
        bmp.put(static_cast<char>(col.r));
        bmp.put(0);
      }
    }

    bmp.close();
  }

  } // namespace bmp
  } // namespace io

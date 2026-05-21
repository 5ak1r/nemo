#include "bmp.hpp"

namespace io {
namespace bmp {

graphics::Texture Read(const std::string& name) {
  std::ifstream bmp;
  io::file::Open(bmp, name);

  uint16_t bType = utils::binary::ReadLE16(bmp);

  if (bType != 0x4D42) // "BM"
    throw std::runtime_error("not a valid BMP file");

  uint32_t fSize        = utils::binary::ReadLE32(bmp);
  uint32_t fReserved    = utils::binary::ReadLE32(bmp);
  uint32_t fDataOffset  = utils::binary::ReadLE32(bmp);

  uint32_t dipSize      = utils::binary::ReadLE32(bmp);
  uint32_t imgWidth     = utils::binary::ReadLE32(bmp);
  uint32_t imgHeight    = utils::binary::ReadLE32(bmp);
  uint16_t numPlanes    = utils::binary::ReadLE16(bmp);
  uint16_t bitsPerPixel = utils::binary::ReadLE16(bmp);
  uint32_t rbgFormat    = utils::binary::ReadLE32(bmp);
  uint32_t dataSize     = utils::binary::ReadLE32(bmp);

  if (dipSize != 40)
    throw std::runtime_error("unsupported header");

  if (numPlanes != 1)
    throw std::runtime_error("invalid BMP file");

  if (bitsPerPixel != 24 && bitsPerPixel != 32)
    throw std::runtime_error("only 32-bit BMP supported");

  if (rbgFormat != 0)
    throw std::runtime_error("invalid format for BMP file");

  bmp.seekg(fDataOffset, std::ios::beg);

  uint32_t bytesPerPixel = bitsPerPixel / 8;
  uint32_t rowSize = ((imgWidth * bitsPerPixel + 31) / 32) * 4;

  std::vector<graphics::Color> buffer(imgWidth * imgHeight);

  for (uint32_t y = 0; y < imgHeight; y++) {
    for (uint32_t x = 0; x < imgWidth; x++) {
      graphics::Color color;

      color.b = static_cast<uint8_t>(bmp.get());
      color.g = static_cast<uint8_t>(bmp.get());
      color.r = static_cast<uint8_t>(bmp.get());

      if (bytesPerPixel == 4) bmp.get(); // not using alpha

      buffer[y * imgWidth + x] = color;
    }

    uint32_t used = imgWidth * bytesPerPixel;
    uint32_t padding = rowSize - used;

    bmp.ignore(padding);
  }

  graphics::Texture texture;
  texture.setWidth(imgWidth);
  texture.setHeight(imgHeight);
  texture.setImage(buffer);

  return texture;
}

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
  utils::binary::WriteLE32(bmp, byteCounts[0] + byteCounts[1] + byteCounts[2]); //total file size
  utils::binary::WriteLE32(bmp, (uint32_t)0); // reserved
  utils::binary::WriteLE32(bmp, byteCounts[0] + byteCounts[1]); // data offset

  // DIP header
  utils::binary::WriteLE32(bmp, byteCounts[1]); // DIP header size
  utils::binary::WriteLE32(bmp, width); // image width
  utils::binary::WriteLE32(bmp, height); //image height
  utils::binary::WriteLE16(bmp, (uint16_t)1); // num color planes
  utils::binary::WriteLE16(bmp, (uint16_t)32); // bits per pixel (RGBA)
  utils::binary::WriteLE32(bmp, (uint32_t)0); // RGB format no compression
  utils::binary::WriteLE32(bmp, byteCounts[2]); // data size

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

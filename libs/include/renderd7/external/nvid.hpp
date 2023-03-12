#pragma once
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory.h>
#include <memory>
#include <renderd7/external/jpgd.h>
#include <renderd7/external/jpge.h>
#include <sstream>
#include <vector>

struct NVID_Header {
  char magic[4];       // Magic
  int framerate;       // Only Up to 60
  int width;           // Width
  int height;          // Height
  uint32_t framecount; // Count of Frames
};

struct NVID_Frame {
  char magic[4];      // Magic
  uint32_t framesize; // Size of Frame
};

struct NVID_Image {
  int framenum; // Register of Frame
  int w;        // Width of Frame
  int h;        // Height of Frame
  int bpp;      // bpp of Frame
  void *pBuf;   // Buffer
};

inline void CreateHeader(NVID_Header &header) {
  header.magic[0] = 'N';
  header.magic[1] = 'V';
  header.magic[2] = 'I';
  header.magic[3] = 'D';
}

inline void CreateFrame(NVID_Frame &frame) {
  frame.magic[0] = 'N';
  frame.magic[1] = 'F';
  frame.magic[2] = 'R';
  frame.magic[3] = 'M';
}

inline bool CheckHeader(NVID_Header &header) {
  if (header.magic[0] == 'N' && header.magic[1] == 'V' &&
      header.magic[2] == 'I' && header.magic[3] == 'D')
    return true;

  return false;
}

inline bool CheckFrame(NVID_Frame &frame) {
  if (frame.magic[0] == 'N' && frame.magic[1] == 'F' && frame.magic[2] == 'R' &&
      frame.magic[3] == 'M')
    return true;

  return false;
}

inline std::vector<std::unique_ptr<NVID_Image>>
LoadNVID(const std::string &path) {
  std::vector<std::unique_ptr<NVID_Image>> res;
  std::ifstream nvid_file(path, std::ios::binary | std::ios::in);
  if (!nvid_file) {
    std::cerr << "Failed to open NVID file: " << path << std::endl;
    return res;
  }

  NVID_Header header;
  nvid_file.read(reinterpret_cast<char *>(&header), sizeof(header));
  if (!CheckHeader(header)) {
    std::cerr << "Invalid NVID header" << std::endl;
    return res;
  }

  for (int i = 0; i < (int)header.framecount; i++) {
    NVID_Frame frame;
    nvid_file.read(reinterpret_cast<char *>(&frame), sizeof(frame));
    if (!CheckFrame(frame)) {
      std::cerr << "Invalid NVID frame" << std::endl;
      return res;
    }

    std::vector<uint8_t> compressed_data(frame.framesize);
    nvid_file.read(reinterpret_cast<char *>(compressed_data.data()),
                   compressed_data.size());

    int width, height, components;
    unsigned char *decompressed_data = jpgd::decompress_jpeg_image_from_memory(
        compressed_data.data(), compressed_data.size(), &width, &height,
        &components, 3);
    if (!decompressed_data) {
      std::cerr << "Failed to decompress JPEG data" << std::endl;
      return res;
    }

    auto image = std::make_unique<NVID_Image>();
    image->bpp = components;
    image->w = width;
    image->h = height;
    image->framenum = i;
    image->pBuf = decompressed_data;

    res.push_back(std::move(image));
  }

  return res;
}

inline std::vector<std::unique_ptr<NVID_Image>> LoadMemNVID(const void *data,
                                                            size_t size) {
  std::vector<std::unique_ptr<NVID_Image>> res;
  std::istringstream nvid_stream(
      std::string(reinterpret_cast<const char *>(data), size));
  NVID_Header header;
  nvid_stream.read(reinterpret_cast<char *>(&header), sizeof(header));
  if (!CheckHeader(header)) {
    std::cerr << "Invalid NVID header" << std::endl;
    return res;
  }
  for (int i = 0; i < (int)header.framecount; i++) {
    NVID_Frame frame;
    nvid_stream.read(reinterpret_cast<char *>(&frame), sizeof(frame));
    if (!CheckFrame(frame)) {
      std::cerr << "Invalid NVID frame" << std::endl;
      return res;
    }
    std::vector<uint8_t> compressed_data(frame.framesize);
    nvid_stream.read(reinterpret_cast<char *>(compressed_data.data()),
                     compressed_data.size());
    int width, height, components;
    unsigned char *decompressed_data = jpgd::decompress_jpeg_image_from_memory(
        compressed_data.data(), compressed_data.size(), &width, &height,
        &components, 3);
    if (!decompressed_data) {
      std::cerr << "Failed to decompress JPEG data" << std::endl;
      return res;
    }
    auto image = std::make_unique<NVID_Image>();
    image->bpp = components;
    image->w = width;
    image->h = height;
    image->framenum = i;
    image->pBuf = decompressed_data;
    res.push_back(std::move(image));
  }
  return res;
}

class NVID_Stream {
public:
  NVID_Stream(const std::string &path)
      : file_(path, std::ios::binary | std::ios::in) {
    if (!file_) {
      std::cout << "Failed to open NVID file: " << path << std::endl;
      return;
    } else {
      file_.read(reinterpret_cast<char *>(&header_), sizeof(header_));
      if (!CheckHeader(header_)) {
        std::cout << "Invalid NVID header" << std::endl;
        return;
      }
    }
  }

  NVID_Stream(const void *data, std::size_t size) {
    if (!data || size < sizeof(header_)) {
      std::cout << "Invalid NVID data" << std::endl;
      return;
    } else {
      memcpy(&header_, data, sizeof(header_));
      if (!CheckHeader(header_)) {
        std::cout << "Invalid NVID header" << std::endl;
        return;
      }
    }
  }

  ~NVID_Stream() { file_.close(); }

  bool ReadNext(NVID_Image &image) {
    if (!file_) {
      return false;
    }

    NVID_Frame frame;
    file_.read(reinterpret_cast<char *>(&frame), sizeof(frame));
    if (!CheckFrame(frame)) {
      std::cout << "Invalid NVID frame" << std::endl;
      return false;
    }

    std::vector<uint8_t> compressed_data(frame.framesize);
    file_.read(reinterpret_cast<char *>(compressed_data.data()),
               compressed_data.size());

    int width, height, components;
    unsigned char *decompressed_data = jpgd::decompress_jpeg_image_from_memory(
        compressed_data.data(), compressed_data.size(), &width, &height,
        &components, 3);
    if (!decompressed_data) {
      std::cout << "Failed to decompress JPEG data" << std::endl;
      return false;
    }

    image.bpp = components;
    image.w = width;
    image.h = height;
    image.framenum = current_frame_++;
    image.pBuf = decompressed_data;

    return true;
  }

private:
  std::ifstream file_;
  NVID_Header header_;
  int current_frame_ = 0;
};
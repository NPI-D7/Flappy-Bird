#pragma once
#include <cstdint>
#include <fstream>
#include <iostream>
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

/*inline std::vector<NVID_Image> LoadNVID(std::string path) {
  std::vector<NVID_Image> res;
  NVID_Header t_header;
  std::ifstream nvid_file2("out.nvid", std::ios::binary | std::ios::in);

  nvid_file2.read((char *)&t_header, sizeof(NVID_Header));
  if (!CheckHeader(t_header))
    return res;

  for (int i = 0; i < t_header.framecount; i++) {
    NVID_Image tmp;
    NVID_Frame frm;
    nvid_file2.read((char *)&frm, sizeof(NVID_Frame));
    if (!CheckFrame(frm)) {
      return res;
    }
    void *pBuf = malloc(frm.framesize);
    nvid_file2.read((char *)pBuf, frm.framesize);
    int lw, lh, lc;
    unsigned char *dat_s = jpgd::decompress_jpeg_image_from_memory(
        (unsigned char *)pBuf, frm.framesize, &lw, &lh, &lc, 3);
    tmp.bpp = lc;
    tmp.w = lw;
    tmp.h = lh;
    tmp.framenum = i;
    tmp.pBuf = dat_s;
    res.push_back(tmp);
  }
  return res;
}*/

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
  NVID_Stream() {}
  ~NVID_Stream() {}

  bool Load(const std::string &path) {
    file.open(path, std::ios::in | std::ios::binary);
    if (!file) {
      std::cerr << "Error: failed to open " << path << std::endl;
      return false;
    }
    file.read(reinterpret_cast<char *>(&t_header), sizeof(NVID_Header));
    if (!CheckHeader(t_header)) {
      std::cerr << "Error: invalid NVID file header" << std::endl;
      return false;
    }
    currentreg = 0;
    return true;
  }

  void Update() {
    if (!file) {
      return;
    }
    NVID_Frame frm;
    file.read(reinterpret_cast<char *>(&frm), sizeof(NVID_Frame));
    if (!CheckFrame(frm)) {
      return;
    }
    if (frm.framesize > buffer.size()) {
      buffer.resize(frm.framesize);
    }
    file.read(reinterpret_cast<char *>(buffer.data()), frm.framesize);
    int lw, lh, lc;
    unsigned char *dat_s = jpgd::decompress_jpeg_image_from_memory(
        buffer.data(), frm.framesize, &lw, &lh, &lc, 3);
    if (!dat_s) {
      std::cerr << "Error: failed to decompress JPEG data" << std::endl;
      return;
    }
    current_frame.bpp = lc;
    current_frame.w = lw;
    current_frame.h = lh;
    current_frame.framenum = currentreg;
    current_frame.pBuf = dat_s;
    currentreg++;
    if (currentreg > (int)t_header.framecount) {
      file.seekg(sizeof(NVID_Header));
      currentreg = 0;
    }
  }

  NVID_Image GetImage() const { return current_frame; }

private:
  bool CheckHeader(const NVID_Header &header) const {
    // TODO: implement header validation logic
    return true;
  }

  bool CheckFrame(const NVID_Frame &frame) const {
    // TODO: implement frame validation logic
    return true;
  }

  NVID_Image current_frame;
  NVID_Header t_header;
  int currentreg = 0;
  std::ifstream file;
  std::vector<unsigned char> buffer;
};

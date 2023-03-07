#pragma once
#include <string>
#include <vector>

#include <renderd7/bmp.hpp>
#include <renderd7/bmpconverter.hpp>

#include <renderd7/Image.hpp>

#include <renderd7/Screen.hpp>
#include <renderd7/Time.hpp>

#include <renderd7/Fonts/NFontApi.hpp>

namespace RenderD7 {
enum Encoder {
  BITMAP, ///< Encode Data to Bitmap
  DIRECT, ///< Encode Direct to Framebuffer(No Decoder Required)
  C3D     ///< Encode Directly to C3D_Tex (Just an Idea)
};

enum Decoder {
  BITMAP2C3D,    ///< Decode and Encode to C3D_Tex (Currently Fastest) (47,4ms)
  BITMAP2PNG2C3D ///< Decode Bitmap end Convert to Png, then C3D (Very Slow)
                 ///< (201,4ms)
};

class BitmapPrinter {
public:
  BitmapPrinter(int w, int h);
  ~BitmapPrinter();
  bool DecodeFile(std::string file);

  void SetDecoder(Decoder deccc) { decc = deccc; }
  void DrawPixel(int x, int y, u8 b, u8 g, u8 r, u8 a);
  void DrawRect(int x, int y, int w, int h, u8 line_w, u8 b, u8 g, u8 r, u8 a);
  void DrawRectFilled(int x, int y, int w, int h, u8 b, u8 g, u8 r, u8 a);
  void DrawBitmap(int x, int y, BMP map);
  void UsePreMap(BMP map);
  void UsePrePrintMap(BitmapPrinter printmap);
  BMP GetBitmap() { return bitmap; }
  void SaveBmp(std::string name);
  void SavePng(std::string name);

  void CreateScreen(C3D_RenderTarget *target);
  bool DrawScreenDirectF(int framerate);
  bool DrawScreenDirect();
  void DrawScreenF(int framerate);
  void DrawScreen();
  bool UpdateScreenF(int framerate);
  bool UpdateScreen();
  void Clear(u8 b = 0, u8 g = 0, u8 r = 0, u8 a = 255);
  void ClearBlank();
  RenderD7::Image GetImage();
  /// Test to Find out The Best Settings for BitmapPrinter
  void Benchmark();
  /// Setup the Benchmark
  /// \param framerate The Fps of the ScreenUpdates
  void SetupBenchmark(int framerate);
  bool IsBenchmarkRunning() { return this->benchmark; }

  void DrawDebugText(int x, int y, int t_size, u32 color, std::string text);
  void DrawText(int x, int y, float t_size, u32 color, std::string text,
                RenderD7::NFontApi font);

private:
  // funcs
  bool Decode(Decoder deccc);
  void DrawDebugChar(u32 posX, u32 posY, int t_size, u32 color, char character);
  void DrawChar(int posX, int posY, float t_size, u32 color, char character,
                RenderD7::NFontApi font);
  // parameter
  int frame = 0;
  RenderD7::Image renderframe;
  bool isscreen = false;
  C3D_RenderTarget *targetr;
  BMP bitmap = BMP(
      20, 20,
      true); // Need to Set e Predefined Bitmap. If not the System will Crash.
  BMP blank = BMP(
      20, 20,
      true); // Need to Set e Predefined Bitmap. If not the System will Crash.

  ///////////////////////////////////////////////////////////////////////////////////////////////////
  // Benchmark Stuff;
  int testfpsd;
  bool benchmark = false;
  bool setupbenchmark;
  float frametime = 0;
  uint64_t lastTime = 0;
  float dtt = 0.f;
  float dtt2 = 0.f;
  float dtt3 = 0.f;
  float timer = 0;
  float mhdtt = 0;
  float mdtt2;
  float mdtt3;

  float fpsClock = 0.f;
  int frameCounter = 0, fps = 0;

  std::vector<float> hdttt;
  std::vector<float> hdttt2;
  std::vector<float> hdttt3;
  std::vector<int> fpscountc;
  int renderedframes = 0;
  int testfps = 60;
  Encoder encc = Encoder::BITMAP;
  Decoder decc = Decoder::BITMAP2C3D;
  ////////////////////////////////////////////////////////////////////////////////////////////////
};
} // namespace RenderD7
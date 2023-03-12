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
/// @brief Encoder
enum Encoder {
  BITMAP, ///< Encode Data to Bitmap
  DIRECT, ///< Encode Direct to Framebuffer(No Decoder Required)
  C3D     ///< Encode Directly to C3D_Tex (Just an Idea)
};

/// @brief Decoder
enum Decoder {
  BITMAP2C3D,    ///< Decode and Encode to C3D_Tex (Currently Fastest) (47,4ms)
  BITMAP2PNG2C3D ///< Decode Bitmap end Convert to Png, then C3D (Very Slow)
                 ///< (201,4ms)
};

/// @brief BitmapPrinetr Class
class BitmapPrinter {
public:
  /// @brief Constructor
  /// @param w Widrth
  /// @param h Height
  BitmapPrinter(int w, int h);
  /// @brief Deconstructor
  ~BitmapPrinter();
  /// @brief Dexode Bitmap File
  /// @param file path to File
  /// @return success ?
  bool DecodeFile(std::string file);

  /// @brief Set the Decoder
  /// @param deccc Decoder
  void SetDecoder(Decoder deccc) { decc = deccc; }
  /// @brief Draw a Pixel
  /// @param x pos x
  /// @param y pos y
  /// @param b color blue
  /// @param g color green
  /// @param r color red
  /// @param a color alpha
  void DrawPixel(int x, int y, u8 b, u8 g, u8 r, u8 a);
  /// @brief Draw Rectangle
  /// @param x pos x
  /// @param y pos y
  /// @param w width
  /// @param h height
  /// @param line_w line width
  /// @param b color blue
  /// @param g color green
  /// @param r color red
  /// @param a colr alpha
  void DrawRect(int x, int y, int w, int h, u8 line_w, u8 b, u8 g, u8 r, u8 a);
  /// @brief Draw a Fillif Rectangle
  /// @param x pos x
  /// @param y pos y
  /// @param w width
  /// @param h height
  /// @param b color blue
  /// @param g color green
  /// @param r color red
  /// @param a color alpha
  void DrawRectFilled(int x, int y, int w, int h, u8 b, u8 g, u8 r, u8 a);
  /// @brief Draw Bitmap
  /// @param x pos x
  /// @param y pos y
  /// @param map Bitmap to Print
  void DrawBitmap(int x, int y, BMP map);
  /// @brief Use Prebuild Bitmap
  /// @param map bitmap
  void UsePreMap(BMP map);
  /// @brief Use Prebuild Printer Setup
  /// @param printmap Printer
  void UsePrePrintMap(BitmapPrinter printmap);
  /// @brief Get Bitmap
  /// @return Bitmap
  BMP GetBitmap() { return bitmap; }
  /// @brief Save to File
  /// @param name Name/Path
  void SaveBmp(std::string name);
  /// @brief Save as Png
  /// @param name Name/Path
  void SavePng(std::string name);

  /// @brief Setup Screen
  /// @param target Screen
  void CreateScreen(C3D_RenderTarget *target);
  /// @brief Draw Directly to Screen With Framerate
  /// @param framerate Framerate
  /// @return
  bool DrawScreenDirectF(int framerate);
  /// @brief Draw Directly to Screen
  /// @return
  bool DrawScreenDirect();
  /// @brief Render on Screen by Framerate
  /// @param framerate Framerate
  void DrawScreenF(int framerate);
  /// @brief Draw to Screen
  void DrawScreen();
  /// @brief Update Image by Framerate
  /// @param framerate Framerate
  /// @return
  bool UpdateScreenF(int framerate);
  /// @brief Update Image
  /// @return
  bool UpdateScreen();
  /// @brief Clear by Color
  /// @param b color blue
  /// @param g color green
  /// @param r color red
  /// @param a color alpha
  void Clear(u8 b = 0, u8 g = 0, u8 r = 0, u8 a = 255);
  /// @brief Clear Completly Blank
  void ClearBlank();
  /// @brief Get Rendered Image
  /// @return Image
  RenderD7::Image GetImage();
  /// Test to Find out The Best Settings for BitmapPrinter
  void Benchmark();
  /// @brief Setup the Benchmark
  /// \param framerate The Fps of the ScreenUpdates
  void SetupBenchmark(int framerate);
  /// @brief Check if Benchmark is Running
  /// @return is running or not
  bool IsBenchmarkRunning() { return this->benchmark; }

  /// @brief Draw a Dubug Text
  /// @param x pos x
  /// @param y pos y
  /// @param t_size Size of the Text
  /// @param color Color of the Text
  /// @param text String of the Text
  void DrawDebugText(int x, int y, int t_size, u32 color, std::string text);
  /// @brief Draw a Text width NFontApi (TTF)
  /// @param x pos x
  /// @param y pos y
  /// @param t_size size of the Text
  /// @param color Color of The Text
  /// @param text String of The Text
  /// @param font TTF Font
  void DrawText(int x, int y, float t_size, u32 color, std::string text,
                RenderD7::NFontApi font);

private:
  // funcs

  /// @brief Decode 2 RenderD7::Image
  /// @param deccc Decoder
  /// @return
  bool Decode(Decoder deccc);
  /// @brief Draw Char Func
  /// @param posX pos x
  /// @param posY pos y
  /// @param t_size size
  /// @param color color
  /// @param character char
  void DrawDebugChar(u32 posX, u32 posY, int t_size, u32 color, char character);
  /// @brief NFont Draw Char
  /// @param posX pos x
  /// @param posY pos y
  /// @param t_size size
  /// @param color color
  /// @param character char
  /// @param font ttf
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
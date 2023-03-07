#pragma once
#include <3ds.h>
#include <algorithm>
#include <citro2d.h>
#include <citro3d.h>
#include <cstring>
#include <dirent.h>
#include <filesystem>
#include <functional>
#include <iostream>
#include <locale>
#include <map>
#include <memory>
#include <random>
#include <stack>
#include <stdio.h>
#include <string>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <vector>

#include <codecvt>

#include <renderd7/BitmapPrinter.hpp>
#include <renderd7/Color.hpp>
#include <renderd7/Draw.hpp>
#include <renderd7/Image.hpp>
#include <renderd7/Ovl.hpp>
#include <renderd7/ResultDecoder.hpp>
#include <renderd7/Screen.hpp>
#include <renderd7/Sheet.hpp>
#include <renderd7/Sprite.hpp>
#include <renderd7/SpriteAnimation.hpp>
#include <renderd7/Tasks.hpp>
#include <renderd7/Time.hpp>
#include <renderd7/Toast.hpp>
#include <renderd7/bmp.hpp>
#include <renderd7/bmpconverter.hpp>
#include <renderd7/external/lodepng.h>
#include <renderd7/ini.hpp>
#include <renderd7/lang.hpp>
#include <renderd7/parameter.hpp>
#include <renderd7/stringtool.hpp>
#include <renderd7/thread.hpp>

extern "C" {
#include <renderd7/external/fs.h>
}

#define RENDERD7VSTRING "0.9.0"
#define CHANGELOG                                                              \
  "0.9.0: Remove Stupid try of Console\nAdd Services list and Clean up "       \
  "Code.\nAlso added Minimal Init for hax2.x\n0.8.5: Fix Deltatime \n0.8.4: "  \
  "A lot of Fixes and new\nFeatures for BitmapPrinter! \n0.8.3: Addet "        \
  "Overlaycount to Info\nand Addet ResultDecoder for errors.\n0.8.2: Fix a "   \
  "lot of Stuff and\nadd c++17 based filesystem class.\n0.8.1: Add abillity "  \
  "to Get Stdout as string\nto render it to the screen.\n0.8.0: Implement "    \
  "BitmapPrinter\n0.7.3: Implement Over\nRender Overlay Framework\n0.7.2: "    \
  "Implement MT to csv file\nsaving.(removed) Add RGB2HEX.\n0.7.1: Add the "   \
  "New Overlay Handler. Its\nJust in code and does nothing yet.\n0.7.0: Made " \
  "Big Progress In the MT\nOvl but it still crashes On\na Scnd "               \
  "C3D_FrameEnd()."                                                            \
  "\nImplement 800px but\ndoesn't work that good. \n0.6.2: Fix Crash when "    \
  "exiting\ntrouth Home Menu.\n0.6.10: rewrite Threadsystem,\nImprove "        \
  "framerate\n0.6.02: Fix Code in lang.hpp\nadd Draw Text Left "               \
  "Function\n(Right since 0.7.0).\nadd changelog\n0.6.01: add Threading "      \
  "system.\n0.6.0: Better "                                                    \
  "Scene Management\n0.5.0: Fixed some Bugs!\n0.4.0: Trying to fix "           \
  "Filesystem and Bugs!\n0.3.0: Recreate D7-Core into RenderD7!\n0.2.0: "      \
  "Trying to create Animations of\nImages instead of Sheets!\n0.1.0: Initial " \
  "Release of\nD7-Core sprite animation plugin!"
#define DEFAULT_CENTER 0.5f

/*extern C3D_RenderTarget* Top;
extern C3D_RenderTarget* TopRight;
extern C3D_RenderTarget* Bottom;*/

extern u32 d7_hDown;
extern u32 d7_hHeld;
extern u32 d7_hUp;
extern touchPosition d7_touch;

extern std::string dspststus;

/// RenderD7
namespace RenderD7 {
float GetDeltaTime();
enum kbd { SWKBD, BKBD };
enum kbd_type { NUMPAD, STANDARD };
struct TObject {
  int x;                 // Position X
  int y;                 // Position Y
  int w;                 // Button Width
  int h;                 // Button Height
  std::string text = ""; // Text
  float correctx = 0;    // Correct X Position
  float correcty = 0;    // Correct Y Position
  float txtsize = 0.7f;  // Set Text Size
};

class Scene {
public:
  static std::stack<std::unique_ptr<Scene>> scenes;
  virtual ~Scene() {}
  virtual void Logic(u32 hDown, u32 hHeld, u32 hUp, touchPosition touch) = 0;
  virtual void Draw() const = 0;
  // virtual void Ovl() const = 0;
  static void Load(std::unique_ptr<Scene> scene, bool fade = false);
  static void Back();
  static void doDraw();
  static void doLogic(u32 hDown, u32 hHeld, u32 hUp, touchPosition touch);
  // static void HandleOvl();
};

class RSettings : public RenderD7::Scene {
private:
  enum RState { RSETTINGS, RINFO, RSERVICES, RCLOG };
  RenderD7::RSettings::RState m_state = RenderD7::RSettings::RState::RSETTINGS;

  mutable float txtposy = 30;

  std::string rd7srstate = "false";
  std::string mtovlstate = "false";
  std::string fpsstate = "60";
  std::string mtscreenstate = "Top";
  std::string mttxtcolstate = "#ffffff";
  std::string mtcola = "255";
  std::string mttxtcola = "255";

  std::vector<RenderD7::TObject> buttons = {
      {20, 35, 120, 35, "RD7SR", -11, 10},
      {20, 85, 120, 35, "Changelog", -27, 9},
      {20, 135, 120, 35, "MT_OVL", -19, 10},
      {20, 185, 120, 35, "FPS", 6, 10},
      {180, 35, 120, 35, "MTSCREEN", -29, 10},
      {180, 85, 120, 35, "DSPERR", -13, 10},
      {180, 135, 120, 35, "INFO", 2, 10},
      {180, 185, 120, 35, "Services", -13, 10}};

public:
  RSettings();
  void Draw(void) const override;
  ~RSettings();
  void Logic(u32 hDown, u32 hHeld, u32 hUp, touchPosition touch) override;
};

void LoadSettings();

class DSP_NF : public RenderD7::Ovl {
public:
  DSP_NF();
  void Draw(void) const override;
  void Logic() override;

private:
  int msgposy = 240;
  int delay = 0;
};

int GetRandomInt(int b, int e);
void DrawMetrikOvl();
bool DrawImageFromSheet(RenderD7::Sheet *sheet, size_t index, float x, float y,
                        float scaleX = 1.0, float scaleY = 1.0);
namespace Error {
void DisplayError(std::string toptext, std::string errortext, int timesec = 3);
void DisplayFatalError(std::string toptext, std::string errortext);
} // namespace Error
namespace Init {
Result Main(std::string app_name = "RD7Game");
Result Minimal(std::string app_name = "RD7Game");
Result Reload();
void Graphics();
void NdspFirm();
} // namespace Init
namespace Exit {
void Main();
void Minimal();
void NdspFirm();
void Graphics();
} // namespace Exit
namespace Msg {
void Display(std::string titletxt, std::string subtext,
             C3D_RenderTarget *target);
void DisplayWithProgress(std::string titletext, std::string subtext,
                         float current, float total, u32 prgbarcolor);
} // namespace Msg

namespace Convert {
inline float StringtoFloat(std::string inp) { return std::atof(inp.c_str()); }
inline int StringtoInt(std::string inp) { return std::atoi(inp.c_str()); }
inline bool FloatToBool(float inp) {
  if (inp == 1)
    return true;
  else
    return false;
}
} // namespace Convert

struct DirContent {
  std::string name;
  std::string path;
  bool isDir;
};

namespace FS {
bool FileExist(const std::string &path);
}

bool IsNdspInit();
void SetupLog(void);
std::string GetFramerate();
bool MainLoop();
void ExitApp();

void ClearTextBufs(void);

std::string Kbd(int lenght, SwkbdType tp);

void FrameEnd();
void ToggleRD7SR();
bool IsRD7SR();

struct TLBtn {
  int x; // Position X
  int y; // Position Y
  int w; // Button Width
  int h; // Button Height
};

struct ScrollList1 {
  std::string Text = "";
};

struct ScrollList2 {
  float x;
  float y;
  float w;
  float h;
  std::string Text = "";
};
/*enum ListType
{
    ONE,
    TWO
};*/
void DrawList1(RenderD7::ScrollList1 &l, float txtsize, C3D_RenderTarget *t);
void DrawTObjects(std::vector<RenderD7::TObject> tobjects, u32 color,
                  u32 txtcolor, int selection = -1,
                  u32 selbgcolor = RenderD7::Color::Hex("#2D98AF"),
                  u32 selcolor = RenderD7::Color::Hex("#000000"));
void DrawSTObject(std::vector<RenderD7::TObject> tobject, int tobjectindex,
                  u32 color, u32 txtcolor);
bool touchTObj(touchPosition touch, RenderD7::TObject button);
bool touchTLBtn(touchPosition touch, RenderD7::TLBtn button);
void DrawTLBtns(std::vector<RenderD7::TLBtn> btns, u32 color,
                int selection = -1,
                u32 selbgcolor = RenderD7::Color::Hex("#2D98AF"),
                u32 selcolor = RenderD7::Color::Hex("#000000"));

struct Checkbox {
  float x, y, s;
  bool is_chexked = false;
  u32 outcol, incol, chcol;
};
void DrawCheckbox(Checkbox box);

void GetDirContentsExt(std::vector<RenderD7::DirContent> &dircontent,
                       const std::vector<std::string> &extensions);
void GetDirContents(std::vector<RenderD7::DirContent> &dircontent);

} // namespace RenderD7

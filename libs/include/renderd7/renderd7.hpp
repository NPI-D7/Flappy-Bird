#pragma once
/// c++ Includes
#include <algorithm>
#include <codecvt>
#include <cstring>
#include <filesystem>
#include <functional>
#include <iostream>
#include <locale>
#include <map>
#include <memory>
#include <random>
#include <stack>
#include <string>
#include <vector>
/// c includes
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
/// 3ds Includes
#include <3ds.h>
#include <citro2d.h>
#include <citro3d.h>
/// RenderD7 Includes
#include <renderd7/BitmapPrinter.hpp>
#include <renderd7/Color.hpp>
#include <renderd7/Draw.hpp>
#include <renderd7/FunctionTrace.hpp>
#include <renderd7/Hardware.hpp>
#include <renderd7/Image.hpp>
#include <renderd7/Memory.hpp>
#include <renderd7/Ovl.hpp>
#include <renderd7/ResultDecoder.hpp>
#include <renderd7/Screen.hpp>
#include <renderd7/Security.hpp>
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

#define RENDERD7VSTRING "0.9.4"
#define CHANGELOG                                                              \
  "0.9.4: Implement new Security System\n To prevent from crashes\nImplement " \
  "Functiontrace for better\nTiming Tests\nImplement MemAlloc Tracker (only "  \
  "size)\nAdd some new Overlays (not functional yet)\nComplete Rewrite of "    \
  "Overlay System\nFixed the FrameEnd Crash\nNew System to get Hardware "      \
  "Info\nRemoved RD7SR\n0.9.3: Completly Documanted Everything\nFix typo "     \
  "in "                                                                        \
  "Sprite::getHeight()\nRemove Deprecated/Useless Stuff\n0.9.2: Add "          \
  "NpiSplashVideo\nNvid Support(v0.0.1)\nAdd "                                 \
  "Basic RenderD7 "                                                            \
  "Splash\nFaster Graphics Init\nFade Effects\nFix Screen for this "           \
  "Changelog\n0.9.1: Fix Critical bug in\nSpritesheet animations\nFix "        \
  "Color "                                                                     \
  "Conver(Hex)\n0.9.0: Remove Stupid try of Console\nAdd Services list and "   \
  "Clean up "                                                                  \
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

#define RD7_DEPRECATED // __attribute__ ((deprecated))

/// @param d7_hDown Current Key Down
extern u32 d7_hDown;
/// @param d7_hHeld Current Key Held
extern u32 d7_hHeld;
/// @param d7_hUp Current Key Up
extern u32 d7_hUp;
/// @param d7_touch Current Touch Position
extern touchPosition d7_touch;

/// @param dspststus Dsp Status String
extern std::string dspststus;

/// @param rd7_do_splash Config Value To Enable RenderD7 Splash
extern bool rd7_do_splash;
/// @param rd7_enable_memtrack Config Value to Track Mem Allocations
extern bool rd7_enable_memtrack;

/// RenderD7
namespace RenderD7 {
/// @brief Get Deltatime
/// @return Deltatime
float GetDeltaTime();
/// @brief Keyboard
enum kbd {
  /// @brief libctru Keyboard
  SWKBD,
  /// @brief Unk (Not Usable)
  BKBD
};
/// @brief Keyboar Type
enum kbd_type { NUMPAD, STANDARD };
/// @brief A Button
struct TObject {
  int x;                 ///< Position X
  int y;                 ///< Position Y
  int w;                 ///< Button Width
  int h;                 ///< Button Height
  std::string text = ""; ///< Text
  float txtsize = 0.7f;  ///< Set Text Size
};
/// @brief Scene Class
class Scene {
public:
  /// @brief Stack of the Scenes
  static std::stack<std::unique_ptr<Scene>> scenes;
  /// @brief Deconstructor
  virtual ~Scene() {}
  /// @brief Logic To Overide
  /// @param hDown Key Down
  /// @param hHeld Key Held
  /// @param hUp Key Up
  /// @param touch Touch Position
  virtual void Logic(u32 hDown, u32 hHeld, u32 hUp, touchPosition touch) = 0;
  /// @brief Draw Func to Override
  virtual void Draw() const = 0;
  /// @brief Push a Scene to Stack
  /// @param scene Scene to Push
  /// @param fade FadeEffect (Not Correctly Implementet yet)
  static void Load(std::unique_ptr<Scene> scene, bool fade = false);
  /// @brief Go Back a Scene
  static void Back();
  /// @brief do the Draw (Called in RenderD7::MainLoop())
  static void doDraw();
  /// @brief do the Logic (Called in RenderD7::MainLoop())
  /// @param hDown Key Down
  /// @param hHeld Key Held
  /// @param hUp Key Up
  /// @param touch Touch Positon
  static void doLogic(u32 hDown, u32 hHeld, u32 hUp, touchPosition touch);
};

/// @brief Integrated Setting Menu of RenderD7
class RSettings : public RenderD7::Scene {
private:
  /// @brief Calculate the Changelog Screen Stuff
  /// @param lines vector of Lines
  /// @param screen_index Current Screen
  /// @param screens Count of Possible Screens
  void calculate_screens(const std::vector<std::string> &lines,
                         int &screen_index, int &screens);
  /// @brief State (Define for Menus)
  enum RState {
    RSETTINGS,
    RINFO,
    RSERVICES,
    RCLOG,
    RMCONFIG,
    RFTRACE,
    RSECM,
    RCREDITS
  };
  /// @param m_state Current menu State (Default=MainMenu aka RSETTINGS)
  RenderD7::RSettings::RState m_state = RenderD7::RSettings::RState::RSETTINGS;

  /// @param screens Count of Changelog Screens
  int screens = 0;
  /// @param screen_index Current Changelog Screen
  int screen_index = 0;
  /// @param lines Vector of Changelog-Lines
  std::vector<std::string> lines;
  /// @brief Position in FTrace Menu
  int ftrace_index = 0;

  /// @param mtovlstate State of Metricks Overlay
  std::string mtovlstate = "false";
  /// @param mtscreenstate Screen the Overlay is Set to
  std::string mtscreenstate = "Top";

  /// @param buttons Vector of Buttons
  std::vector<RenderD7::TObject> buttons = {
      {20, 35, 120, 35, "NotYET"},      {20, 85, 120, 35, "Changelog"},
      {20, 135, 120, 35, "Metrik-Ovl"}, {20, 185, 120, 35, "Tasks"},
      {180, 35, 120, 35, "FTrace"},     {180, 85, 120, 35, "Credits"},
      {180, 135, 120, 35, "Info"},      {180, 185, 120, 35, "Security"}};

public:
  /// @brief Constructor
  RSettings();
  /// @brief Override for Draw
  /// @param
  void Draw(void) const override;
  /// @brief Deconstructor
  ~RSettings();
  /// @brief Override for Logic
  /// @param hDown Key Down
  /// @param hHeld Key Held
  /// @param hUp Key Up
  /// @param touch Touch Position
  void Logic(u32 hDown, u32 hHeld, u32 hUp, touchPosition touch) override;
};

/// @brief Show Up the RenderD7-Settings Menu
void LoadSettings();

/// @brief DspNotFound Error Toast (Deprectated)
class DSP_NF : public RenderD7::Ovl {
public:
  /// @brief Constructor
  DSP_NF();
  /// @brief Override for Draw
  void Draw(void) const override;
  /// @brief Override for Logic
  void Logic() override;

private:
  /// @param msgposy Y Position of Toast
  int msgposy = 240;
  /// @param delay Delay of Toast
  int delay = 0;
};

/// @brief Get A Rendom Int
/// @param b From
/// @param e To
/// @return Random Int
int GetRandomInt(int b, int e);
/// @brief Short a String with (..,)
/// @param in Input string
/// @param size Size of Input Text
/// @param maxlen Max length of texr
/// @param font Custom Font for Correct Size Calculation
/// @return Shorted String
std::string ShortString(std::string in, float size, int maxlen,
                        C2D_Font font = nullptr);
/// @brief DrawMetrikOvl (YOUR OWN RISK)
void DrawMetrikOvl();
/// @brief Draw Image from RenderD7 Sheet
/// @param sheet Spritesheet
/// @param index Image index Value
/// @param x Pos X
/// @param y Pos Y
/// @param scaleX Scale on X-Axis
/// @param scaleY Scale on Y-Axis
/// @return success ?
bool DrawImageFromSheet(RenderD7::Sheet *sheet, size_t index, float x, float y,
                        float scaleX = 1.0, float scaleY = 1.0);
/// @brief Display the Npi-D7 Video Intro (NVID)
void DoNpiIntro();
/// @brief Fade In
/// @param duration Duration in Frames
void FadeIn();
/// @brief Fade Out
/// @param duration Duration in Frames
void FadeOut();
/// @brief Display Fade Effects
void FadeDisplay();

namespace Error {
/// @brief DEPRECATED Display Error for n Seconds
/// @param toptext Head Text
/// @param errortext Error Text
/// @param timesec Time n to Display in Seconds
void DisplayError(std::string toptext, std::string errortext, int timesec = 3);
/// @brief Display A Fatal Error
/// @param toptext Head Text
/// @param errortext Error Text
void DisplayFatalError(std::string toptext, std::string errortext);
} // namespace Error

namespace Init {
/// @brief Init Default RenderD7
/// @param app_name Name of Your App
/// @return ResCode
Result Main(std::string app_name = "RD7Game");
/// @brief Init Minimal RenderD7 (For better Hax2.x support)
/// @param app_name Name of Your App
/// @return ResCode
Result Minimal(std::string app_name = "RD7Game");
/// @brief Reload the Graphics Engine
/// @return ResCode
Result Reload();
/// @brief Init Graphics Only (NOT SUPPORTET use Reload)
void Graphics();
/// @brief Init Ndsp for Sounds
void NdspFirm();
} // namespace Init

namespace Msg {
/// @brief Display A Message
/// @param titletxt Header Text
/// @param subtext Message Text
/// @param target Screen
void Display(std::string titletxt, std::string subtext,
             C3D_RenderTarget *target);
/// @brief Display A Message Wit Progress
/// @param titletext Header Text
/// @param subtext Message Text
/// @param current Current Progress
/// @param total Total Progress
/// @param prgbarcolor Color of Progressbar
void DisplayWithProgress(std::string titletext, std::string subtext,
                         float current, float total, u32 prgbarcolor);
} // namespace Msg

namespace Convert {
/// @brief Convert a String to Flaot
/// @param inp Input String
/// @return Float
inline float StringtoFloat(std::string inp) { return std::atof(inp.c_str()); }
/// @brief Convert String to Int
/// @param inp Input String
/// @return Int
inline int StringtoInt(std::string inp) { return std::atoi(inp.c_str()); }
/// @brief Convert a Float to Bool
/// @param inp Input Float
/// @return Bool
inline bool FloatToBool(float inp) { return (inp == 1 ? true : false); }
} // namespace Convert

namespace FS {
/// @brief Check if File exists
/// @param path Path to the File
/// @return exists or not
bool FileExist(const std::string &path);
} // namespace FS

/// @brief Check if Ndsp is Init
/// @return is or not
bool IsNdspInit();
/// @brief Get Current Framerate as String
/// @return Framerate String
std::string GetFramerate();
/// @brief MainLoop of RenderD7s
/// @return Is Still Running or not
bool MainLoop();
/// @brief Exit App (brak the MainLoop)
void ExitApp();

/// @brief Clear the Citro2D TextBuffers
/// @param
void ClearTextBufs(void);

/// @brief Open A Keyboard (SWKBD)
/// @param lenght Length of the string
/// @param tp Type of The Keyboard
/// @return the string if pressed Ok
std::string Kbd(int lenght, SwkbdType tp);

/// @brief Draw Overlays And end the Frame. DO NEVER USE C3D_FRAMEEND cause it
/// breaks Overlay crash Security
void FrameEnd();

/// @brief Textless Button
struct TLBtn {
  int x; ///< Position X
  int y; ///< Position Y
  int w; ///< Button Width
  int h; ///< Button Height
};
/// @brief Draw Buttons
/// @param tobjects Vector of Buttons
/// @param color Color of the Buttons
/// @param txtcolor Color of The Text
/// @param selection Positon of Selection
/// @param selbgcolor Selection BackgroundColor
/// @param selcolor Selection Color
void DrawTObjects(std::vector<RenderD7::TObject> tobjects, u32 color,
                  u32 txtcolor, int selection = -1,
                  u32 selbgcolor = RenderD7::Color::Hex("#2D98AF"),
                  u32 selcolor = RenderD7::Color::Hex("#000000"));
/// @brief Draw A Single Button
/// @param tobject Button
/// @param tobjectindex Button Index
/// @param color Color of the Button
/// @param txtcolor Color of The Text
void DrawSTObject(std::vector<RenderD7::TObject> tobject, int tobjectindex,
                  u32 color, u32 txtcolor);
/// @brief Touched A Button
/// @param touch Touch Position
/// @param button Button
/// @return is touched or not
bool touchTObj(touchPosition touch, RenderD7::TObject button);
/// @brief Touched A Textless Button
/// @param touch Touch Position
/// @param button Button
/// @return is touched or not
bool touchTLBtn(touchPosition touch, RenderD7::TLBtn button);
/// @brief Draw Textless Buttons
/// @param tobjects Vector of Buttons
/// @param color Color of the Buttons
/// @param selection Positon of Selection
/// @param selbgcolor Selection BackgroundColor
/// @param selcolor Selection Color
void DrawTLBtns(std::vector<RenderD7::TLBtn> btns, u32 color,
                int selection = -1,
                u32 selbgcolor = RenderD7::Color::Hex("#2D98AF"),
                u32 selcolor = RenderD7::Color::Hex("#000000"));
} // namespace RenderD7

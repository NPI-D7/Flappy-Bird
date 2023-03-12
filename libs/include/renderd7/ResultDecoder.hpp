#pragma once
#include <3ds.h>
#include <string>

namespace RenderD7 {
/// @brief Decoder for 3ds Result Codes
class ResultDecoder {
public:
  /// @brief Constructor
  ResultDecoder() {}
  /// @brief Deconstructor
  ~ResultDecoder() {}
  /// @brief Load a Result into Decoder
  /// @param rescode Result Code
  void Load(Result rescode);
  /// @brief Load A Hex Converted Code into Decoder
  /// @param rescode Result-Hex Code
  void Load(std::string rescode);
  /// @brief Get Hex Code
  /// @return Hex-Code
  std::string GetCode();
  /// @brief Get Level Name
  /// @return Level Name
  std::string GetLevel();
  /// @brief Get Level Value
  /// @return Level Value
  int GetLevelInt();
  /// @brief Get The Mosule Name
  /// @return Module Name
  std::string GetModule();
  /// @brief Get The Module Value
  /// @return Module Value
  int GetModuleInt();
  /// @brief Get The Description
  /// @return Description
  std::string GetDescription();
  /// @brief Get The Description Valur
  /// @return Description Value
  int GetDescriptionInt();
  /// @brief Get the Summary
  /// @return Summary
  std::string GetSummary();
  /// @brief Get the Summary Value
  /// @return Summary Value
  int GetSummaryInt();

private:
  /// @param m_rescode Result code
  Result m_rescode;
};
} // namespace RenderD7
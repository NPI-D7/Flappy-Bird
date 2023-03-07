#pragma once
#include <3ds.h>
#include <string>

namespace RenderD7 {
class ResultDecoder {
public:
  ResultDecoder() {}
  ~ResultDecoder() {}
  void Load(Result rescode);
  void Load(std::string rescode);
  std::string GetCode();
  std::string GetLevel();
  int GetLevelInt();
  std::string GetModule();
  int GetModuleInt();
  std::string GetDescription();
  int GetDescriptionInt();
  std::string GetSummary();
  int GetSummaryInt();

private:
  Result m_rescode;
};
} // namespace RenderD7
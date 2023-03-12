#pragma once
#include <renderd7/external/json.hpp>
#include <string>

namespace RenderD7 {
namespace Lang {
/// @brief Get 3ds System lang! [en] by default
/// @return Sytemlang as string
std::string getSys();
/// @brief Get The Translation String
/// @param key Key of Translation
/// @return The Translated String
std::string get(const std::string &key);
/// @brief Load A Language json
/// @param lang The Language Key [en], [de], etc, or getSys()
void load(const std::string &lang);
} // namespace Lang
} // namespace RenderD7

#pragma once

namespace RenderD7 {
namespace Hardware {
/// @brief Initialisize required Services
void Initialisize();
/// @brief Check if Headphones are Plugged in
/// @return true if headphones plugged in
bool IsHeadphones();
/// @brief Check if the 3ds Is Charging
/// @return true if System gets Charged
bool IsCharging();
/// @brief Check the Battery Percentage
/// @return Persentage as float
float GetBatteryPercentage();
/// @brief Get current State of 3d Slider
/// @return current 3dslider poition
float Get3dSliderLevel();
/// @brief Get Current state of Sound Slider
/// @return current SoundSlider state
float GetSoundSliderLevel();
} // namespace Hardware
} // namespace RenderD7
#pragma once

#include <3ds.h>
#include <string>

/** Sound Class */
class sound {
public:
  /// \brief Construct new Soundeffect
  /// \param path Path to the .wav file
  /// \param channel the channel 1-23
  /// \param toloop true:loop the sound, false: don't loop
  sound(const std::string &path, int channel = 1, bool toloop = false);
  /// @brief Deconstructor
  ~sound();
  /// @brief Play the sound
  void play();
  /// @brief Stop the sound
  void stop();

private:
  /// \param dataSize Size of the filedata
  u32 dataSize;
  /// \param waveBuf For ndsp
  ndspWaveBuf waveBuf;
  /// \param data Memmory data of the sound
  uint8_t *data = NULL;
  /// \param chnl Channel of the sound
  int chnl;
};

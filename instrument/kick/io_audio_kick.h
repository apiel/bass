#ifndef IO_AUDIO_KICK_H_
#define IO_AUDIO_KICK_H_

#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <Audio.h>

#include "../io_audio_base.h"
#include "./io_audio_kick_core.h"
#include "./io_audio_kick_ui.h"

class IO_AudioKick
    : public IO_AudioKickCore,
      public IO_AudioBase<IO_AudioKickCore, IO_AudioKickCoreUI> {
   public:
    IO_AudioKick() {
        coreUI = new IO_AudioKickCoreUI(this);
        seq = new IO_AudioSeq<IO_AudioKickCore>(this);
        seqUI = new IO_AudioSeqUI<IO_AudioKickCore>(seq);
    }
};

#endif

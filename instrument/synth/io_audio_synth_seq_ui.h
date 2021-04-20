#ifndef IO_AUDIO_SYNTH_SEQ_UI_H_
#define IO_AUDIO_SYNTH_SEQ_UI_H_

#include <Arduino.h>

// #include "../../Pattern.h"
#include "./io_audio_synth_core.h"
#include "./io_audio_synth_seq.h"
// #include "../../io_pattern_storage.h"

class IO_AudioSynthSeqUI {
   private:
    IO_AudioSynthCore* core;
    IO_AudioSynthSeq* seq;

   public:
    IO_AudioSynthSeqUI(IO_AudioSynthCore* _core, IO_AudioSynthSeq* _seq) {
        core = _core;
        seq = _seq;
    }
};

#endif

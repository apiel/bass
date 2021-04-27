#ifndef IO_STATE_H_
#define IO_STATE_H_

#include <Arduino.h>

#include "io_midi_core.h"
#include "io_util.h"

bool mcMode = false;
bool sdAvailable = true;

void toggleMcMode() { mcMode = !mcMode; }

#endif

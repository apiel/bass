#ifndef IO_STATE_H_
#define IO_STATE_H_

#include <Arduino.h>

#include "io_util.h"

bool mcMode = false;
bool sdAvailable = true;

void toggleGcMode() { mcMode = !mcMode; }

#endif

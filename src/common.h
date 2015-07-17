#pragma once
#include <pebble.h>

typedef enum{start, work, rest}MODE;

extern MODE mode;
extern time_t leftTime;

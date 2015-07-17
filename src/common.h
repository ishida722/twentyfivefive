#pragma once
#include <pebble.h>

typdef enum{start, work, rest}MODE;

extern MODE mode;
extern time_t leftTime;

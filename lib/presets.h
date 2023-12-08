#ifndef HEADER_PRESETS
#define HEADER_PRESETS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define Type int

inline static int randint(int min, int max){ return (rand() % (max-min+1)) + min; }

#endif

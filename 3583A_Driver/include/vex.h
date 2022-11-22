/*----------------------------------------------------------------------------
 *
 * Copyright (C) 2022 VEX Team 3583A - All Rights Reserved
 * Any other team can NOT use, distribute, or modify this code 
 * as per the terms of VEX honor code.
 *
 *---------------------------------------------------------------------------*/


//#include <math.h>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>


#include "v5.h"
#include "v5_vcs.h"

#include "robot-config.h"


#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)
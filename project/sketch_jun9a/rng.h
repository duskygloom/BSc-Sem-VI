#pragma once

#include "common.h"

/**
 * @param analogPin
 * An un-initialized pin to act as an entropy source.
 */
ulong trulyRandom(byte analogPin);

/**
 * @note
 * This function is using the Arduino provided random()
 * function. Make sure that you have set a good seed
 * value before using it.
 */
int rngFunc(byte *dest, unsigned size);

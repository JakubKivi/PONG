#ifndef DEBUG_PRINT_H
#define DEBUG_PRINT_H

#include <Arduino.h>
#include <fastled.h>

// Ensure Menu declaration is available and the global instance `menu` is declared
#include "menu/Menu.h"
extern Menu menu;

// target color (0xFF5500) components
#define DEBUG_TARGET_R 0xFF
#define DEBUG_TARGET_G 0x55
#define DEBUG_TARGET_B 0x00

#define DEBUG_ENABLED() (menu.getCurrentColor().r == DEBUG_TARGET_R && \
						 menu.getCurrentColor().g == DEBUG_TARGET_G && \
						 menu.getCurrentColor().b == DEBUG_TARGET_B)

#define DEBUG_FN() do { if (DEBUG_ENABLED()) { Serial.print("[FN] "); Serial.println(__func__); } } while(0)
#define DEBUG_ARG(arg) do { if (DEBUG_ENABLED()) { Serial.print("  "); Serial.print(#arg); Serial.print(" = "); Serial.println(arg); } } while(0)
#define DEBUG_CHECKPOINT(msg) do { if (DEBUG_ENABLED()) { Serial.print("[CP] "); Serial.println(msg); } } while(0)

#endif // DEBUG_PRINT_H

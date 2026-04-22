// FastLED-MM — Arduino IDE entry point.
//
// This file mirrors src/main.cpp for Arduino IDE users.
// PlatformIO users: use src/main.cpp via platformio.ini.
//
// Arduino IDE setup:
//   1. Install the projectMM library (Sketch > Include Library > Add .ZIP Library)
//   2. Install FastLED via the Library Manager
//   3. Open this sketch and flash

#include <Arduino.h>
#include <FastLED.h>
#include "src/core/AppSetup.h"
#include "src/FlmConfig.h"
#include "src/FlmPixels.h"
#include "src/effects/WaveRainbow2D.h"
#include "src/drivers/FastLEDDriver.h"

CRGB flm_leds[FLM_NUM_LEDS];

REGISTER_MODULE(WaveRainbow2DEffect)
REGISTER_MODULE(FastLEDDriverModule)

static Scheduler     scheduler;
static ModuleManager mm(scheduler);
static HttpServer    server(80);
static WsServer      ws;

static void firstBoot(ModuleManager& mm) {
    if (pal::hasModuleType(mm, "WaveRainbow2DEffect")) return;
    JsonDocument d; auto ep = d.as<JsonObjectConst>();
    mm.addModule("WaveRainbow2DEffect", "fx1",     ep, ep, 0, "");
    mm.addModule("FastLEDDriverModule", "driver1", ep, ep, 1, "");
    mm.saveAllState();
}

void setup() {
    Serial.begin(115200);
    pal::embeddedSetup(mm, scheduler, server, ws, nullptr, firstBoot);
}

void loop() { pal::suspend_forever(); }

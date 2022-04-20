#include <AUnit.h>
#include <Arduino.h>
#include <Canny.h>
#include <R51Core.h>

namespace R51 {

using namespace aunit;

test(SystemEventTest, Empty) {
    uint8_t expect[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    SystemEvent event;
    assertEqual(event.id, 0);
    assertEqual(event.size, 0);
    assertEqual(memcmp(expect, event.data, 5), 0);
}

test(SystemEventTest, WithID) {
    uint8_t expect[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    SystemEvent event(Event::BODY_POWER_STATE);
    assertEqual(event.id, (uint8_t)Event::BODY_POWER_STATE);
    assertEqual(event.size, 0);
    assertEqual(memcmp(expect, event.data, 5), 0);
}

test(SystemEventTest, WithData) {
    uint8_t expect[] = {0x00, 0x11, 0xFF, 0xFF, 0xFF};
    SystemEvent event(Event::BODY_POWER_STATE, {0x00, 0x11});
    assertEqual(event.id, (uint8_t)Event::BODY_POWER_STATE);
    assertEqual(event.size, 2);
    assertEqual(memcmp(expect, event.data, 5), 0);
}

}  // namespace R51

// Test boilerplate.
void setup() {
#ifdef ARDUINO
    delay(1000);
#endif
    SERIAL_PORT_MONITOR.begin(115200);
    while(!SERIAL_PORT_MONITOR);
}

void loop() {
    aunit::TestRunner::run();
    delay(1);
}

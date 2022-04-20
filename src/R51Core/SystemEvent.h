#ifndef _R51_CORE_SYSTEM_EVENT_H_
#define _R51_CORE_SYSTEM_EVENT_H_

#include <Arduino.h>
#include <Canny.h>

namespace R51 {

enum class Event : uint8_t {
    BODY_POWER_STATE = 0x80,
};

struct SystemEvent : public Printable {
    // Unique Event identifier. This is unique among all events.
    uint8_t id;
    // Event data. Empty bytes are padded with 0xFF.
    uint8_t data[5];
    // The number of bytes set in data. The unset bytes are padded with 0xFF.
    uint8_t size;

    // Construct an empty system event. ID is set to 0x00 and size to 0.
    SystemEvent();

    // Construct a specific system event with empty data.
    SystemEvent(Event event);

    // Construct a specific system event containing the provided data. The
    // size is set to the size of the provided data array. This array
    // should not exceed 5 bytes.
    template <size_t N> 
    SystemEvent(Event event, const uint8_t (&data)[N]);

    // Print the system event.
    size_t printTo(Print& p) const override;
};

// Return true if the two system events are equal
bool operator==(const SystemEvent& left, const SystemEvent& right);

// Return true if the two system events are not equal
bool operator!=(const SystemEvent& left, const SystemEvent& right);

template <size_t N>
SystemEvent::SystemEvent(Event event, const uint8_t (&data)[N]) :
        id((uint8_t)event), size(sizeof(data)) {
    for (uint8_t i = 0; i < size; i++) {
        this->data[i] = data[i];
    }
    for (uint8_t i = size; i < 5; i++) {
        this->data[i] = 0xFF;
    }
}

}  // namespace R51

#endif  // _R51_CORE_SYSTEM_EVENT_H_

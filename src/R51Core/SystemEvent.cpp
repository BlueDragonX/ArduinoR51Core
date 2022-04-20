#include "SystemEvent.h"

namespace R51 {

SystemEvent::SystemEvent() : id(0), size(0) {
    memset(data, 0xFF, 5);
}

SystemEvent::SystemEvent(Event event) : id((uint8_t)event), size(0) {
    memset(data, 0xFF, 5);
}

size_t SystemEvent::printTo(Print& p) const {
    size_t n = p.print(id, HEX);
    for (uint8_t i = 0; i < size; i++) {
        n += p.print(":");
        n += p.print(data[i], HEX);
    }
    return n;
}

bool operator==(const SystemEvent& left, const SystemEvent& right) {
    return left.id == right.id && left.size == right.size &&
        memcmp(left.data, right.data, left.size) == 0;
}

// Return true if the two system events are not equal
bool operator!=(const SystemEvent& left, const SystemEvent& right) {
    return left.id != right.id || left.size != right.size ||
        memcmp(left.data, right.data, left.size) != 0;
}

}  // namespace R51

#ifndef _R51_CORE_MESSAGE_H_
#define _R51_CORE_MESSAGE_H_

#include <Arduino.h>
#include <Canny.h>

namespace R51 {

struct SystemEvent {
    // Unique Event identifier. This is unique among all events.
    uint8_t id;
    // Event data. Empty bytes are padded with 0xFF.
    uint8_t data[5];
    // The number of bytes set in data. The unset bytes are padded with 0xFF.
    uint8_t size;

    SystemEvent() : id(0), size(0) {
        id = 0;
        size = 0;
        memset(data, 0xFF, 5);
    }

    explicit SystemEvent(uint8_t id) : id(id), size(0) {
        memset(data, 0xFF, 5);
    }

    SystemEvent(uint8_t id, uint8_t size) : id(id), size(size) {
        memset(data, 0xFF, 5);
    }
};

class Message {
    public:
        // The message type.
        enum Type {
            EMPTY,
            SYSTEM_EVENT,
            CAN_FRAME,
        };

        // Default constructor. Sets type to EMPTY.
        Message() : Message(EMPTY, nullptr) {}

        // Construct a message that references a system event.
        Message(SystemEvent& system_event) :
            type_(SYSTEM_EVENT), ref_(&system_event) {}

        // Construct a message that references a CAN frame.
        Message(Canny::Frame& can_frame) :
            type_(CAN_FRAME), ref_(&can_frame) {}

        // Return the type of the mesasge.
        enum Type type() const { return type_; };

        // Return the system event referenced by the message. Requires that
        // type() returns SYSTEM_EVENT or undefined behavior will result.
        const SystemEvent& system_event() const { return *((SystemEvent*)ref_); }

        // Return the can frame referenced by the message. Requires that type()
        // returns CAN_FRAME or undefined behavior will result.
        const Canny::Frame& can_frame() const { return *((Canny::Frame*)ref_); }

    private:
        Type type_;
        void* ref_;

        Message(Type type, void* ref) : type_(type), ref_(ref) {}

        friend bool operator==(const Message&, const Message&);
        friend bool operator!=(const Message&, const Message&);
};

// Return true if the two messages reference the same payload.
bool operator==(const Message& left, const Message& right);

// Return true if the two messages reference different payloads.
bool operator!=(const Message& left, const Message& right);

}  // namespace R51

#endif  // _R51_CORE_MESSAGE_H_

#ifndef _R51_CORE_MESSAGE_H_
#define _R51_CORE_MESSAGE_H_

#include <Arduino.h>
#include <Canny.h>
#include "SystemEvent.h"

namespace R51 {

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

#include "Ticker.h"

namespace R51 {

Ticker::Ticker(uint32_t interval, Faker::Clock* clock) :
        interval_(interval), last_tick_(0), clock_(clock) {}

bool Ticker::active() const {
    if (clock_->millis() - last_tick_ >= interval_) {
        return true;
    }
    return false;
}

void Ticker::reset() {
    if (clock_->millis() - last_tick_ >= interval_) {
        last_tick_ = clock_->millis();
    }
}

}  // namespace R51

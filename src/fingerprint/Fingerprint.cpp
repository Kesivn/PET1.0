#include <cstdint>
#include <limits>

#include "Fingerprint.h"


Fingerprint::Fingerprint(uint64_t value, int length)
    : value_(value), length_(length) {
    if (length_ <= 0) {
        length_ = 0;
        value_ = 0;
        return;
    }
    if (length_ >= 64) {
        length_ = 64;
        return;
    }
    // mask value to the specified length
    uint64_t mask = (length_ >= 64) ? std::numeric_limits<uint64_t>::max() : ((1ULL << length_) - 1ULL);
    value_ &= mask;
}

uint64_t Fingerprint::prefixBits(int k) const {
    if (k <= 0) return 0ULL;
    if (k >= length_) return value_;
    int shift = length_ - k;
    return value_ >> shift;
}

Fingerprint Fingerprint::suffix(int k) const {
    if (k <= 0) return *this;
    if (k >= length_) return Fingerprint(0ULL, 0);
    int newlen = length_ - k;
    uint64_t mask = (newlen >= 64) ? std::numeric_limits<uint64_t>::max() : ((1ULL << newlen) - 1ULL);
    uint64_t newval = value_ & mask;
    return Fingerprint(newval, newlen);
}
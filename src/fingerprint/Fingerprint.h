#pragma once

#include <cstdint>

class Fingerprint {
public:
    explicit Fingerprint(uint64_t value, int length = 64);

    uint64_t prefixBits(int k) const;

    Fingerprint suffix(int k) const;

    uint64_t raw() const {
        return value_;
    }

    int length() const {
        return length_;
    }

private:
    uint64_t value_;
    int length_;
};
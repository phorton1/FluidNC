// Copyright (c) 2021 -  Stefan de Bruijn
// Use of this source code is governed by a GPLv3 license that can be found in the LICENSE file.

#pragma once

#include "StringRange.h"
#include "Pin.h"

#include <cstring>
#include <Stream.h>

class SimpleOutputStream : public Stream {
public:
    SimpleOutputStream() = default;

    // SimpleOutputStream is not for Input; these are inherited without implementation:
    virtual int available() { return 0; }
    virtual int read() { return 0; }
    virtual int peek() { return 0; }

    // Output methods are inherited from Stream:
    // virtual void flush() = 0;
    // virtual size_t write(uint8_t value) = 0;

    virtual ~SimpleOutputStream() {}
};

Print& operator<<(Print& lhs, char c);
Print& operator<<(Print& lhs, const char* s);
Print& operator<<(Print& lhs, int value);
Print& operator<<(Print& lhs, unsigned int value);
Print& operator<<(Print& lhs, float value);
Print& operator<<(Print& lhs, StringRange range);
Print& operator<<(Print& lhs, const Pin& pin);

// Copyright (c) 2021 -  Stefan de Bruijn
// Use of this source code is governed by a GPLv3 license that can be found in the LICENSE file.

#include "SimpleOutputStream.h"

#include <cstring>
#ifdef ESP32
#    include <stdlib_noniso.h>  // dtostrf()
#endif

// Anonymous namespace to avoid name conflicts:
namespace {
    char* intToBuf(int value, char* dst) {
#ifdef ESP32
        return itoa(value, dst, 10);
#else
        _itoa_s(value, dst, 10, 10);
        return dst + strlen(dst);
#endif
    }

#ifdef ESP32
    const char* floatToString(float value, int numberDigits, int precision, char* buf) {
        // dtostrf() is an Arduino extension
        return dtostrf(value, numberDigits, precision, buf);
    }
#else
    const char* floatToString(float value, int numberDigits, int precision, char* buf) {
        if (isnan(value)) {
            return "NaN";
        } else if (isinf(value)) {
            return "Inf";
        } else {
            char fmt[10];
            fmt[0] = '%';
            fmt[1] = '0';

            char* next = intToBuf(numberDigits, fmt + 2);
            *next++ = '.';
            intToBuf(precision, next);

            snprintf(buf, sizeof(buf) - 1, fmt, value);
            return buf;
        }
    }
#endif
}

Print& operator<<(Print& lhs, char c) {
    lhs.write(c);
    return lhs;
}

Print& operator<<(Print& lhs, const char* s) {
    for (; *s; ++s) {
        lhs.write(*s);
    }
    return lhs;
}

Print& operator<<(Print& lhs, int value) {
    char buf[12];  // Up to 10 digits, possibly a -, plus a null
#ifdef ESP32
    itoa(value, buf, 10);
#else
    _itoa_s(value, buf, 10, 10);
#endif

    lhs << buf;

    return lhs;
}

Print& operator<<(Print& lhs, unsigned int value) {
    if (value == 0) {
        lhs.write('0');
        return lhs;
    }
    char  reverse[11];  // Up to 10 digits plus a null
    char* p = reverse;
    while (value) {
        *p++ = value % 10 + '0';
        value /= 10;
    }
    while (p > reverse) {
        lhs.write(*--p);
    }
    return lhs;
}

Print& operator<<(Print& lhs, float value) {
    char buf[30];  // that's already quite big
    lhs << floatToString(value, 4, 3, buf);
    return lhs;
}

Print& operator<<(Print& lhs, StringRange range) {
    for (auto ch : range) {
        lhs.write(ch);
    }
    return lhs;
}

Print& operator<<(Print& lhs, const Pin& pin) {
    lhs << pin.name();
    return lhs;
}

/*
char* SimpleOutputStream::intToBuf(int value, char* dst) {
#ifdef ESP32
    return itoa(value, dst, 10);
#else
    _itoa_s(value, dst, 10, 10);
    return dst + strlen(dst);
#endif
}

void SimpleOutputStream::add(const char* s) {
    for (; *s; ++s) {
        add(*s);
    }
}

void SimpleOutputStream::add(int value) {
    char buf[12];  // Up to 10 digits, possibly a -, plus a null
    intToBuf(value, buf);
    add(buf);
}

void SimpleOutputStream::add(unsigned int value) {
    if (value == 0) {
        add('0');
        return;
    }
    char  reverse[11];  // Up to 10 digits plus a null
    char* p = reverse;
    while (value) {
        *p++ = value % 10 + '0';
        value /= 10;
    }
    while (p > reverse) {
        add(*--p);
    }
}

#ifdef ESP32
void SimpleOutputStream::add(float value, int numberDigits, int precision) {
    char buf[30];
    // dtostrf() is an Arduino extension
    add(dtostrf(value, numberDigits, precision, buf));
}
#else
void SimpleOutputStream::add(float value, int numberDigits, int precision) {
    if (isnan(value)) {
        add("NaN");
    } else if (isinf(value)) {
        add("Inf");
    }

    char buf[30];  // that's already quite big
    char fmt[10];
    fmt[0] = '%';
    fmt[1] = '0';

    char* next = intToBuf(numberDigits, fmt + 2);
    *next++ = '.';
    intToBuf(precision, next);

    snprintf(buf, sizeof(buf) - 1, fmt, value);
    add(buf);
}
#endif

void SimpleOutputStream::add(StringRange range) {
    for (auto ch : range) {
        add(ch);
    }
}

void SimpleOutputStream::add(const Pin& pin) {
    add(pin.name());
}
*/

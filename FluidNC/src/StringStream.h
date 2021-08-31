// Copyright (c) 2021 Stefan de Bruijn
// Use of this source code is governed by a GPLv3 license that can be found in the LICENSE file.

#pragma once

#include "StringRange.h"
#include "SimpleOutputStream.h"

#include <Print.h>
#include <vector>

class StringStream : public Print {
    std::vector<char> data_;

public:
    size_t write(uint8_t value) override {
        data_.push_back(char(value));
        return 1;
    }
    StringRange str() const { return StringRange(data_.data(), data_.data() + data_.size()); }
};

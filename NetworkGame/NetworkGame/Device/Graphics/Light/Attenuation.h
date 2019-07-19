#pragma once
#include <array>

namespace Graphics {

struct Attenuation {
public:
    Attenuation() :Attenuation(0.0f, 1.0f) {}
    Attenuation(float minLength, float maxLength)
        :attenuation{ minLength,
        maxLength,
        1 / (minLength - maxLength),
        -maxLength / (minLength - maxLength) } {}
public:
    std::array<float, 4> attenuation;
};

} //Graphics 
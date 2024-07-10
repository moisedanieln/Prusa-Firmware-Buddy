#pragma once
#include <stdio.h>
#include "marlin_server_types/general_response.hpp"
#include "printers.h"
#include <cstring>
#include <color.hpp>

namespace filament {

struct Description {
    uint16_t nozzle;
    uint16_t nozzle_preheat;
    uint16_t heatbed;
    const char *name;
};

enum class Type : uint8_t {
    NONE = 0,
    PLA,
    PETG,
    ASA,
    PC,
    PVB,
    ABS,
    HIPS,
    PP,
    FLEX,
    PA,
    _last = PA
};

constexpr Type default_type = Type::PLA;
constexpr float cold_nozzle = 50.f;
constexpr float cold_bed = 45.f;

Type get_type(const char *name, size_t name_len);

const Description &get_description(Type type);
const char *get_name(Type type);

Type get_type_to_load();
void set_type_to_load(Type filament);

std::optional<Color> get_color_to_load();
void set_color_to_load(std::optional<Color> color);
}; // namespace filament

// memory_engine/memory_engine.h
#pragma once
#include <cstdint>     // ← Esta línea faltaba

namespace memory_engine {
    void init();
    bool write_float(uint64_t addr, float value);
}
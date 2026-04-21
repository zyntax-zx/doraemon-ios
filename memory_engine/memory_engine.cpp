#include "memory_engine.h"
#include "../utils/utils.h"
#include "../jit_helper/jit_helper.h"

namespace memory_engine {
    void init() {
        utils::log_to_file("[MEMORY] Engine inicializado (%s)", jit_helper::get_status().c_str());
    }

    bool write_float(uint64_t addr, float value) {
        utils::log_to_file("[MEMORY] Write 0x%llx = %.2f", addr, value);
        return true;
    }
}
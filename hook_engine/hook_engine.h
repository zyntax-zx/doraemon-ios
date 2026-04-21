#pragma once
#include <cstdint>

enum HookMode { MODE_RESEARCH, MODE_EXPLOIT, MODE_STEALTH };

namespace hook_engine {
    void init();
    bool add_brk_hook(uint64_t addr, void* replacement, void** original);
    bool hook_vtable(void* object_instance, uint32_t vtable_index, void* replacement, void** original);
    extern HookMode current_mode;
}
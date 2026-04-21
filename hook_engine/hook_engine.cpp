#include "hook_engine.h"
#include <ptrauth.h>
#include "../utils/utils.h"

HookMode hook_engine::current_mode = MODE_RESEARCH;

namespace hook_engine {
    void* strip_pac(void* ptr) {
        if (__builtin_available(iOS 12.0, *))
            return ptrauth_strip(ptr, ptrauth_key_function_pointer);
        return ptr;
    }

    bool add_brk_hook(uint64_t addr, void* repl, void** orig) {
        utils::log_to_file("[HOOK] BRK en 0x%llx", addr);
        return true;
    }

    bool hook_vtable(void* object_instance, uint32_t vtable_index, void* replacement, void** original) {
        if (!object_instance) return false;
        void** vtable = *(void***)object_instance;
        *original = vtable[vtable_index];
        vtable[vtable_index] = strip_pac(replacement);
        utils::log_to_file("[VTABLE] Hook índice %u en 0x%llx", vtable_index, (uint64_t)object_instance);
        return true;
    }

    void init() {
        utils::log_to_file("[HOOK] Engine inicializado (PAC + VTable support)");
    }
}
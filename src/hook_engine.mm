#import "nexus.h"
#include <dlfcn.h>
#include <mach-o/dyld.h>

// Fishhook (incluido inline para no depender de archivos externos)
struct rebinding {
    const char *name;
    void *replacement;
    void **replaced;
};

// Prototipo de rebind_symbols (asumiendo fishhook.c compilado junto)
extern "C" int rebind_symbols(struct rebinding rebindings[], size_t rebindings_nel);

void hook_engine_init(void) {
    nexus_log("HOOK", "Hook Engine inicializado.");
}

// Hook por símbolo exportado (fishhook)
bool hook_symbol(const char *symbol, void *replacement, void **original) {
    struct rebinding rb = { symbol, replacement, original };
    int result = rebind_symbols(&rb, 1);
    if (result == 0) {
        nexus_log("HOOK", "[OK] Símbolo '%s' hookeado.", symbol);
        return true;
    }
    nexus_log("HOOK", "[FAIL] No se pudo hookear '%s'.", symbol);
    return false;
}

// Hook por dirección directa (patch de instrucción ARM64 BL/BLR)
// En modo RESEARCH: solo loggea. En modo EXPLOIT: aplica el patch.
bool hook_by_offset(uintptr_t offset, void *replacement) {
    intptr_t slide = _dyld_get_image_vmaddr_slide(0);
    uintptr_t target = (uintptr_t)_dyld_get_image_header(0) + offset;
    // No aplicamos el hook en modo RESEARCH
    if (g_nexus_mode == NEXUS_MODE_RESEARCH) {
        nexus_log("HOOK", "[RESEARCH] Offset 0x%lx detectado (no modificado).", offset);
        return true;
    }
    nexus_log("HOOK", "[EXPLOIT] Hookeando offset 0x%lx...", offset);
    // Instrucción BL hacia nuestro replacement
    // En producción se calcularía el opcode BL correcto
    uintptr_t diff = (uintptr_t)replacement - target;
    uint32_t bl_instr = 0x94000000 | ((diff >> 2) & 0x3FFFFFF);
    extern bool mem_write(uintptr_t, const void*, size_t);
    return mem_write(target, &bl_instr, 4);
}

// Bool Hook: invierte el valor booleano en una dirección
bool hook_bool_at(uintptr_t addr) {
    uint8_t current = 0;
    extern bool mem_read(uintptr_t, void*, size_t);
    if (!mem_read(addr, &current, 1)) return false;
    uint8_t flipped = current ? 0 : 1;
    extern bool mem_write(uintptr_t, const void*, size_t);
    bool result = mem_write(addr, &flipped, 1);
    nexus_log("HOOK", "Bool en 0x%lx: %d -> %d", addr, current, flipped);
    return result;
}

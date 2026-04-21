// utils/utils.cpp
#include "utils.h"
#include <os/log.h>
#include <string>
#import <Foundation/Foundation.h>

namespace utils {
    static os_log_t log_handle = nullptr;

    void init_logging() {
        // Crear handle de os_log (más fiable que fopen en ESign)
        log_handle = os_log_create("com.enhanced.hacker", "default");

        NSString* bundleID = [[NSBundle mainBundle] bundleIdentifier];
        os_log(log_handle, "🚀 enhanced-ios-hacker.dylib CARGADO - Bundle: %{public}@", bundleID);
        os_log(log_handle, "✅ Logging iniciado con os_log (más estable en jailed)");
    }

    void log_to_file(const char* fmt, ...) {
        if (!log_handle) return;

        va_list args;
        va_start(args, fmt);
        char buffer[1024];
        vsnprintf(buffer, sizeof(buffer), fmt, args);
        va_end(args);

        os_log(log_handle, "%{public}s", buffer);
    }
}
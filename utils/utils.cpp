// utils/utils.cpp
#include "utils.h"
#include <stdio.h>
#include <stdarg.h>
#include <mach-o/dyld.h>
#include <string>
#import <Foundation/Foundation.h>

namespace utils {
    static FILE* log_file = nullptr;

    void init_logging() {
        // Obtener Bundle ID del app actual
        NSString* bundleID = [[NSBundle mainBundle] bundleIdentifier];
        utils::log_to_file("[BUNDLE] App detectado: %s", [bundleID UTF8String]);

        // Obtener carpeta Documents de forma más fiable
        NSArray* paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
        NSString* documentsPath = [paths firstObject];
        NSString* logPath = [documentsPath stringByAppendingPathComponent:@"ENHANCED_LOGS.TXT"];

        log_file = fopen([logPath UTF8String], "a");
        if (log_file) {
            utils::log_to_file("✅ Log iniciado en: %s", [logPath UTF8String]);
        } else {
            // fallback
            char path[1024];
            uint32_t size = sizeof(path);
            _NSGetExecutablePath(path, &size);
            std::string fallback = std::string(path) + "/../Documents/ENHANCED_LOGS.TXT";
            log_file = fopen(fallback.c_str(), "a");
        }
    }

    void log_to_file(const char* fmt, ...) {
        if (!log_file) return;
        va_list args;
        va_start(args, fmt);
        vfprintf(log_file, fmt, args);
        va_end(args);
        fprintf(log_file, "\n");
        fflush(log_file);
    }
}
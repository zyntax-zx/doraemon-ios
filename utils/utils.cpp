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
        // Intentamos obtener la carpeta Documents de forma oficial
        NSArray* paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
        NSString* documentsPath = [paths firstObject];
        NSString* logPath = [documentsPath stringByAppendingPathComponent:@"ENHANCED_LOGS.TXT"];

        log_file = fopen([logPath UTF8String], "a");

        if (log_file) {
            // Log inicial con información útil
            NSString* bundleID = [[NSBundle mainBundle] bundleIdentifier];
            log_to_file("🚀 enhanced-ios-hacker.dylib cargado");
            log_to_file("[BUNDLE] App actual: %s", [bundleID UTF8String]);
            log_to_file("[LOG] Archivo creado en: %s", [logPath UTF8String]);
        } else {
            // Fallback si falla
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
#pragma once
#import <Foundation/Foundation.h>
#include <stdint.h>
#include <stdbool.h>
#include <mach/mach.h>

// Versión del framework
#define NEXUS_VERSION "1.0.0"
#define NEXUS_PORT    27042

// Modos de operación
typedef enum {
    NEXUS_MODE_RESEARCH = 0,  // Solo loggea, no modifica
    NEXUS_MODE_EXPLOIT  = 1   // Modifica valores reales
} NexusMode;

// Sistema de logs unificado
void nexus_log(const char *module, const char *fmt, ...);

// Inicializadores de módulos
void core_server_init(void);
void memory_engine_init(void);
void hook_engine_init(void);
void module_analyzer_init(void);
void exploit_framework_init(void);

// Modo global
extern NexusMode g_nexus_mode;

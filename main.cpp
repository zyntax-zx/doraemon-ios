// main.cpp - VERSIÓN DE PRUEBA (visible)
#include "utils/utils.h"
#include "core_server/server.h"
#include "hook_engine/hook_engine.h"
#include "memory_engine/memory_engine.h"
#include "jit_helper/jit_helper.h"
#include <UIKit/UIKit.h>

extern "C" void init_exploit_framework();

__attribute__((constructor))
static void init_framework() {
    // TEST VISUAL - Esto debe aparecer en pantalla si el dylib se carga
    dispatch_async(dispatch_get_main_queue(), ^{
        UIAlertController *alert = [UIAlertController 
            alertControllerWithTitle:@"enhanced-ios-hacker"
            message:@"✅ DYLIB CARGADA CORRECTAMENTE\niOS 26 jailed - ESign"
            preferredStyle:UIAlertControllerStyleAlert];
        [alert addAction:[UIAlertAction actionWithTitle:@"OK" style:UIAlertActionStyleDefault handler:nil]];
        [[UIApplication sharedApplication].keyWindow.rootViewController presentViewController:alert animated:YES completion:nil];
    });

    utils::init_logging();
    utils::log_to_file("🚀 enhanced-ios-hacker.dylib CARGADO - Prueba visible activada");

    memory_engine::init();
    hook_engine::init();
    init_exploit_framework();
    core_server::start_tcp_server();

    utils::log_to_file("✅ Framework híbrido listo (ESign mode)");
}
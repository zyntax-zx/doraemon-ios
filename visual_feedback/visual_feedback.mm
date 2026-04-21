// visual_feedback/visual_feedback.mm
#import <UIKit/UIKit.h>
#include "../utils/utils.h"

extern "C" void show_load_toast() {
    dispatch_async(dispatch_get_main_queue(), ^{
        UIAlertController *alert = [UIAlertController 
            alertControllerWithTitle:@"✅ enhanced-ios-hacker"
            message:@"Dylib cargada correctamente\niOS 26 - ESign mode"
            preferredStyle:UIAlertControllerStyleAlert];
        
        [alert addAction:[UIAlertAction actionWithTitle:@"OK" 
            style:UIAlertActionStyleDefault handler:nil]];
        
        [[UIApplication sharedApplication].keyWindow.rootViewController 
            presentViewController:alert animated:YES completion:nil];
    });
}
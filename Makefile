include $(THEOS)/makefiles/common.mk

# Cambiamos de TWEAK a LIBRARY para que no pida plist de filtro
LIBRARY_NAME = enhanced-ios-hacker

enhanced-ios-hacker_FILES = main.cpp \
    core_server/server.cpp \
    hook_engine/hook_engine.cpp \
    memory_engine/memory_engine.cpp \
    exploit_framework/exploit_framework.mm \
    utils/utils.cpp \
    jit_helper/jit_helper.mm

ARCHS = arm64 arm64e
TARGET = iphone:clang:latest:15.0

enhanced-ios-hacker_CFLAGS = -fobjc-arc -std=c++20
enhanced-ios-hacker_LDFLAGS = -framework Foundation

include $(THEOS_MAKE_PATH)/library.mk

after-package::
	@echo "✅ enhanced-ios-hacker.dylib compilado correctamente (listo para ESign)"
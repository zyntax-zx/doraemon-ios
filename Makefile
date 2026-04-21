include $(THEOS)/makefiles/common.mk

TWEAK_NAME = enhanced-ios-hacker

# Solo los archivos que realmente existen
enhanced-ios-hacker_FILES = main.cpp \
    core_server/server.cpp \
    hook_engine/hook_engine.cpp \
    memory_engine/memory_engine.cpp \
    exploit_framework/exploit_framework.cpp \
    utils/utils.cpp

# Configuración moderna para iOS 26 jailed (arm64 + arm64e)
ARCHS = arm64 arm64e
TARGET = iphone:clang:latest:15.0

enhanced-ios-hacker_CFLAGS = -fobjc-arc -std=c++20
enhanced-ios-hacker_LDFLAGS = -framework Foundation

include $(THEOS_MAKE_PATH)/tweak.mk

after-package::
	@echo "✅ enhanced-ios-hacker.dylib compilado correctamente"
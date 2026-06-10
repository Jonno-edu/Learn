EMBEDDED_C_OBC_ROOT ?= ../..
FREERTOS_KERNEL_DIR ?= $(EMBEDDED_C_OBC_ROOT)/vendor/FreeRTOS-Kernel
FREERTOS_CONFIG_DIR ?= $(EMBEDDED_C_OBC_ROOT)/freertos
FREERTOS_POSIX_PORT_DIR := $(FREERTOS_KERNEL_DIR)/portable/ThirdParty/GCC/Posix

FREERTOS_INCLUDES := \
	-I$(FREERTOS_CONFIG_DIR) \
	-I$(FREERTOS_KERNEL_DIR)/include \
	-I$(FREERTOS_POSIX_PORT_DIR) \
	-I$(FREERTOS_POSIX_PORT_DIR)/utils

FREERTOS_KERNEL_SRCS := \
	$(FREERTOS_KERNEL_DIR)/tasks.c \
	$(FREERTOS_KERNEL_DIR)/queue.c \
	$(FREERTOS_KERNEL_DIR)/list.c \
	$(FREERTOS_KERNEL_DIR)/portable/MemMang/heap_4.c \
	$(FREERTOS_POSIX_PORT_DIR)/port.c \
	$(FREERTOS_POSIX_PORT_DIR)/utils/wait_for_event.c

FREERTOS_CFLAGS ?= -std=c11 -Wall -Wextra -Wno-unused-parameter -Wno-sign-conversion -O2
FREERTOS_LDLIBS ?= -pthread

FREERTOS_KERNEL_CHECK = test -d "$(FREERTOS_KERNEL_DIR)" || \
	(printf 'Missing FreeRTOS kernel at %s\nRun: rtk sh embedded-c-obc/scripts/setup_freertos_macos.sh\n' "$(FREERTOS_KERNEL_DIR)"; exit 2)

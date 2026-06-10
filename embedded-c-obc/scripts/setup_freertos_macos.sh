#!/bin/sh
set -eu

ROOT_DIR=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
KERNEL_DIR="$ROOT_DIR/vendor/FreeRTOS-Kernel"

if [ -d "$KERNEL_DIR/.git" ]; then
    git -C "$KERNEL_DIR" fetch --depth 1 origin main
    git -C "$KERNEL_DIR" checkout FETCH_HEAD
else
    mkdir -p "$ROOT_DIR/vendor"
    git clone --depth 1 https://github.com/FreeRTOS/FreeRTOS-Kernel.git "$KERNEL_DIR"
fi

printf 'FreeRTOS-Kernel ready at %s\n' "$KERNEL_DIR"
printf 'Run: rtk make -C embedded-c-obc/freertos smoke\n'

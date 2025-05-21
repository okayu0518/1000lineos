#!/bin/bash
set -xue

OBJCOPY=/bin/llvm-objcopy

# clangのパス (Ubuntuの場合は CC=clang)
CC=clang
CFLAGS="-std=c11 -O2 -g3 -Wall -Wextra --target=riscv32 -ffreestanding -nostdlib"

# build shell
$CC $CFLAGS -Wl,-Tuser.ld -Wl,-Map=shell.map -o shell.elf shell.c user.c common.c
$OBJCOPY --set-section-flags .bss=alloc,contents -O binary shell.elf shell.bin
# 生バイナリ形式の実行イメージを、C言語に埋め込める形式に変換する処理です。
$OBJCOPY -Ibinary -Oelf32-littleriscv shell.bin shell.bin.o

# build kernel
$CC $CFLAGS -Wl,-Tkernel.ld -Wl,-Map=kernel.map -o kernel.elf \
  kernel.c common.c shell.bin.o

QEMU=qemu-system-riscv32

# QEMUを起動
$QEMU -machine virt -bios default -nographic -serial mon:stdio --no-reboot \
  -kernel kernel.elf -monitor telnet:127.0.0.1:4444,server,nowait

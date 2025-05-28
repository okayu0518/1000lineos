#include "user.h"

extern char __stack_top[];

__attribute__((section(".text.start")))
__attribute__((naked))
void start(void) {
    __asm__ __volatile__(
        "mv sp, %[stack_top]\n"             // setup stack pointer
        "call main\n"                       // call main
        "call exit\n" ::[stack_top] "r"(__stack_top));
}

int syscall(int sysno, int arg0, int arg1, int arg2) {
    register int a0 __asm__("a0") = arg0;
    register int a1 __asm__("a1") = arg1;
    register int a2 __asm__("a2") = arg2;
    register int a3 __asm__("a3") = sysno;

    __asm__ __volatile__("ecall"                                // カーネルに処理を移譲する特殊命令
                         : "=r"(a0)                             // カーネルからの戻り値はa0に格納
                         : "r"(a0), "r"(a1), "r"(a2), "r"(a3)
                         : "memory");
    return a0;
}

void putchar(char ch) {
    syscall(SYS_PUTCHAR, ch, 0, 0); // システムコールを使って文字を出力
}

int getchar(void) {
    return syscall(SYS_GETCHAR, 0, 0, 0); // システムコールを使って文字を取得
}

__attribute__((noreturn)) void exit(void) {
    syscall(SYS_EXIT, 0, 0, 0); // システムコールを使ってプログラムを終了
    for (;;); // exitがもしも戻ってきたら無限ループ
}

int readfile(const char *filename, void *buf, int len) {
    return syscall(SYS_READFILE, (int) filename, (int) buf, len);
}

int writefile(const char *filename, const void *buf, int len) {
    return syscall(SYS_WRITEFILE, (int) filename, (int) buf, len);
}

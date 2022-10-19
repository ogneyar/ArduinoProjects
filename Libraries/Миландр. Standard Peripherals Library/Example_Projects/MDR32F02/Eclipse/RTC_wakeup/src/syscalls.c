#include <MLDR187_it.h>
#include <MLDR187_uart.h>
#include <MLDR187_gpio.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdlib.h>

#define DEFAULT_UART MDR_UART1

static void terminate(int code)
{
    (void)code;
    asm volatile("j .");
}

int sys_close(int fd)
{
    // Only stdout is supported in this environment.
    // Stdout file descriptor number is 1.
    // Trying to close anything except 1 is error.
    if (fd != 1)
        return -EBADF;

    // Do nothing.

    return 0; // success
}

ssize_t sys_write(int fd, char* buf, size_t n)
{
    // Only stdout is supported in this environment.
    // Stdout file descriptor number is 1.
    // Trying to write anything except 1 is error.
    if (fd != 1)
        return -EBADF;

    UART_SendBytes(DEFAULT_UART, (uint8_t*)buf, n);

    return n;
}

int sys_fstat(int fd, void* st)
{
    // Only stdout is supported in this environment.
    // Stdout file descriptor number is 1.
    // Trying to fstat anything except 1 is error.
    if (fd != 1)
        return -EBADF;

    // Note: real stats are not provided.
    // This implementation is just a minimal code
    // allowing write to stdout.
    memset(st, 0, sizeof(struct stat));

    return 0; // success
}

void sys_exit(int code)
{
    terminate(code);
    // never return
}

extern volatile size_t brk_base;
extern volatile size_t brk_size;

// brk syscall handler
size_t sys_brk(size_t addr)
{
    size_t newbrk = addr;
    if (addr < brk_base)
        newbrk = brk_base;
    else if (addr > brk_base + brk_size)
        newbrk = brk_base + brk_size;

    return newbrk;
}

void _exit(int code) {
    sys_exit(code);
    __builtin_unreachable();
}

int brk(void* addr) {
    void* newbrk = (void *) sys_brk((size_t)addr);
    return (newbrk == addr) ? 0 : -1;
}

static void *curbrk = 0;
void *_sbrk(intptr_t incr)
{
    if (curbrk == 0) {
        curbrk = (void *) sys_brk(0);
    }

    void *oldbrk = curbrk;
    void* addr = oldbrk + incr;
    void* newbrk = (void *) sys_brk((size_t) addr);
    if (newbrk == addr) {
        curbrk = newbrk;
        return oldbrk;
    } else {
        return (void *) -1;
    }
}

ssize_t _write (int fd, const void *buf, size_t nbyte) {
    return sys_write(fd, (char *)buf, nbyte);
}

int _close (int fd) {
    return sys_close(fd);
}

int _fstat(int fd, struct stat *buf) {
    return sys_fstat(fd, (char *)buf);
}

ssize_t _read (int fd, void *buf, size_t nbyte) {
    (void)fd;
    (void)buf;
    (void)nbyte;
    errno = ENOSYS;
    return -1;
}

int	_isatty (int fd) {
    (void)fd;
    errno = ENOSYS;
    return -1;
}

_off_t _lseek (int fd, _off_t offset, int whence) {
    (void)fd;
    (void)offset;
    (void)whence;
    errno = ENOSYS;
    return -1;
}

int _kill(int pid, int sig) {
    (void)pid;
    terminate(-sig);
    return 0;
}

int _getpid() {
    return 0;
}


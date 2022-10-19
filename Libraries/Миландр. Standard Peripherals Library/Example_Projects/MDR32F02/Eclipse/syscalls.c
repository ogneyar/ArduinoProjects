/**
  ******************************************************************************
  * @file    syscalls.c
  * @author  Milandr Application Team
  * @version V1.0.1
  * @date    01/06/2021
  * @brief   Implementation of newlib syscalls
  ******************************************************************************
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, MILANDR SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  */

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

caddr_t _sbrk(int nbytes)
{
  extern char __heap_top[];    // end of the bss section (start of heap)
  extern char __heap_limit[];  // end of the heap section (start of stack)
  char *prev_heap_end;
  static char *cur_heap_end = __heap_top;

  if(cur_heap_end + nbytes > __heap_limit)
  {
	  errno = ENOMEM;
	  return (caddr_t)-1;
  }

  prev_heap_end = cur_heap_end;
  cur_heap_end += nbytes;

  return prev_heap_end;
}

void _exit(int code) {
    sys_exit(code);
    __builtin_unreachable();
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
    errno = ENOSYS;
    return -1;
}

int	_isatty (int fd) {
    errno = ENOSYS;
    return -1;
}

_off_t _lseek (int fd, _off_t offset, int whence) {
    errno = ENOSYS;
    return -1;
}

int _kill(int pid, int sig) {
    terminate(-sig);
    return 0;
}

int _getpid() {
    return 0;
}


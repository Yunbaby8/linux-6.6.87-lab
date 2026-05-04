#include <linux/kernel.h>
#include <linux/syscalls.h>

SYSCALL_DEFINE0(my_syscall)
{
    printk(KERN_INFO "[my_syscall] called, return 42\n");
    return 42;
}


#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/jiffies.h>
#include <linux/utsname.h>

static int hello_kernel_show(struct seq_file *m, void *v)
{
    seq_printf(m, "Hello from kernel\n");
    seq_printf(m, "jiffies: %lu\n", jiffies);
    seq_printf(m, "release: %s\n", init_uts_ns.name.release);

    return 0;
}

static int hello_kernel_open(struct inode *inode, struct file *file)
{
    return single_open(file, hello_kernel_show, NULL);
}

static const struct proc_ops hello_kernel_proc_ops = {
    .proc_open    = hello_kernel_open,
    .proc_read    = seq_read,
    .proc_lseek   = seq_lseek,
    .proc_release = single_release,
};

static int __init hello_kernel_init(void)
{
    proc_create("hello_kernel", 0444, NULL, &hello_kernel_proc_ops);
    pr_info("hello_kernel: /proc/hello_kernel created\n");

    return 0;
}

fs_initcall(hello_kernel_init);

#include <linux/module.h>  

#include <linux/tty.h>      /* console_print() interface */

#include <linux/fs.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <asm/uaccess.h>
#include <asm/segment.h>
#include <linux/fcntl.h>
#include <linux/buffer_head.h>

#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/utsname.h>
#include <linux/version.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Erwan Daniel <daniel.erwan31@gmail.com>");
MODULE_DESCRIPTION("Epitech project");
MODULE_VERSION("1");

#define VERSION_RESET 0
#define VERSION_MODIFIED 1

struct version_string_holder {
  int  size;
  int  null_byte_pos;
  int  state;
  char *string;
  char *original;
};

struct version_string_holder version_string;

static ssize_t version_read(struct file * file, char * buf,
 size_t count, loff_t *ppos)
{
  int to_copy;

  if (*ppos >= version_string.null_byte_pos)
    return 0;
    
  to_copy = version_string.size - *ppos;
  if (count < to_copy)
    to_copy = count;
    
  memcpy(buf, &version_string.string[*ppos], to_copy);
  *ppos += to_copy;
  
  return to_copy;
}

static ssize_t version_write(struct file * file, const char * buf,
 size_t count, loff_t *ppos)
{
  int to_copy ;

  // No memory left
  if (*ppos >= version_string.size - 1) {
    return ENOSPC;
  }

  to_copy = version_string.size - 1 - *ppos;
  if (count < to_copy)
    to_copy = count - 1;
  printk("try to copy %d bytes at %d position, user asked %d bytes\n", to_copy, *ppos, count);
  memcpy(&version_string.string[*ppos], buf, to_copy);
  *ppos += to_copy;
  
  version_string.string[*ppos] = '\0';
  version_string.null_byte_pos = *ppos;
  version_string.state = VERSION_MODIFIED;
  
  return to_copy;
}

static long version_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
  if (cmd == VERSION_MODIFIED)
  {
    copy_to_user((int32_t*) arg, &version_string.state, sizeof(version_string.state));
  }
  else if (cmd == VERSION_RESET)
  {
    memcpy(version_string.string, version_string.original, version_string.size - 1);
    version_string.null_byte_pos = version_string.size - 1;
    version_string.state = VERSION_RESET;
  }
  else
    return -1;
  
  return 0;
}

static const struct file_operations version_fops = {
 .owner = THIS_MODULE,
 .read = version_read,
 .write = version_write,
 .unlocked_ioctl = version_ioctl
};

static struct miscdevice version_dev = {
 MISC_DYNAMIC_MINOR,
 "version",
 &version_fops
};

#define VERSION_STRING(state) state ? "VERSION_MODIFIED" : "VERSION_RESET"

static int __init version_init(void)
{
  int    ret;

  version_string.size = strlen(utsname()->version) + 2;
  version_string.string = kmalloc(version_string.size, GFP_KERNEL);
  version_string.original = kmalloc(version_string.size, GFP_KERNEL);
  
  memcpy(version_string.string, utsname()->version, version_string.size - 1);
  version_string.string[version_string.size - 2] = '\n';
  version_string.string[version_string.size - 1] = '\0';


  memcpy(version_string.original, version_string.string, version_string.size - 1);
  
  version_string.state = VERSION_RESET;
  version_string.null_byte_pos = version_string.size - 1;  

  ret = misc_register(&version_dev);
  if (ret)
    printk(KERN_ERR "Unable to register version misc device\n");
  return ret;
}

module_init(version_init);

static void __exit version_exit(void)
{
  kfree(version_string.string);
  misc_deregister(&version_dev);
}
module_exit(version_exit);

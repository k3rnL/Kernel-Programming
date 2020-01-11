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

struct version_string_holder {
  int  size;
  int  null_byte_pos;
  char *string;
};

struct version_string_holder version_string;

static ssize_t version_read(struct file * file, char * buf,
 size_t count, loff_t *ppos)
{
  int to_copy;

  if (*ppos >= version_string.null_byte_pos)
    return 0;
    
  to_copy = version_string.null_byte_pos - *ppos;
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
    to_copy = count;
  printk("try to copy %d bytes at %d position, user asked %d bytes\n", to_copy, *ppos, count);
  memcpy(&version_string.string[*ppos], buf, to_copy);
  *ppos += to_copy;
  
  version_string.string[*ppos] = '\0';
  version_string.null_byte_pos = *ppos;
  
  return to_copy;
}

static const struct file_operations version_fops = {
 .owner = THIS_MODULE,
 .read = version_read,
 .write = version_write
};

static struct miscdevice version_dev = {
 MISC_DYNAMIC_MINOR,
 "version",
 &version_fops
};

static int __init version_init(void)
{
  int    ret;

  version_string.size = strlen(utsname()->version) + 2;
  version_string.string = kmalloc(version_string.size, GFP_KERNEL);
  
  memcpy(version_string.string, utsname()->version, version_string.size - 1);
  
  version_string.string[version_string.size - 2] = '\n';
  version_string.string[version_string.size - 1] = '\0';

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

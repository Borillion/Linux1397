/** Issues:
** Why does count in memory_read, not correlate to memory_write count
** 
//read from userspace
[ 2524.083959] <1> strlen : 1612
[ 2524.083963] <1> count : 7

//odd output for seemingly no reason//
[ 2528.442425] <1> read strlen : 0
[ 2528.442430] <1> read count : 65536

//write to userspace
[ 2528.442443] <1> read strlen : 7
[ 2528.442445] <1> read count : 65536

**/

/* <memory initial> */
/* Necessary includes for device drivers */
#include <linux/version.h>
#include <linux/init.h>
// #include <linux/config.h>
#include <linux/module.h>
#include <linux/kernel.h> /* printk() */
#include <linux/slab.h> /* kmalloc() */
#include <linux/fs.h> /* everything... */
#include <linux/errno.h> /* error codes */
#include <linux/types.h> /* size_t */
#include <linux/proc_fs.h>
#include <linux/fcntl.h> /* O_ACCMODE */
// #include <asm/system.h> /* cli(), *_flags */
#include <asm/switch_to.h>
#include <asm/uaccess.h> /* copy_from/to_user */

MODULE_LICENSE("Dual BSD/GPL");

/* Declaration of memory.c functions */
int memory_open(struct inode *inode, struct file *filp);
int memory_release(struct inode *inode, struct file *filp);
ssize_t memory_read(struct file *filp, char *buf, size_t count, loff_t *f_pos);
ssize_t memory_write(struct file *filp, char *buf, size_t count, loff_t *f_pos);
void memory_exit(void);
int memory_init(void);

/* Structure that declares the usual file */
/* access functions */
struct file_operations memory_fops = {
  read: memory_read,
  write: memory_write,
  open: memory_open,
  release: memory_release
};

/* Declaration of the init and exit functions */
module_init(memory_init);
module_exit(memory_exit);

/* Global variables of the driver */
/* Major number */
int memory_major = 60;
/* Buffer to store data */
char *memory_buffer;
/* read length from user input */
int read_length;

/* <memory init module> */
int memory_init(void) {
  int result;

  /* Registering device */
  result = register_chrdev(memory_major, "memory", &memory_fops);
  if (result < 0) {
    printk(
      "<1>memory: cannot obtain major number %d\n", memory_major);
    return result;
  }

  printk("<1>Inserting memory module\n"); 
  return 0;

}

/* <memory exit module> */
void memory_exit(void) {
  /* Freeing the major number */
  unregister_chrdev(memory_major, "memory");

  /* Freeing buffer memory */
  if (memory_buffer) {
    kfree(memory_buffer);
  }

  printk("<1>Removing memory module\n");

}
/* <memory open> */
int memory_open(struct inode *inode, struct file *filp) {

  /* Success */
  return 0;
}

/* <memory release> */
int memory_release(struct inode *inode, struct file *filp) {
 
  /* Success */
  return 0;
}

/* <memory read> */
ssize_t memory_read(struct file *filp, char *buf, 
                    size_t count, loff_t *f_pos) { 
 
  //uncomment for testing
  //printk("<1> read strlen : %d\n", strlen(buf));
  //printk("<1> read count : %d\n", count);

  /* Transfering data to user space */ 
  //dest, source, how many
  copy_to_user(buf,memory_buffer,read_length);

  /* Changing reading position as best suits */ 
  if (*f_pos == 0) {
  //set the position to location of read index 
    *f_pos += read_length; 
    return read_length; 

  } else { 
    return 0; 
  }
}

/* <memory write> */
ssize_t memory_write( struct file *filp, char *buf,
                      size_t count, loff_t *f_pos) {
  int result = 0;
     
  //uncomment for testing
  //printk("<1> strlen : %d\n", strlen(buf));
  //printk("<1> count : %d\n", count);
  
  //allocate the size of kmemory, indicated by count
  //asign to memory_buffer
  /* Allocating memory for the buffer */
  memory_buffer = kmalloc(count, GFP_KERNEL); 
  if (!memory_buffer) { 
    //if memory_buffer pointer is null
   //allocation failed
    printk("<1>dynamic memory allocation failed!\n");
    result = -ENOMEM;
    goto fail; 
  } 
  //if alloc successful fill with 0's
  memset(memory_buffer, 0, count);
  //copy from term_buffer into memory_buffer
  //destination, source, number
  copy_from_user(memory_buffer,buf,count);
  read_length = count;
  //return number written
  return count;

  //alloc of memory failed 
  fail: 
    memory_exit(); 
    return result;

}


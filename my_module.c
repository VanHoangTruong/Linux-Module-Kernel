#include <linux/module.h>
#include <linux/random.h>
#include <linux/init.h>
#include <linux/device.h>         // Header to support the kernel Driver Model
#include <linux/kernel.h>         // Contains types, macros, functions for the kernel
#include <linux/fs.h>             // Header for the Linux file system support
#include <linux/uaccess.h>          // Required for the copy to user function

MODULE_LICENSE("GPL");          ///< The license type -- this affects available functionality
MODULE_AUTHOR("Truong Van Hoang");    ///< The author -- visible when you use modinfo
MODULE_DESCRIPTION("random number");  ///< The description -- see modinfo
MODULE_VERSION("0.1");            ///< A version number to inform users

static int Major;
static ssize_t randomNumber(struct file *,char *, size_t , loff_t *);
static struct class* charClass   = NULL;
static struct device* charDevice = NULL;
static struct file_operations file_ops={
     .owner=THIS_MODULE,
     .read=randomNumber,   
};

static ssize_t randomNumber(struct file *filp,char *buffer, size_t length, loff_t *offset)
{
	int randomNumber;
	get_random_bytes(&randomNumber,sizeof(randomNumber));
	int ret = copy_to_user(buffer,&randomNumber,4);
	if (ret == 0){
		printk(KERN_ALERT "Sent %ld character to the user\n ",sizeof(randomNumber));
		return sizeof(randomNumber);
	} else {
		printk(KERN_ALERT "Failed to send!\n");
		return -EFAULT;
	}
}

static int mod_init(void){
	Major=register_chrdev(0,"my_module",&file_ops);   
	if(Major < 0)
	{
		printk(KERN_ALERT "Register failed!!!\n");
		return Major;
	}	
	
	printk(KERN_ALERT "Register successfull!!!\n");
	
	charClass = class_create(THIS_MODULE,"1612857");
	if(IS_ERR(charClass)){
		unregister_chrdev(Major,"my_module");
		printk(KERN_ALERT "Failed to Register device class\n");
		return PTR_ERR(charClass);
	}
	printk(KERN_ALERT "device class Register correctly\n");
	charDevice = device_create(charClass, NULL, MKDEV(Major,0),NULL,"my_module");
	if(IS_ERR(charDevice)){
		class_destroy(charClass);
		unregister_chrdev(Major,"my_module");
		printk(KERN_ALERT "Failed to create device\n");
		return PTR_ERR(charDevice);
	}
	printk(KERN_ALERT "device class created correctly\n");
	
	return 0;
}

static void mod_exit(void){
	
	device_destroy(charClass,MKDEV(Major,0));
	class_unregister(charClass);
	class_destroy(charClass);
	
	unregister_chrdev(Major,"my_module");       
    printk(KERN_ALERT "Goodbye from LKM\n");
}

module_init(mod_init);
module_exit(mod_exit);

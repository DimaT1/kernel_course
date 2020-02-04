#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <linux/uaccess.h>

#define DEVICE_MAJOR 42
#define DEVICE_MAX_MINORS 1
#define DEVICE_NAME "uglyrandom"
#define BUF_LEN 5

struct random_generator {
	unsigned int x;
	unsigned int a;
	unsigned int c;
	unsigned int m;
};

static struct random_generator generator;

struct device_data {
	struct cdev cdev;
	size_t size;
	char buffer[BUF_LEN];
};

static struct device_data data;

static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *file, char __user *user_buffer,
			   size_t size, loff_t *offset);
static ssize_t device_write(struct file *file, const char __user *user_buffer,
			    size_t size, loff_t *offset);

const struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = device_open,
	.read = device_read,
	.write = device_write,
	.release = device_release,
};

void generate_new(struct random_generator *generator)
{
	generator->x =
		(generator->a * generator->x + generator->c) % generator->m;
}

static int device_open(struct inode *inode, struct file *file)
{
	struct device_data *buf_data =
		container_of(inode->i_cdev, struct device_data, cdev);
	file->private_data = buf_data;
	try_module_get(THIS_MODULE);
	return 0;
}

static ssize_t device_read(struct file *file, char __user *user_buffer,
			   size_t size, loff_t *offset)
{
	int i;
	struct device_data *buf_data = (struct device_data *)file->private_data;
	ssize_t len = (ssize_t)(buf_data->size - *offset < size ?
					buf_data->size - *offset :
					size);

	if (len <= 0)
		return 0;

	generate_new(&generator);

	for (i = 0; i < 4; ++i) {
		data.buffer[i] = (generator.x >> (8 * i)) & 0xff;
	}

	if (copy_to_user(user_buffer, buf_data->buffer + *offset, len))
		return -EFAULT;

	*offset += len;
	return len;
}

static ssize_t device_write(struct file *file, const char __user *user_buffer,
			    size_t size, loff_t *offset)
{
	int i;
	struct device_data *buf_data = (struct device_data *)file->private_data;
	ssize_t len = (ssize_t)(buf_data->size - *offset < size ?
					buf_data->size - *offset :
					size);
	if (len <= 0)
		return 0;

	if (copy_from_user(buf_data->buffer + *offset, user_buffer, len))
		return -EFAULT;

	generator.x = 0;
	for (i = 0; i < 4; ++i) {
		generator.x += data.buffer[i] << (8 * i);
	}

	*offset += len;
	return len;
}

static int device_release(struct inode *inode, struct file *file)
{
	module_put(THIS_MODULE);
	return 0;
}

static int __init device_init(void)
{
	int err = register_chrdev_region(MKDEV(DEVICE_MAJOR, 0),
					 DEVICE_MAX_MINORS, DEVICE_NAME);
	if (err != 0) {
		printk(KERN_ERR "uglyrandom: Error when trying to insert\n");
		return err;
	}

	printk(KERN_INFO "uglyrandom: Inserted\n");

	data.size = BUF_LEN;

	generator.x = 42;
	generator.a = 1103515245;
	generator.c = 12345;
	generator.m = 2147483648;

	data.buffer[4] = '\0';

	cdev_init(&data.cdev, &fops);
	cdev_add(&data.cdev, MKDEV(DEVICE_MAJOR, 0), 1);

	return 0;
}

static void __exit device_cleanup(void)
{
	printk(KERN_INFO "uglyrandom: Removed\n");
	unregister_chrdev_region(MKDEV(DEVICE_MAJOR, 0), DEVICE_MAX_MINORS);
	cdev_del(&data.cdev);
}

module_init(device_init);
module_exit(device_cleanup);

MODULE_DESCRIPTION("A simple linear congruential generator");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Dmitry Torilov <dmtorilov@edu.hse.ru>");
MODULE_SUPPORTED_DEVICE(DEVICE_NAME);

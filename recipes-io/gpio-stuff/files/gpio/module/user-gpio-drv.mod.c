#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xf1939dfb, "module_layout" },
	{ 0xdbd06b7c, "class_destroy" },
	{ 0xbf791ed0, "device_destroy" },
	{ 0x7485e15e, "unregister_chrdev_region" },
	{ 0xd28894cc, "device_create" },
	{ 0xd611e41d, "cdev_del" },
	{ 0xe7516dad, "__class_create" },
	{ 0xf1cb35c7, "cdev_add" },
	{ 0xd5febbbb, "cdev_init" },
	{ 0xd8e484f0, "register_chrdev_region" },
	{ 0x29537c9e, "alloc_chrdev_region" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0x27e1a049, "printk" },
	{ 0x432fd7f6, "__gpio_set_value" },
	{ 0xfa2a45e, "__memzero" },
	{ 0x67c2fa54, "__copy_to_user" },
	{ 0x6c8d5ae8, "__gpio_get_value" },
	{ 0xa8f59416, "gpio_direction_output" },
	{ 0xfe990052, "gpio_free" },
	{ 0x47229b5c, "gpio_request" },
	{ 0xdd0a2ba2, "strlcat" },
	{ 0x73e20c1c, "strlcpy" },
	{ 0x12da5bb2, "__kmalloc" },
	{ 0x97255bdf, "strlen" },
	{ 0xfbc74f64, "__copy_from_user" },
	{ 0x65d6d0f0, "gpio_direction_input" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "5B327B04F67723173545FCB");

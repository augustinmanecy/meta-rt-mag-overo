#############################################################################
#
#	Makefile for building a gpio demo application making simple gpio operations
#
#############################################################################

APPNAME		= DemoGPIO

OVEROTOP	= /home/gus/yocto/overo/build
CROSS_COMPILE	?= $(OVEROTOP)/tmp/sysroots/x86_64-linux/usr/bin/armv7a-vfp-neon-poky-linux-gnueabi/arm-poky-linux-gnueabi-

CC		= $(CROSS_COMPILE)gcc

CFLAGS += \
	-std=gnu99 \
	-Wall \
	-Wimplicit \
	-Wpointer-arith \
	-Wswitch \
	-Wredundant-decls \
	-Wreturn-type \
	-Wshadow \
	-Wunused \
	-Wcast-qual \
	-Wnested-externs \
	-Wmissing-prototypes \
	-Wstrict-prototypes \
	-Wmissing-declarations \
	-I ../lib

DEP_OUTPUT_OPTION = -MMD -MF $(@:.o=.d)

OBJ_FILES = "$(APPNAME).o"

$(APPNAME) : $(OBJ_FILES)
	@echo "Creating executable $@ ..."
	$(CC) -o $@ $^ -lgpio
# $(CC) -o $@ -L ../lib $^ -lgpio

.PHONY: %.d
%.d: ;

%.o : %.c %.d
	@echo "Compiling $< ..."
	$(COMPILE.c) $(DEP_OUTPUT_OPTION) $(OUTPUT_OPTION) $<

clean:
	rm -rf $(APPNAME) *.o *.d

DEP_FILES = $(strip $(OBJ_FILES:.o=.d))

ifneq ($(DEP_FILES),)
ifeq ($(strip $(filter clean%, $(MAKECMDGOALS))),)
-include $(DEP_FILES)
endif
endif


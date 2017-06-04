################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: RPICAMG+

# Tool invocations
RPICAMG+: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross G++ Linker'
	arm-linux-gnueabihf-g++ -L/home/raspberry/Documentos/rpi/rootfs/usr/lib -L/home/raspberry/Documentos/rpi/rootfs/lib/arm-linux-gnueabihf -L/home/raspberry/Documentos/rpi/rootfs/usr/local/lib -L/home/raspberry/Documentos/rpi/tools/arm-bcm2708/gcc-linaro-4.9-2016.02-x86_64_arm-linux-gnueabihf/arm-linux-gnueabihf/libc/lib -L/home/raspberry/Documentos/rpi/rootfs/usr/lib/arm-linux-gnueabihf -L/home/raspberry/Documentos/rpi/rootfs/lib --sysroot=/home/raspberry/Documentos/rpi/rootfs/ -Xlinker -rpath "/home/raspberry/Documentos/rpi/rootfs/lib/arm-linux-gnueabihf/" -Xlinker -rpath "/home/raspberry/Documentos/rpi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian/arm-linux-gnueabihf/libc" -Xlinker -rpath "/home/raspberry/Documentos/rpi/rootfs/lib/arm-linux-gnueabihf" -Xlinker -rpath "/home/raspberry/Documentos/rpi/rootfs/usr/lib/arm-linux-gnueabihf/neon/vfp" -Xlinker -rpath "/home/raspberry/Documentos/rpi/rootfs/usr/lib/arm-linux-gnueabihf" -Xlinker -rpath "/home/raspberry/Documentos/rpi/rootfs/usr/lib/" -Xlinker -rpath "/home/raspberry/Documentos/rpi/rootfs/usr/local/lib/" -o "RPICAMG+" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C++_DEPS)$(OBJS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(CXX_DEPS)$(C_UPPER_DEPS) RPICAMG+
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

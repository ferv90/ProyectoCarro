################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/RPICAMG+.cpp 

OBJS += \
./src/RPICAMG+.o 

CPP_DEPS += \
./src/RPICAMG+.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabihf-g++ -std=c++0x -D__GXX_EXPERIMENTAL_CXX0X__ -I/home/raspberry/Documentos/rpi/rootfs/usr/local/include/opencv -I/home/raspberry/Documentos/rpi/rootfs/usr/local/include -I/home/raspberry/Documentos/rpi/rootfs/usr/include/arm-linux-gnueabihf -I/home/raspberry/Documentos/rpi/tools/arm-bcm2708/gcc-linaro-4.9-2016.02-x86_64_arm-linux-gnueabihf/arm-linux-gnueabihf/libc/lib -I/home/raspberry/Documentos/rpi/rootfs/usr/local/include/opencv2 -I/home/raspberry/Documentos/rpi/rootfs/usr/include -O0 -g3 -Wall -Wextra -c -fmessage-length=0  --sysroot=/home/raspberry/Documentos/rpi/rootfs/ -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



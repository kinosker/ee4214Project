################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/TFT_Draw.c \
../src/myBarrier.c \
../src/platform.c \
../src/project.c 

LD_SRCS += \
../src/lscript.ld 

OBJS += \
./src/TFT_Draw.o \
./src/myBarrier.o \
./src/platform.o \
./src/project.o 

C_DEPS += \
./src/TFT_Draw.d \
./src/myBarrier.d \
./src/platform.d \
./src/project.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MicroBlaze gcc compiler'
	mb-gcc -Wall -O0 -g3 -c -fmessage-length=0 -D __XMK__ -I../../xilkernel_bsp_0/microblaze_0/include -mlittle-endian -mcpu=v9.3 -mxl-soft-mul -Wl,--no-relax -ffunction-sections -fdata-sections -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



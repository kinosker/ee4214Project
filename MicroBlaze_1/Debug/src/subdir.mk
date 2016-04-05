################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/ballControl.c \
../src/myBoundaryChecker.c \
../src/myTimer.c \
../src/platform.c \
../src/project_core1.c 

LD_SRCS += \
../src/lscript.ld 

OBJS += \
./src/ballControl.o \
./src/myBoundaryChecker.o \
./src/myTimer.o \
./src/platform.o \
./src/project_core1.o 

C_DEPS += \
./src/ballControl.d \
./src/myBoundaryChecker.d \
./src/myTimer.d \
./src/platform.d \
./src/project_core1.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MicroBlaze gcc compiler'
	mb-gcc -Wall -O0 -g3 -I"C:\Users\KaiHsiang\Desktop\EE4214_Workspace\Lab1\MulticoreProcessor\MulticoreProcessor.sdk\4214_project\MicroBlaze_1\myCommon" -c -fmessage-length=0 -D __XMK__ -I../../xilkernel_bsp_1/microblaze_1/include -mlittle-endian -mcpu=v9.3 -mxl-soft-mul -Wl,--no-relax -ffunction-sections -fdata-sections -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../myCommon/myBarrier.c 

OBJS += \
./myCommon/myBarrier.o 

C_DEPS += \
./myCommon/myBarrier.d 


# Each subdirectory must supply rules for building sources it contributes
myCommon/%.o: ../myCommon/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MicroBlaze gcc compiler'
	mb-gcc -Wall -O0 -g3 -I"C:\Users\KaiHsiang\Desktop\EE4214_Workspace\Lab1\MulticoreProcessor\MulticoreProcessor.sdk\4214_project\MicroBlaze_0\myCommon" -c -fmessage-length=0 -D __XMK__ -I../../xilkernel_bsp_0/microblaze_0/include -mlittle-endian -mcpu=v9.3 -mxl-soft-mul -Wl,--no-relax -ffunction-sections -fdata-sections -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



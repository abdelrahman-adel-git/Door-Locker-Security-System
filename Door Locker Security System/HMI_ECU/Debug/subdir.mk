################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HMI_ECU.c \
../Timer1.c \
../my_gpio.c \
../my_keypad.c \
../my_lcd.c \
../my_uart.c 

OBJS += \
./HMI_ECU.o \
./Timer1.o \
./my_gpio.o \
./my_keypad.o \
./my_lcd.o \
./my_uart.o 

C_DEPS += \
./HMI_ECU.d \
./Timer1.d \
./my_gpio.d \
./my_keypad.d \
./my_lcd.d \
./my_uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



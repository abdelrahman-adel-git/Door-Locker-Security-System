################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Buzzer.c \
../Control_ECU.c \
../Timer0.c \
../Timer1.c \
../external_eeprom.c \
../my_dcMotor.c \
../my_gpio.c \
../my_twi.c \
../my_uart.c 

OBJS += \
./Buzzer.o \
./Control_ECU.o \
./Timer0.o \
./Timer1.o \
./external_eeprom.o \
./my_dcMotor.o \
./my_gpio.o \
./my_twi.o \
./my_uart.o 

C_DEPS += \
./Buzzer.d \
./Control_ECU.d \
./Timer0.d \
./Timer1.d \
./external_eeprom.d \
./my_dcMotor.d \
./my_gpio.d \
./my_twi.d \
./my_uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



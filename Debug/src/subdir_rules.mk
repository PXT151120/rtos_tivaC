################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: GNU Compiler'
	"C:/ti/ccs1240/ccs/tools/compiler/gcc-arm-none-eabi-9-2019-q4-major/bin/arm-none-eabi-gcc-9.2.1.exe" -c -mcpu=cortex-m4 -march=armv7e-m -mthumb -DPART_TM4C123GH6PM -I"C:/ti/TivaWare_C_Series-2.2.0.295" -I"D:/Work_Program_files/TIVA_C/Code_Composer_Studio/rtos_tivaC" -I"D:/Work_Program_files/TIVA_C/Code_Composer_Studio/rtos_tivaC/CMSIS/Include" -I"D:/Work_Program_files/TIVA_C/Code_Composer_Studio/rtos_tivaC/ek-tm4c123gxl" -I"D:/Work_Program_files/TIVA_C/Code_Composer_Studio/rtos_tivaC/inc" -I"D:/Work_Program_files/TIVA_C/Code_Composer_Studio/rtos_tivaC/src" -I"C:/ti/ccs1240/ccs/tools/compiler/gcc-arm-none-eabi-9-2019-q4-major/arm-none-eabi/include" -O0 -ffunction-sections -fdata-sections -g -gdwarf-3 -gstrict-dwarf -Wall -specs="nosys.specs" -MMD -MP -MF"src/$(basename $(<F)).d_raw" -MT"$(@)" -std=c99 $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '



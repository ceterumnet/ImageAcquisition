################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../windows/vc9/IPixInsightCamera.cpp 

OBJS += \
./windows/vc9/IPixInsightCamera.o 

CPP_DEPS += \
./windows/vc9/IPixInsightCamera.d 


# Each subdirectory must supply rules for building sources it contributes
windows/vc9/%.o: ../windows/vc9/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -c -pipe -arch x86_64 -mmacosx-version-min=10.5 -Xarch_x86_64 -D__PCL_MACOSX -D_REENTRANT -I/Users/draphael/PCL/include -O0 -g3 -Wall -c -fmessage-length=0 -Wno-parentheses -MMD -MP -MF -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../test/TestCameraItem.cpp 

OBJS += \
./test/TestCameraItem.o 

CPP_DEPS += \
./test/TestCameraItem.d 


# Each subdirectory must supply rules for building sources it contributes
test/%.o: ../test/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -c -pipe -arch x86_64 -mmacosx-version-min=10.5 -Xarch_x86_64 -D__PCL_MACOSX -D_REENTRANT -I/Users/draphael/PCL/include -I/usr/local/include -O0 -g3 -Wall -fvisibility=hidden -fvisibility-inlines-hidden -fnon-call-exceptions -c -fmessage-length=0 -Wno-parentheses -MMD -MP -MF -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o   "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



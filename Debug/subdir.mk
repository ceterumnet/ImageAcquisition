################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CameraDialog.cpp \
../ExposeImageInstance.cpp \
../ExposeImageInterface.cpp \
../ExposeImageParameters.cpp \
../ExposeImageProcess.cpp \
../ImageAcquisisitionSettingsParameters.cpp \
../ImageAcquisitionModule.cpp \
../ImageAcquisitionSettingsInstance.cpp \
../ImageAcquisitionSettingsInterface.cpp \
../ImageAcquisitionSettingsProcess.cpp 

OBJS += \
./CameraDialog.o \
./ExposeImageInstance.o \
./ExposeImageInterface.o \
./ExposeImageParameters.o \
./ExposeImageProcess.o \
./ImageAcquisisitionSettingsParameters.o \
./ImageAcquisitionModule.o \
./ImageAcquisitionSettingsInstance.o \
./ImageAcquisitionSettingsInterface.o \
./ImageAcquisitionSettingsProcess.o 

CPP_DEPS += \
./CameraDialog.d \
./ExposeImageInstance.d \
./ExposeImageInterface.d \
./ExposeImageParameters.d \
./ExposeImageProcess.d \
./ImageAcquisisitionSettingsParameters.d \
./ImageAcquisitionModule.d \
./ImageAcquisitionSettingsInstance.d \
./ImageAcquisitionSettingsInterface.d \
./ImageAcquisitionSettingsProcess.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -c -pipe -arch x86_64 -mmacosx-version-min=10.5 -Xarch_x86_64 -D__PCL_MACOSX -D_REENTRANT -I/Users/draphael/PCL/include -O0 -g3 -Wall -c -fmessage-length=0 -Wno-parentheses -MMD -MP -MF -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



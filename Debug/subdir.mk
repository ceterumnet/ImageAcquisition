################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CameraData.cpp \
../CameraDialog.cpp \
../CameraItem.cpp \
../DeviceItem.cpp \
../ExposeImageInstance.cpp \
../ExposeImageInterface.cpp \
../ExposeImageParameters.cpp \
../ExposeImageProcess.cpp \
../FilterWheelData.cpp \
../FilterWheelItem.cpp \
../ImageAcquisisitionSettingsParameters.cpp \
../ImageAcquisitionModule.cpp \
../ImageAcquisitionSession.cpp \
../ImageAcquisitionSessionInstance.cpp \
../ImageAcquisitionSessionInterface.cpp \
../ImageAcquisitionSessionParameters.cpp \
../ImageAcquisitionSessionProcess.cpp \
../ImageAcquisitionSettingsInstance.cpp \
../ImageAcquisitionSettingsInterface.cpp \
../ImageAcquisitionSettingsProcess.cpp \
../parsers.cpp 

OBJS += \
./CameraData.o \
./CameraDialog.o \
./CameraItem.o \
./DeviceItem.o \
./ExposeImageInstance.o \
./ExposeImageInterface.o \
./ExposeImageParameters.o \
./ExposeImageProcess.o \
./FilterWheelData.o \
./FilterWheelItem.o \
./ImageAcquisisitionSettingsParameters.o \
./ImageAcquisitionModule.o \
./ImageAcquisitionSession.o \
./ImageAcquisitionSessionInstance.o \
./ImageAcquisitionSessionInterface.o \
./ImageAcquisitionSessionParameters.o \
./ImageAcquisitionSessionProcess.o \
./ImageAcquisitionSettingsInstance.o \
./ImageAcquisitionSettingsInterface.o \
./ImageAcquisitionSettingsProcess.o \
./parsers.o 

CPP_DEPS += \
./CameraData.d \
./CameraDialog.d \
./CameraItem.d \
./DeviceItem.d \
./ExposeImageInstance.d \
./ExposeImageInterface.d \
./ExposeImageParameters.d \
./ExposeImageProcess.d \
./FilterWheelData.d \
./FilterWheelItem.d \
./ImageAcquisisitionSettingsParameters.d \
./ImageAcquisitionModule.d \
./ImageAcquisitionSession.d \
./ImageAcquisitionSessionInstance.d \
./ImageAcquisitionSessionInterface.d \
./ImageAcquisitionSessionParameters.d \
./ImageAcquisitionSessionProcess.d \
./ImageAcquisitionSettingsInstance.d \
./ImageAcquisitionSettingsInterface.d \
./ImageAcquisitionSettingsProcess.d \
./parsers.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -c -pipe -arch x86_64 -mmacosx-version-min=10.5 -Xarch_x86_64 -D__PCL_MACOSX -D_REENTRANT -I/Users/draphael/PCL/include -I/usr/local/include -O0 -g3 -Wall -fvisibility=hidden -fvisibility-inlines-hidden -fnon-call-exceptions -c -fmessage-length=0 -Wno-parentheses -MMD -MP -MF -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/3D\ game.cpp \
../src/Game.cpp \
../src/Map.cpp \
../src/Player.cpp \
../src/Ray.cpp 

OBJS += \
./src/3D\ game.o \
./src/Game.o \
./src/Map.o \
./src/Player.o \
./src/Ray.o 

CPP_DEPS += \
./src/3D\ game.d \
./src/Game.d \
./src/Map.d \
./src/Player.d \
./src/Ray.d 


# Each subdirectory must supply rules for building sources it contributes
src/3D\ game.o: ../src/3D\ game.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/3D game.d" -MT"src/3D\ game.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



vpath %.cpp src/
TARGET= project1
INCLUDES= -I inc/

CC = g++
FLAGS= -D$(TARGET)
CPPLIBS= -L/usr/lib -lopencv_core -lopencv_flann -lopencv_video
LDFLAGS = -lpthread -lrt -lm -lwiringPi -L/usr/lib -lopencv_core -lopencv_flann -lopencv_video
SRC := main.cpp capture.cpp motor.cpp ultrasonic_sensor.cpp mysemaphores.cpp scheduler.cpp
OBJ := $(SRC:.cpp=.o)

build: 	$(OBJ)
	$(CC) -g $(CFLAGS) $(FLAGS) $(OBJ) -o $(TARGET) $(LDFLAGS) `pkg-config --libs opencv` $(CPPLIBS)

	
clean:
	rm -f $(TARGET) *.o *.elf *.ma




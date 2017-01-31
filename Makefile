all: mem

OBJS = main.o Memory_Manager_Unit.o Utilities.o

SOURCE	= main.cpp Memory_Manager_Unit.cpp Utilities.cpp

HEADER  = Memory_Manager_Unit.h Utilities.h

OUT = virtual_memory


CC	= g++
FLAGS	= -c

mem: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT)


main.o: main.cpp
		$(CC) $(FLAGS) main.cpp

Memory_Manager_Unit.o: Memory_Manager_Unit.cpp
		$(CC) $(FLAGS) Memory_Manager_Unit.cpp

Utilities.o: Utilities.cpp
		$(CC) $(FLAGS) Utilities.cpp


clean:
	rm -f $(OBJS) $(OUT)

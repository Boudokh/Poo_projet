CPP=g++ --std=c++11 -Wall
all: Board
tp: board_gen.o Board.o Objects.o
	$(CPP) board_gen.o Board.o Objects.o -o tp

board_gen.o: board_gen.cpp
	$(CPP) -c board_gen.cpp

Board.o: Board.cpp Board.hpp
	$(CPP) -c Board.cpp

Objects.o: elems\Objects.cpp elems\Objects.hpp elems\Fixed.o elems\Movable.o
	$(CPP) -c elems\Objects.cpp

Fixed.o: elems\Fixed.cpp elems\Fixed.hpp elems\Objects.o
	$(CPP) -c elems\Fixed.cpp

Movable.o: elems\Movable.cpp elems\Movable.hpp elems\objects.o
	$(CPP) -c elems\Movable.cpp

clean:
	del *.o
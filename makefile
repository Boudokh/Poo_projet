CPP=g++ --std=c++11 -Wall
all: Board

Board: board_gen.o Game.o Board.o Object.o Fixed.o Reumus.o Teupor.o Diams.o Geurchars.o Movable.o Streumons.o
	$(CPP) board_gen.o Game.o Board.o Object.o Fixed.o Reumus.o Teupor.o Diams.o Geurchars.o Movable.o Streumons.o -o Board

board_gen.o: board_gen.cpp
	$(CPP) -c board_gen.cpp

Game.o: Game.cpp Game.hpp
	$(CPP) -c Game.cpp

Board.o: Board.cpp Board.hpp
	$(CPP) -c Board.cpp

Object.o: Object.cpp Object.hpp
	$(CPP) -c Object.cpp

Fixed.o: Fixed.cpp Fixed.hpp Object.o
	$(CPP) -c Fixed.cpp

Diams.o : Fixed.cpp Fixed.hpp Object.o Diams.cpp Diams.hpp
	$(CPP) -c Diams.cpp

Reumus.o: Reumus.cpp Reumus.hpp Fixed.o Object.o
	$(CPP) -c Reumus.cpp

Teupor.o: Teupor.cpp Teupor.hpp Fixed.o Object.o
	$(CPP) -c Teupor.cpp

Movable.o : Movable.cpp Movable.hpp Object.o
	$(CPP) -c Movable.cpp

Streumons.o : Streumons.cpp Streumons.hpp Movable.o Object.o
	$(CPP) -c Streumons.cpp

Geurchars.o : Geurchars.cpp Geurchars.hpp Fixed.o Object.o
	$(CPP) -c Geurchars.cpp

clean:
	del *.o *.exe
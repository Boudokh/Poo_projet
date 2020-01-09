CPP=g++ --std=c++11 -Wall
FILES=Game.o Board.o Object.o Reumus.o Teupor.o Diams.o Geurchars.o Streumons.o Oueurj.o
all: gc gp

Board: board_gen.o $(FILES)
	$(CPP) board_gen.o $(FILES) -o Board

gc: g_creator.o $(FILES)
	$(CPP) g_creator.o $(FILES) -o gc -lncurses

gp: g_player.o $(FILES)
	$(CPP) g_player.o $(FILES) -o gp -lncurses

g_creator.o: g_creator.cpp
	$(CPP) -c g_creator.cpp

g_player.o: g_player.cpp
	$(CPP) -c g_player.cpp

board_gen.o: board_gen.cpp
	$(CPP) -c board_gen.cpp

Game.o: Game.cpp Game.hpp
	$(CPP) -c Game.cpp

Board.o: Board.cpp Board.hpp
	$(CPP) -c Board.cpp

Object.o: Object.cpp Object.hpp
	$(CPP) -c Object.cpp

Diams.o : Object.o Diams.cpp Diams.hpp
	$(CPP) -c Diams.cpp

Reumus.o: Reumus.cpp Reumus.hpp Object.o
	$(CPP) -c Reumus.cpp

Teupor.o: Teupor.cpp Teupor.hpp Object.o
	$(CPP) -c Teupor.cpp

Geurchars.o : Geurchars.cpp Geurchars.hpp Object.o
	$(CPP) -c Geurchars.cpp

Streumons.o : Streumons.cpp Streumons.hpp Object.o
	$(CPP) -c Streumons.cpp

Oueurj.o : Oueurj.cpp Oueurj.hpp Object.o
	$(CPP) -c Oueurj.cpp

clean:
	rm *.o Board gp gc
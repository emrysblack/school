## Compile game only if chess.o or board.o  or piece.o changed
out : chess.o board.o piece.o
	g++ -o out chess.o board.o piece.o 

## Compile Chess.o only if chess.cpp or board.h or piece.h changed
chess.o : chess.cpp board.h piece.h
	g++ -c chess.cpp 

## Compile board.o only if board.cpp or board.h changed
board.o : board.cpp board.h
	g++ -c board.cpp

## Compile piece.o only if piece.cpp or piece.h changed
piece.o : piece.cpp piece.h
	g++ -c piece.cpp

## clean up

clean :
	rm out *.o
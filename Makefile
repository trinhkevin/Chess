all: chess

chess: chess.cpp board.h piece.h LTexture.h king.h queen.h bishop.h knight.h rook.h pawn.h AI.h
	g++ chess.cpp -w -lSDL2 -lSDL2_image -o chess

clean:
	rm chess

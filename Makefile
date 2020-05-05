Socoban : Move.o main.o AutoMove.o
	g++ -o sokoban Move.o AutoMove.o main.o -lncursesw
	rm -f *.o

Map.o : Move.cpp
	g++ -c -o Move.o Move.cpp -lncursesw

main.o : main.cpp
	g++ -c -o main.o main.cpp -lncursesw

AutoMove.o : AutoMove.cpp
	g++ -c -o AutoMove.o AutoMove.cpp -lncursesw

clean:
	

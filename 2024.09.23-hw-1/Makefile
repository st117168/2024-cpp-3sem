program: main.o text-editor.o
	g++ main.o text-editor.o -o program
main.o: main.cpp
	g++ -c 	main.cpp
text-editor.o: text-editor.cpp
	g++ -c 	text-editor.cpp
clean:
	rm program *.o
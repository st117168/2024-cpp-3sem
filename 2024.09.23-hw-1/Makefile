program: main.o TextEditor.o
	g++ main.o TextEditor.o -o program
main.o: main.cpp
	g++ -c 	main.cpp
TextEditor.o: TextEditor.cpp
	g++ -c 	TextEditor.cpp
clean:
	rm program *.o
build: editor.o
	gcc editor.c -lm -Wall -o editor

editor.o: editor.c
	gcc -c editor.c

run: editor
	./editor

clean:
	rm *.o editor
	

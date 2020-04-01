quidditch: main.o threadFunc.o signalHandlers.o
	gcc -o quidditch main.o threadFunc.o signalHandlers.o -lpthread

main.o: main.c threadFunc.h signalHandlers.h
	gcc -c main.c -lpthread

threadFunc.o: threadFunc.c threadFunc.h
	gcc -c threadFunc.c -lpthread

signalHandlers.o: signalHandlers.c signalHandlers.h
	gcc -c signalHandlers.c -lpthread

clean:
	rm *.o
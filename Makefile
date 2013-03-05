quash: quash.o
	g++ quash.o -o quash

quash.o: quash.cpp
	g++ -g -c quash.cpp


clean:
	rm *~ *.o quash

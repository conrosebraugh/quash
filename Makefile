quash: quash.o Job.o
	g++ quash.o Job.o -o quash

quash.o: quash.cpp
	g++ -g -c quash.cpp

Job.o: Job.cpp
	g++ -g -c Job.cpp

clean:
	rm *~ *.o quash

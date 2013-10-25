lab_1:	main.o tube.o
	g++ -Wall -g main.o tube.o -o lab_1 

main.o:main.cpp tube.h
	g++ -Wall -c main.cpp

tube.o:tube.cpp tube.h
	g++ -Wall -c tube.cpp

clean:
	rm -f lab_1 *.o

tube:	main.cpp tube.cpp tube.h
	g++ -Wall -g main.cpp tube.cpp -o tube 

clean:
	rm -f tube *.o

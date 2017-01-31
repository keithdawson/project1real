project1:   main.o
	g++ -Wall -std=c++11 main.cpp -o project1

main.o:	main.cpp
	gcc -Wall -c main.cpp

clean:	
	rm -f *.o project1
	
	

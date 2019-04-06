exe: Main.o CrewMember.o CrewMembers.o Plane.o Planes.o Flight.o Flights.o
	g++ -std=c++11 -o exe Main.o CrewMember.o CrewMembers.o Plane.o Planes.o Flight.o Flights.o

main.o: Main.cpp
	g++ -std=c++11 -c Main.cpp

CrewMember.o: CrewMember.cpp CrewMember.h
	g++ -std=c++11 -c CrewMember.cpp

CrewMembers.o: CrewMembers.cpp CrewMembers.h CrewMember.h
	g++ -std=c++11 -c CrewMembers.cpp

Plane.o: Plane.cpp Plane.h
	g++ -std=c++11 -c Plane.cpp

Planes.o: Planes.cpp Planes.h Plane.h
	g++ -std=c++11 -c Planes.cpp

Flight.o: Flight.cpp Flight.h
	g++ -std=c++11 -c Flight.cpp

Flights.o: Flights.cpp Flights.h Flight.h
	g++ -std=c++11 -c Flights.cpp

clean:
	rm *.o exe

run: exe
	./exe
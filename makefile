CXXFLAGS = -std=c++0x

OBJECTS = Driver.o Contestant.o Card.o

program3:	$(OBJECTS)
	g++ $(CXXFLAGS) $(OBJECTS) -o $@

Driver.o:	Driver.cpp
Contestant.o:	Contestant.h Contestant.cpp
Card.o:	Card.cpp Card.h

clean:
	rm -f *.o program3


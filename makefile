# Specify the target
FLAGS = -Wall -std=c++11

all: program3

# Link one.o and two.o into an executable called

program3: Contestant.o Card.o Driver.o
	g++ $(FLAGS) Contestant.o Card.o Driver.o -o program3
# g++ std=c++11 <etc>

Constestant.o:	Contestant.cpp Contestant.h
	g++ $(FLAGS) -g -c Contestant.cpp -o Contestant.o

Card.o:	Card.cpp Card.h
	g++ $(FLAGS) -g -c Card.cpp -o Card.o


Driver.o:	driver.cpp
	g++ $(FLAGS) -g -c driver.cpp -o driver.o




clean:
	rm -f *.o submission


tar:
	tar cvzf dinhofer_h_p3.tar.gz Contestant.cpp Contestant.h Card.cpp Card.h driver.cpp makefile

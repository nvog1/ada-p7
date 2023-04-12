#Nicolás Van Olmen Giménez, 74383864R
all: maze_greedy.cc
	g++ -g -Wall -o maze_greedy maze_greedy.cc
clean:
	rm maze_greedy
tar: maze_greedy.cc
	tar cvzf 74383864R.tar.gz maze_greedy.cc makefile

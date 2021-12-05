UTILS = Utilities/Utilities.o
INCLUDE = -I.
FLAGS = -Wall -Wextra -Wpedantic -std=c++17 -g
.PHONY: build

build: 01/01.out 02/02.out 03/03.out 04/04.out

01/01.out: 01/01.cpp $(UTILS)
	g++ $^ $(FLAGS) $(INCLUDE) -o $@

02/02.out: 02/02.cpp $(UTILS)
	g++ $^ $(FLAGS) $(INCLUDE) -o $@

03/03.out: 03/03.cpp $(UTILS)
	g++ $^ $(FLAGS) $(INCLUDE) -o $@

04/04.out: 04/04.cpp $(UTILS)
	g++ $^ $(FLAGS) $(INCLUDE) -o $@

Utilities/Utilities.o: Utilities/Utilities.cpp Utilities/Utilities.h
	g++ $< $(FLAGS) $(INCLUDE) -c -o $@

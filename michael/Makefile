UTILS = Utilities/Utilities.o
INCLUDE = -I.
FLAGS = -Wall -Wextra -Wpedantic -std=c++17 -g
OUTPUT = 01/01.out 02/02.out 03/03.out 04/04.out 05/05.out 06/06.out

.PHONY: build
build: $(OUTPUT)

01/01.out: 01/01.cpp $(UTILS)
	g++ $^ $(FLAGS) $(INCLUDE) -o $@

02/02.out: 02/02.cpp $(UTILS)
	g++ $^ $(FLAGS) $(INCLUDE) -o $@

03/03.out: 03/03.cpp $(UTILS)
	g++ $^ $(FLAGS) $(INCLUDE) -o $@

04/04.out: 04/04.cpp $(UTILS)
	g++ $^ $(FLAGS) $(INCLUDE) -o $@

05/05.out: 05/05.cpp $(UTILS)
	g++ $^ $(FLAGS) $(INCLUDE) -o $@

06/06.out: 06/06.cpp $(UTILS)
	g++ $^ $(FLAGS) $(INCLUDE) -o $@

Utilities/Utilities.o: Utilities/Utilities.cpp Utilities/Utilities.h
	g++ $< $(FLAGS) $(INCLUDE) -c -o $@

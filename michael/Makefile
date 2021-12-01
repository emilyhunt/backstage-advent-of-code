UTILS = Utilities/Utilities.o
INCLUDE = -I.
.PHONY: build

build: 01/01.out 02/02.out



01/01.out: 01/01.cpp $(UTILS)
	g++ $^ -Wall -Wextra -Wpedantic $(INCLUDE) -o $@

02/02.out: 02/02.cpp $(UTILS)
	g++ $^ -Wall -Wextra -Wpedantic $(INCLUDE) -o $@

Utilities/Utilities.o: Utilities/Utilities.cpp Utilities/Utilities.h
	g++ $< -Wall -Wextra -Wpedantic $(INCLUDE) -c -o $@

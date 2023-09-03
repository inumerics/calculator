CC = g++
CXXFLAGS = -std=c++14 -Wall

SRC     = source/
BUILD   = build/

#*******************************************************************************
calc: $(BUILD)main.o $(BUILD)calculator.o $(BUILD)states.o
	$(CC) $(CXXFLAGS) -o $@ $^

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)calculator.o: $(SRC)calculator.cpp $(SRC)calculator.hpp | $(BUILD)
	$(CC) $(CXXFLAGS) -c -o $@ $<

$(BUILD)main.o: $(SRC)main.cpp $(SRC)calculator.hpp | $(BUILD)
	$(CC) $(CXXFLAGS) -c -o $@ $<

$(BUILD)states.o: $(BUILD)states.cpp | $(BUILD)
	$(CC) $(CXXFLAGS) -I $(SRC) -c -o $@ $<

$(BUILD)states.cpp: $(SRC)calculator.bnf $(SRC)calculator.hpp | $(BUILD)
	parser -o $(BUILD)states.cpp $(SRC)calculator.bnf
	
#*******************************************************************************
clean:
	rm -f calc
	rm -f $(BUILD)calculator.o
	rm -f $(BUILD)states.cpp
	rm -f $(BUILD)states.o
	rm -f $(BUILD)main.o
	rm -f -d $(BUILD)

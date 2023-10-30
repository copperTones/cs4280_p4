HEADER = token.h scanner.h langToken.h
CPP = main.cpp scanner.cpp
LANG = f1Token.cpp
PROJ = p1

P1: p1
p1: $(HEADER) $(CPP) $(LANG)
	g++ $(CPP) $(LANG) -o $(PROJ)

.PHONY: clean
clean:
	rm $(PROJ)

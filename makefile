HEADER = token.h scanner.h langToken.h parser.h
CPP = main.cpp scanner.cpp parser.cpp
LANG = f1Token.cpp f1BNF.cpp

P2: p2
p2: $(HEADER) $(CPP) $(LANG)
	g++ $(CPP) $(LANG) -o p2

.PHONY: clean
clean:
	rm p2

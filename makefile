P2: p2
p2: *.h *.cpp
	g++ *.cpp -o p2

.PHONY: clean
clean:
	rm p2

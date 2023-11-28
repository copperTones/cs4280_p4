P3: p3
p3: *.h *.cpp
	g++ -std=c++11 *.cpp -o p3

.PHONY: clean
clean:
	rm p3

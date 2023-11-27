P3: p3
p3: *.h *.cpp
	g++ *.cpp -o p3

.PHONY: clean
clean:
	rm p3

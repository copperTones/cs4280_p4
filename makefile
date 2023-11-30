P3: p4
p4: *.h *.cpp
	g++ -std=c++11 *.cpp -o comp

.PHONY: clean
clean:
	rm comp


all: compile
	./comp/game 10 10

compile: src/game.cpp
	gcc ./src/game.cpp -o ./comp/game -lglut -lGLU -lGL -lm -lstdc++

clean:
	rm ./src/maze

kruskal: compile-kruskal
	./comp/kruskal

compile-kruskal: src/kruskal.cpp
	gcc ./src/kruskal.cpp -o ./comp/kruskal -lstdc++

test: tests/test.cpp
	gcc ./tests/test.cpp -o ./tests/comp/test -lstdc++
	./tests/comp/test

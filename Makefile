
all: compile
	./comp/maze 40 20

compile: src/maze.cpp
	gcc ./src/maze.cpp -o ./comp/maze -lglut -lGLU -lGL -lm -lstdc++

clean:
	rm ./src/maze

kruskal: compile-kruskal
	./comp/kruskal

compile-kruskal: src/kruskal.cpp
	gcc ./src/kruskal.cpp -o ./comp/kruskal -lstdc++

prim: compile-prim
	./comp/prim

compile-prim: src/prim.cpp
	gcc ./src/prim.cpp -o ./comp/prim -lstdc++

test: tests/test.cpp
	gcc ./tests/test.cpp -o ./tests/comp/test -lstdc++
	./tests/comp/test


all: compile
	./comp/game 10 10 --print --func=dfs

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

compile-backtraking: src/maze_gen/backtraking.cpp
	gcc ./src/backtraking.cpp -o ./comp/backtraking -lstdc++

run-backtraking: compile-backtraking
	./comp/backtraking

compile-tank: src/graphics/tank/3dtank.c
		gcc src/graphics/tank/3dtank.c -o ./comp/tank -lglut -lGLU -lGL -lm -lstdc++

run-tank: compile-tank
	./comp/tank

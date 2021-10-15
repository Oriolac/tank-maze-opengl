
all: compile
	./comp/game 15 15 --print --func=dfs

compile: src/game.cpp
	gcc ./src/game.cpp -o ./comp/game -lglut -lGLU -lGL -lm -lstdc++

clean:
	rm ./comp/game

test: tests/test.cpp
	gcc ./tests/test.cpp -o ./tests/comp/test -lstdc++
	./tests/comp/test

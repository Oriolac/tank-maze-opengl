
all: compile
	./maze a b

compile: maze.cpp
	gcc maze.cpp -o maze -lglut -lGLU -lGL -lm 

clean:
	rm maze

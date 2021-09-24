
all: compile
	./maze a b

compile: maze.cpp
	gcc maze.cpp -o maze -lglut -lGLU -lGL -lm -lstdc++

clean:
	rm maze

kruskal: compile-kruskal
	./kruskal

compile-kruskal: kruskal.cpp
	gcc kruskal.cpp -o kruskal -lstdc++

prim: compile-prim
	./prim

compile-prim: prim.cpp
	gcc prim.cpp -o prim -lstdc++

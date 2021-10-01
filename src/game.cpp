#include <cstdio>
#include <cstdlib>
#include "kruskal.cpp"
#include "utils/dimensions.cpp"

int main(int argc, char **argv) {
    if (argc != 1 && argc != 3) {
        printf("Usage:\n\t./maze [<rows>=20 <cols>=20]\n");
        return 0;
    }
    Dimensions dimensions = getDimensions(argc, argv);
    Graph graph = createLaberinthWithKruskal(dimensions.cols, dimensions.rows);
    graph.kruskal();
    graph.printMaze();
}


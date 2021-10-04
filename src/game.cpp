#include <cstdio>
#include <cstdlib>
#include "dfs.cpp"
#include "utils/dimensions.cpp"
#include "utils/GraphAdapter.h"
#include <GL/glut.h>



#define SIDE_LENGTH 30


GraphDFS graph = GraphDFS(0, 0);
int COLUMNS;
int ROWS;
int WIDTH;
int HEIGHT;

void display();

int main(int argc, char **argv) {
    if (argc != 1 && argc != 3) {
        printf("Usage:\n\t./maze [<rows>=20 <cols>=20]\n");
        return 0;
    }
    Dimensions dimensions = getDimensions(argc, argv);
    graph = GraphDFS(dimensions.cols, dimensions.rows);
    graph.start();
    COLUMNS = graph.getCols();
    ROWS = graph.getRows();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    WIDTH = SIDE_LENGTH * graph.getCols();
    HEIGHT = SIDE_LENGTH * graph.getRows();
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Maze");

    glutDisplayFunc(display);

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, WIDTH - 1, 0, HEIGHT - 1);

    glutMainLoop();

}

void display() {
    int i, j;

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    for (int tile_count = 0; tile_count < graph.getNumTiles(); tile_count++) {
        if (graph.isWall(tile_count)) {
            std::pair<int, int> *coords = graph.toCoordinates(tile_count);
            glColor3f(0.6, 0.6, 0.6);
            glBegin(GL_QUADS);
            i = coords->first;
            j = coords->second;
            glVertex2i(i * WIDTH / COLUMNS, j * HEIGHT / ROWS);
            glVertex2i((i + 1) * WIDTH / COLUMNS, j * HEIGHT / ROWS);
            glVertex2i((i + 1) * WIDTH / COLUMNS, (j + 1) * HEIGHT / ROWS);
            glVertex2i(i * WIDTH / COLUMNS, (j + 1) * HEIGHT / ROWS);
            glEnd();
        }
    }
    glutSwapBuffers();

}

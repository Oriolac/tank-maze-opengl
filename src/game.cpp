#include <cstdio>
#include <cstdlib>
#include "kruskal.cpp"
#include "utils/dimensions.cpp"
#include <GL/glut.h>


#define WIDTH 500
#define HEIGHT 500

int keyflag = 0;

Graph graph = Graph(0, 0);
int COLUMNS;
int ROWS;

void display();

int main(int argc, char **argv) {
    if (argc != 1 && argc != 3) {
        printf("Usage:\n\t./maze [<rows>=20 <cols>=20]\n");
        return 0;
    }
    Dimensions dimensions = getDimensions(argc, argv);
    graph = createLaberinthWithKruskal(dimensions.cols, dimensions.rows);
    graph.kruskal();
    graph.printMaze();
    COLUMNS = graph.getCols();
    ROWS = graph.getRows();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Chess board");

    glutDisplayFunc(display);

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, WIDTH - 1, 0, HEIGHT - 1);

    glutMainLoop();

}


void display() {
    int i, j;

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    for (i = 0; i < WIDTH; i++)
        for (j = 0; j < HEIGHT; j++)
            if ((keyflag == 0 && (i + j) % 2 == 0) || (keyflag == 1 && (i + j) % 2 == 1)) {
                glColor3f(0.6, 0.6, 0.6);
                glBegin(GL_QUADS);

                glVertex2i(i * WIDTH / COLUMNS , j * HEIGHT / ROWS);
                glVertex2i((i + 1) * WIDTH / COLUMNS, j * HEIGHT / ROWS);
                glVertex2i((i + 1) * WIDTH / COLUMNS, (j + 1) * HEIGHT / ROWS);
                glVertex2i(i * WIDTH / COLUMNS, (j + 1) * HEIGHT / ROWS);

                glEnd();
            }

    glutSwapBuffers();

}

#include <cstdio>
#include <cstdlib>
#include "dfs.cpp"
#include "utils/dimensions.cpp"
#include "utils/GraphInterface.h"
#include <GL/glut.h>
#include "utils/graphics.h"

#define SIDE_LENGTH 30

#define COLOR_WALL Color(0.6, 0.6, 0.7)
#define INITIAL_PATH_COLOR Color(0.2, 0.8, 0.2)
#define LAST_PATH_COLOR Color(0.8, 0.2, 0.2)

GraphInterface *graph;
int COLUMNS;
int ROWS;
int WIDTH;
int HEIGHT;



void display();

void config_opengl(int &argc, char **argv);

void addSquare(int i, int j, struct Color color);

int main(int argc, char **argv) {
    if (argc < 1 || argc > 4) {
        printf("Usage:\n\t./maze [<rows>=20 <cols>=20 [--func={start, dfsbrave, dfsheur}]]\n");
        exit(0);
    }
    Dimensions dimensions = getDimensions(argc, argv);
    bool mustPrint = false;
    GraphDFS graphDfs = GraphDFS(dimensions.cols, dimensions.rows);
    graph = static_cast<GraphInterface *>(malloc(sizeof(GraphDFS)));
    if (!graph) {
        printf("malloc failed\n");
        return -1;
    }
    graph = &graphDfs;
    for (int i = 3; i < argc; i++) {
        std::string s = argv[i];
        std::string delimiter = "=";
        size_t pos = s.find(delimiter);
        std::string tok = s.substr(0, pos);
        if (std::equal(tok.begin(), tok.end(), std::string("--func").begin())) {
            s.erase(0, pos + delimiter.length());
            tok = s.substr(0, pos + 1);
            GraphDFS graphDfs = GraphDFS(dimensions.cols, dimensions.rows);
            graph = &graphDfs;
        } else if (std::equal(tok.begin(), tok.end(), std::string("--print").begin())) {
            mustPrint = true;
        } else {
            printf("Usage:\n\t./maze [<rows>=20 <cols>=20 [--func={start, dfsbrave, dfsheur}]]\n");
            exit(0);
        }
    }
    graph->start();
    if (mustPrint)
        graph->print();
    config_opengl(argc, argv);

}

void config_opengl(int &argc, char **argv) {
    COLUMNS = graph->getCols();
    ROWS = graph->getRows();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    WIDTH = SIDE_LENGTH * COLUMNS;
    HEIGHT = SIDE_LENGTH * ROWS;
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
    glClearColor(0.1, 0.1, 0.1, 0.0);

    glClear(GL_COLOR_BUFFER_BIT);
    for (int tile_count = 0; tile_count < COLUMNS * ROWS; tile_count++) {
        if (graph->isWall(tile_count)) {
            std::pair<int, int> *coords = graph->toCoordinates(tile_count);
            i = coords->first;
            j = coords->second;
            addSquare(i, j, COLOR_WALL);
        }
    }
    pair<int, int> initial_pos = graph->get_initial_pos();
    addSquare(initial_pos.first, initial_pos.second, INITIAL_PATH_COLOR);
    pair<int, int> last_pos = graph->get_last_pos();
    addSquare(last_pos.first, last_pos.second, LAST_PATH_COLOR);
    glutSwapBuffers();

}

void addSquare(int i, int j, struct Color color) {
    glColor3f(color.red, color.green, color.blue);
    glBegin(GL_QUADS);
    glVertex2i(i * WIDTH / COLUMNS, j * HEIGHT / ROWS);
    glVertex2i((i + 1) * WIDTH / COLUMNS, j * HEIGHT / ROWS);
    glVertex2i((i + 1) * WIDTH / COLUMNS, (j + 1) * HEIGHT / ROWS);
    glVertex2i(i * WIDTH / COLUMNS, (j + 1) * HEIGHT / ROWS);
    glEnd();
}

#include <cstdio>
#include <cstdlib>
#include "dfs.cpp"
#include "utils/dimensions.cpp"
#include "utils/GraphInterface.h"
#include <GL/glut.h>
#include "utils/graphics.h"
#include "backtraking.cpp"

#define SIDE_LENGTH 30

#define COLOR_WALL Color(0.55, 0.55, 0.7)
#define MAIN_CHARACTER_INITIAL_POS Color(0.2, 0.8, 0.2)
#define ENEMY_CHARACTER_LAST_POS Color(0.8, 0.2, 0.2)
#define BACKGROUND_COLOR 0.75, 0.75, 0.9, 0.0

GraphInterface *graph;
int COLUMNS;
int ROWS;
int WIDTH;
int HEIGHT;


void display();

void config_opengl(int &argc, char **argv);

void addSquare(int i, int j, struct Color color);

void maze_display();

void characters_display();

int main(int argc, char **argv) {
    if (argc < 1 || argc > 5) {
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
        if (std::equal(s.begin(), s.end(), std::string("--print").begin())) {
            mustPrint = true;
        } else if (std::equal(tok.begin(), tok.end(), std::string("--func").begin())) {
            s.erase(0, pos + delimiter.length());
            tok = s.substr(0, pos + 1);
            if (std::equal(tok.begin(), tok.end(), std::string("heur").begin())) {
                GraphDfsHeur graphHeur = GraphDfsHeur(dimensions.cols, dimensions.rows);
                graph = &graphHeur;
            } else if (std::equal(tok.begin(), tok.end(), std::string("dfs").begin())) {
                graphDfs = GraphDFS(dimensions.cols, dimensions.rows);
                graph = &graphDfs;
            }
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
    glutCreateWindow("GraphDfsHeur");
    glutDisplayFunc(display);

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, WIDTH - 1, 0, HEIGHT - 1);

    glutMainLoop();
}


void display() {
    maze_display();
    glutSwapBuffers();
}


void maze_display() {
    int i, j;
    glClearColor(BACKGROUND_COLOR);
    glClear(GL_COLOR_BUFFER_BIT);
    for (int row = ROWS - 1; row >= 0; row--) {
        for (int col = COLUMNS - 1; col >= 0; col--) {
            int pos = graph->to_pos(col, row);
            if (graph->is_wall(pos)) {
                addSquare(col, row, COLOR_WALL);
            }
        }
    }
    pair<int, int> initial_pos = graph->get_main_coords();
    addSquare(initial_pos.first, initial_pos.second, MAIN_CHARACTER_INITIAL_POS);
    pair<int, int> last_pos = graph->get_enemy_coords();
    addSquare(last_pos.first, last_pos.second, ENEMY_CHARACTER_LAST_POS);
}

void addSquare(int i, int j, struct Color color) {
    i = i;
    j = -j + ROWS - 1;
    glColor3f(color.red, color.green, color.blue);
    glBegin(GL_QUADS);
    glVertex2i(i * WIDTH / COLUMNS, j * HEIGHT / ROWS);
    glVertex2i((i + 1) * WIDTH / COLUMNS, j * HEIGHT / ROWS);
    glVertex2i((i + 1) * WIDTH / COLUMNS, (j + 1) * HEIGHT / ROWS);
    glVertex2i(i * WIDTH / COLUMNS, (j + 1) * HEIGHT / ROWS);
    glEnd();
}

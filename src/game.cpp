#include <cstdio>
#include <cstdlib>
#include "maze/dfs.cpp"
#include "utils/dimensions.cpp"
#include "maze/GraphInterface.h"
#include <GL/glut.h>
#include "utils/graphics.h"
#include "Character.cpp"

#define SIDE_LENGTH 30

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

void keyboard(unsigned char c, int x, int y);

void idle();

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
        exit(-1);
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
            graphDfs = GraphDFS(dimensions.cols, dimensions.rows);
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
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, WIDTH - 1, 0, HEIGHT - 1);

    glutMainLoop();
}


void display() {
    maze_display();
    characters_display();
    glutSwapBuffers();
}

void characters_display() {
    MainCharacter main_character = MainCharacter(graph->get_main_coords(), SIDE_LENGTH);
    EnemyCharacter enemy_character = EnemyCharacter(graph->get_enemy_coords(), SIDE_LENGTH);
}


void maze_display() {
    int i, j;
    glClearColor(BACKGROUND_COLOR);
    glClear(GL_COLOR_BUFFER_BIT);
    for (int tile_count = 0; tile_count < COLUMNS * ROWS; tile_count++) {
        if (graph->is_wall(tile_count)) {
            pair<int, int> *coords = graph->toCoordinates(tile_count);
            i = coords->first;
            j = coords->second;
            addSquare(i, j, COLOR_WALL);
        }
    }
    pair<int, int> initial_pos = graph->get_main_coords();
    addSquare(initial_pos.first, initial_pos.second, COLOR_MAIN_CHARACTER_INITIAL_POS);
    pair<int, int> last_pos = graph->get_enemy_coords();
    addSquare(last_pos.first, last_pos.second, COLOR_ENEMY_CHARACTER_LAST_POS);
}

void keyboard(unsigned char c, int x, int y) {
    switch (c) {
        case 'a':case 'A':
            printf("LEFT\n");
            break;
        case 'd':case 'D':
            printf("RIGHT\n");
            break;
        case 'w':case 'W':
            printf("UP\n");
            break;
        case 's':case 'S':
            printf("DOWN\n");
            break;
        default:
            break;
    }
    glutPostRedisplay();
};

void idle() {
    t=glutGet(GLUT_ELAPSED_TIME);

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

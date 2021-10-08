#include <cstdio>
#include <cstdlib>
#include "maze_gen/dfs.cpp"
#include "utils/dimensions.cpp"
#include "maze_gen/GraphInterface.h"
#include <GL/glut.h>
#include "utils/graphics.h"
#include "Character.cpp"
#include "Context.cpp"
#include "maze_gen/backtraking.cpp"
#include <memory>

#define SIDE_LENGTH 30

#define BACKGROUND_COLOR 0.75, 0.75, 0.9, 0.0

Context *context;
std::shared_ptr<GraphInterface> graph;
int COLUMNS;
int ROWS;
int WIDTH;
int HEIGHT;

int last_t = 0;

void display();

void config_opengl(int &argc, char **argv);

void addSquare(int i, int j, struct Color color);

void maze_display();

void characters_display();

void keyboard(unsigned char c, int x, int y);

void idle();

bool get_opt_args(int argc, char *const *argv, const Dimensions &dimensions);

int main(int argc, char **argv) {
    if (argc < 4 || argc > 5) {
        printf("Usage:\n\t./game [<rows>=20 <cols>=20 --func={dfs, heur} [--print]]\n");
        exit(0);
    }
    Dimensions dimensions = getDimensions(argc, argv);
    bool mustPrint = false;
    mustPrint = get_opt_args(argc, argv, dimensions);
    graph->start();
    if (mustPrint)
        graph->print();
    MainCharacter main_character = MainCharacter(graph->get_main_coords(), SIDE_LENGTH);
    EnemyCharacter enemy_character = EnemyCharacter(graph->get_enemy_coords(), SIDE_LENGTH);
    Context new_cont = Context(graph, &main_character, &enemy_character);
    context = &new_cont;
    config_opengl(argc, argv);
}

bool get_opt_args(int argc, char *const *argv, const Dimensions &dimensions) {
    bool mustPrint;
    for (int i = 3; i < argc; i++) {
        string s = argv[i];
        string delimiter = "=";
        size_t pos = s.find(delimiter);
        string tok = s.substr(0, pos);
        if (equal(s.begin(), s.end(), string("--print").begin())) {
            mustPrint = true;
        } else if (equal(tok.begin(), tok.end(), string("--func").begin())) {
            s.erase(0, pos + delimiter.length());
            tok = s.substr(0, pos + 1);
            if (equal(tok.begin(), tok.end(), string("heur").begin())) {
                GraphDfsHeur graphHeur = GraphDfsHeur(dimensions.cols, dimensions.rows);
                graph = make_shared<GraphDfsHeur>(graphHeur);
                if (!graph) {
                    printf("malloc failed\n");
                    exit(-1);
                }
            } else if (equal(tok.begin(), tok.end(), string("dfs").begin())) {
                GraphDFS graphDfs = GraphDFS(dimensions.cols, dimensions.rows);
                graph = make_shared<GraphDFS>(graphDfs);
                if (!graph) {
                    printf("malloc failed\n");
                    exit(-1);
                }
            }
        } else {
            printf("Usage:\n\t./game [<rows>=20 <cols>=20 --func={dfs, heur} [--print]]\n");
            exit(0);
        }
    }
    return mustPrint;
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
    context->getMainCharacter()->draw();
    context->getEnemyCharacter()->draw();
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
        case 'a':
        case 'A':
            context->move(Direction::LEFT);
            break;
        case 'd':
        case 'D':
            context->move(Direction::RIGHT);
            break;
        case 'w':
        case 'W':
            context->move(Direction::UP);
            break;
        case 's':
        case 'S':
            context->move(Direction::DOWN);
            break;
        default:
            break;
    }
    glutPostRedisplay();
};

void idle() {
    int t = glutGet(GLUT_ELAPSED_TIME);
    if (last_t == 0) {
        last_t = t;
    }else {
        context->getMainCharacter()->integrate(t -  last_t);
        context->getEnemyCharacter()->integrate(t - last_t);
        last_t = t;
    }
    Direction dir = static_cast<Direction>(rand() % 5);
    context ->move_enemy(dir);
    glutPostRedisplay();
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

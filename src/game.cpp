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

#define SIDE_LENGTH 40

#define PI 3.1416
#define BACKGROUND_COLOR 0.75, 0.75, 0.9, 0.0

#define FLOOR 0
Context *context;
std::shared_ptr<GraphInterface> graph;
int COLUMNS;
int ROWS;
int WIDTH;
int HEIGHT;
int anglebeta = 0;
int anglealpha = 0;

int last_t = 0;

void display();

void config_opengl(int &argc, char **argv);

void addSquare(int i, int j, struct Color color, int height);

void maze_display();

void characters_display();

void keyboard(unsigned char c, int x, int y);

void idle();

bool get_opt_args(int argc, char *const *argv, const Dimensions &dimensions);

void create_position_observer(int anglealpha, int anglebeta, int radi);

void addPath(int i, int j, Color color, float height);

int main(int argc, char **argv) {
    if (argc < 4 || argc > 5) {
        printf("Usage:\n\t./game [<rows>=20 <cols>=20 --func={dfs, heur} [--print]]\n");
        exit(0);
    }
    anglealpha = 90;
    anglebeta = -2;
    Dimensions dimensions = getDimensions(argc, argv);
    bool mustPrint = get_opt_args(argc, argv, dimensions);
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
    WIDTH = SIDE_LENGTH * COLUMNS;
    HEIGHT = SIDE_LENGTH * ROWS;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("GraphDfsHeur");
    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);

    glutMainLoop();
}


void display() {
    maze_display();
    characters_display();
    glutSwapBuffers();
}

void characters_display() {
    context->getMainCharacter()->draw(COLORTUP_MAIN_FACE_VERTEX, COLORTUP_MAIN_BACK_VERTEX);
    context->getEnemyCharacter()->draw(COLORTUP_ENEMY_FACE_VERTEX, COLORTUP_ENEMY_BACK_VERTEX);
}


void maze_display() {
    int i, j;
    glClearColor(BACKGROUND_COLOR);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    create_position_observer(anglealpha, anglebeta, 300);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-WIDTH * 2 / 3, WIDTH * 2 / 3, -HEIGHT * 2 / 3, HEIGHT * 2 / 3, 10, 2000);
    for (int tile_count = 0; tile_count < COLUMNS * ROWS; tile_count++) {
        pair<int, int> *coords = graph->toCoordinates(tile_count);
        i = coords->first;
        j = coords->second;
        if (graph->is_wall(tile_count)) {
            addSquare(i, j, COLOR_WALL, 20);
        } else {
            addPath(i, j, COLOR_PATH, FLOOR);
        }
    }
    pair<int, int> initial_pos = graph->get_main_coords();
    addPath(initial_pos.first, initial_pos.second, COLOR_MAIN_CHARACTER_INITIAL_POS, FLOOR + 0.1);
    pair<int, int> last_pos = graph->get_enemy_coords();
    addPath(last_pos.first, last_pos.second, COLOR_ENEMY_CHARACTER_LAST_POS, FLOOR + 0.1);
}

void create_position_observer(int alpha, int beta, int radi) {
    float x, y, z;
    float upx, upy, upz;
    float modul;

    x = (float) radi * cos(alpha * 2 * PI / 360.0) * cos(beta * 2 * PI / 360.0);
    y = (float) radi * sin(beta * 2 * PI / 360.0);
    z = (float) radi * sin(alpha * 2 * PI / 360.0) * cos(beta * 2 * PI / 360.0);

    if (beta > 0) {
        upx = -x;
        upz = -z;
        upy = (x * x + z * z) / y;
    } else if (beta == 0) {
        upx = 0;
        upy = 1;
        upz = 0;
    } else {
        upx = x;
        upz = z;
        upy = -(x * x + z * z) / y;
    }


    modul = sqrt(upx * upx + upy * upy + upz * upz);

    upx = upx / modul;
    upy = upy / modul;
    upz = upz / modul;

    gluLookAt(x, y, z, WIDTH / 2, HEIGHT / 2, 0.0, upx, upy, upz);
}

void keyboard(unsigned char c, int x, int y) {
    switch (c) {
        case 'a':
        case 'A':
            context->move_main(Direction::TURN_LEFT);
            break;
        case 'd':
        case 'D':
            context->move_main(Direction::TURN_RIGHT);
            break;
        case 'i':
            if (anglebeta <= (90 - 4))
                anglebeta = (anglebeta + 3);
            break;
        case 'k':
            if (anglebeta >= (-90 + 4))
                anglebeta = (anglebeta - 3);
            break;
        case 'j':
            anglealpha = (anglealpha + 3) % 360;
            break;
        case 'l':
            anglealpha = (anglealpha - 3 + 360) % 360;
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
    } else {
        context->integrate(context->getMainCharacter(), t - last_t);
        context->integrate(context->getEnemyCharacter(), t - last_t);
        last_t = t;
    }
    context->move_enemy(static_cast<Direction>(rand() % 3));
    glutPostRedisplay();
}

void addSquare(int i, int j, struct Color color, int height) {
    glMatrixMode(GL_MODELVIEW);
    glPolygonMode(GL_FRONT, GL_FILL);
    glColor3f(color.red, color.green, color.blue);
    glBegin(GL_QUADS);
    glVertex3f(i * WIDTH / COLUMNS, j * HEIGHT / ROWS, height);
    glVertex3f((i + 1) * WIDTH / COLUMNS, j * HEIGHT / ROWS, height);
    glVertex3f((i + 1) * WIDTH / COLUMNS, (j + 1) * HEIGHT / ROWS, height);
    glVertex3f(i * WIDTH / COLUMNS, (j + 1) * HEIGHT / ROWS, height);
    glEnd();

    glColor3f(0, 0, 0);
    glBegin(GL_QUADS);
    glVertex3f(i * WIDTH / COLUMNS , j * HEIGHT / ROWS , FLOOR);
    glVertex3f(i * WIDTH / COLUMNS , (j + 1) * HEIGHT / ROWS , FLOOR);
    glVertex3f((i + 1) * WIDTH / COLUMNS, (j + 1) * HEIGHT / ROWS , FLOOR);
    glVertex3f((i + 1) * WIDTH / COLUMNS, j * HEIGHT / ROWS , FLOOR);
    glEnd();

    glColor3f(COLORTUP_WALL_SIDE);
    glBegin(GL_QUADS);
    glVertex3f(i * WIDTH / COLUMNS , ((j + 1) * HEIGHT / ROWS) , height);
    glVertex3f((i + 1) * WIDTH / COLUMNS , (j + 1) * HEIGHT / ROWS, height);
    glVertex3f((i + 1) * WIDTH / COLUMNS , (j + 1) * HEIGHT / ROWS, FLOOR );
    glVertex3f(i * WIDTH / COLUMNS, (j + 1) * HEIGHT / ROWS , FLOOR );
    glEnd();

    glColor3f(COLORTUP_WALL_SIDE);
    glBegin(GL_QUADS);
    glVertex3f(i * WIDTH / COLUMNS, j * HEIGHT / ROWS, FLOOR);
    glVertex3f((i + 1) * WIDTH / COLUMNS, j * HEIGHT / ROWS, FLOOR );
    glVertex3f((i + 1) * WIDTH / COLUMNS, j * HEIGHT / ROWS, height);
    glVertex3f(i * WIDTH / COLUMNS, j * HEIGHT / ROWS, height );
    glEnd();


    glColor3f(COLORTUP_WALL_SIDE);
    glBegin(GL_QUADS);
    glVertex3f(i * WIDTH / COLUMNS , j * HEIGHT / ROWS , height);
    glVertex3f(i * WIDTH / COLUMNS , (j + 1) * HEIGHT / ROWS , height);
    glVertex3f(i * WIDTH / COLUMNS , (j + 1) * HEIGHT / ROWS , FLOOR );
    glVertex3f(i * WIDTH / COLUMNS , j * HEIGHT / ROWS , FLOOR );
    glEnd();


    glColor3f(COLORTUP_WALL_SIDE);
    glBegin(GL_QUADS);
    glVertex3f((i + 1) * WIDTH / COLUMNS , j * HEIGHT / ROWS , height );
    glVertex3f((i + 1) * WIDTH / COLUMNS , j * HEIGHT / ROWS , FLOOR );
    glVertex3f((i + 1) * WIDTH / COLUMNS , (j + 1) * HEIGHT / ROWS , FLOOR );
    glVertex3f((i + 1) * WIDTH / COLUMNS , (j + 1) * HEIGHT / ROWS , height);
    glEnd();

}

void addPath(int i, int j, Color color, float height) {
    glMatrixMode(GL_MODELVIEW);
    glPolygonMode(GL_FRONT, GL_FILL);
    glColor3f(color.red, color.green, color.blue);
    glBegin(GL_QUADS);

    glVertex3f(i * WIDTH / COLUMNS, j * HEIGHT / ROWS,  height);
    glVertex3f((i + 1) * WIDTH / COLUMNS, j * HEIGHT / ROWS, height);
    glVertex3f((i + 1) * WIDTH / COLUMNS, (j + 1) * HEIGHT / ROWS, height);
    glVertex3f(i * WIDTH / COLUMNS, (j + 1) * HEIGHT / ROWS, height);

    glBegin(GL_QUADS);
    glVertex3f(i * WIDTH / COLUMNS, j * HEIGHT / ROWS, height);
    glVertex3f(i * WIDTH / COLUMNS, (j + 1) * HEIGHT / ROWS, height);
    glVertex3f((i + 1) * WIDTH / COLUMNS, (j + 1) * HEIGHT / ROWS, height);
    glVertex3f((i + 1) * WIDTH / COLUMNS, j * HEIGHT / ROWS, height);
    glEnd();

    glEnd();
}

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
#include "utils/textures.cpp"

#define SIDE_LENGTH 40

#define PI 3.1416
#define BACKGROUND_COLOR 0.3, 0.3, 0.5, 0.0

#define FLOOR 10
std::shared_ptr<Context> context;
std::shared_ptr<GraphInterface> graph;
int COLUMNS;
int ROWS;
int WIDTH;
int HEIGHT;
int anglebeta = 0;
int anglealpha = 0;
double time_maze = 60;
double time_left = time_maze;
std::shared_ptr<Dimensions> dimensions;

int last_t = 0;

void display();

void config_opengl(int &argc, char **argv);

void addSquare(int i, int j, struct Color color, int height);

void screen_display();

void maze_display();

void characters_display();

void characters_light();

void keyboard(unsigned char c, int x, int y);

void idle();

bool get_opt_args(int argc, char *const *argv);

void create_position_observer(int anglealpha, int anglebeta, int radi);

void addPath(int i, int j, Color color, float height);

void ambient_light_display();

int main(int argc, char **argv) {
    if (argc < 4 || argc > 5) {
        printf("Usage:\n\t./game [<rows>=20 <cols>=20 --func={dfs, heur} [--print]]\n");
        exit(0);
    }
    anglealpha = 90;
    anglebeta = -2;
    Dimensions new_dimensions = getDimensions(argc, argv);
    dimensions = make_shared<Dimensions>(new_dimensions);
    bool mustPrint = get_opt_args(argc, argv);
    graph->start();
    if (mustPrint)
        graph->print();
    MainCharacter main_character = MainCharacter(graph->get_main_coords(), SIDE_LENGTH);
    EnemyCharacter enemy_character = EnemyCharacter(graph->get_enemy_coords(), SIDE_LENGTH);
    Context new_cont = Context(graph, &main_character, &enemy_character, SIDE_LENGTH);
    context = make_shared<Context>(new_cont);
    config_opengl(argc, argv);
}

bool get_opt_args(int argc, char *const *argv) {
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
                GraphDfsHeur graphHeur = GraphDfsHeur(dimensions->cols, dimensions->rows);
                graph = make_shared<GraphDfsHeur>(graphHeur);
                if (!graph) {
                    printf("malloc failed\n");
                    exit(-1);
                }
            } else if (equal(tok.begin(), tok.end(), string("dfs").begin())) {
                GraphDFS graphDfs = GraphDFS(dimensions->cols, dimensions->rows);
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
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);

    glBindTexture(GL_TEXTURE_2D, TEXTURE_STONE);
    LoadTexture(std::string("textures/stone.jpeg").c_str(), 512);
    glBindTexture(GL_TEXTURE_2D, TEXTURE_GRASS);
    LoadTexture(std::string("textures/grass.jpg").c_str(), 512);
    glDisable(GL_TEXTURE_2D);
    glutMainLoop();
}


void display() {
    glClearColor(BACKGROUND_COLOR);
    glNormal3f(0, 0, -1);
    maze_display();
    characters_display();
    screen_display();
    ambient_light_display();
    characters_light();
    glutSwapBuffers();
}

void characters_display() {
    context->getMainCharacter()->draw(COLORTUP_MAIN_FACE_VERTEX);
    context->getEnemyCharacter()->draw(COLORTUP_ENEMY_FACE_VERTEX);
    context->drawBullet();
    float color[] = {1,1,1};
    setMaterial(color);
}

void characters_light() {
    context->getMainCharacter()->drawLight();
    context->getEnemyCharacter()->drawLight();
}


void screen_display() {
    float scale = 0.2;
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0, WIDTH, 0.0, HEIGHT);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    glLoadIdentity();
    string s = "Time left:";
    int x_chars = (s.length() + 3) * 90 * scale;
    glTranslatef(WIDTH - x_chars, HEIGHT * 9 / 10, 1);
    glScalef(scale, scale, 1);
    s = s.append(std::to_string((int) time_left));
    void *font = GLUT_STROKE_MONO_ROMAN;
    int x = 0;
    for (char c: s) {
        glPushMatrix();
        glTranslatef(x * 90, 0, 0);
        glutStrokeCharacter(font, c);
        glPopMatrix();
        x++;
    }
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void ambient_light_display() {
    GLfloat color[4] = {0.1, 0.1, 0.1, 1};
    GLfloat vec[4] = {100, 100, 1000};
    glLightfv (GL_LIGHT0, GL_POSITION, vec);
    glLightfv(GL_LIGHT0, GL_AMBIENT, color);
    glEnable(GL_LIGHT0);
}

void maze_display() {
    int i, j;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    create_position_observer(anglealpha, anglebeta, 300);
    GLfloat material[4] = {0.7, 0.7, 0.7, 1};
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-WIDTH * 2 / 3, WIDTH * 2 / 3, -HEIGHT * 2 / 3, HEIGHT * 2 / 3, -10000, 20000);
    for (int tile_count = 0; tile_count < COLUMNS * ROWS; tile_count++) {
        pair<int, int> *coords = graph->toCoordinates(tile_count);
        i = coords->first;
        j = coords->second;
        if (graph->is_wall(tile_count)) {
            addSquare(i, j, COLOR_WALL, 40);
        } else {
            addPath(i, j, COLOR_PATH, FLOOR);
        }
    }
}

void create_position_observer(int alpha, int beta, int radi) {
    float upx, upy, upz;
    float x = (float) radi * cos(alpha * 2 * PI / 360.0) * cos(beta * 2 * PI / 360.0);
    float y = (float) radi * sin(beta * 2 * PI / 360.0);
    float z = (float) radi * sin(alpha * 2 * PI / 360.0) * cos(beta * 2 * PI / 360.0);
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
    float modul = sqrt(upx * upx + upy * upy + upz * upz);
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
        case 'w':
        case 'W':
            context->move_main(Direction::TURN_UP);
            break;
        case 's':
        case 'S':
            context->move_main(Direction::TURN_DOWN);
            break;
        case 'e':
        case 'E':
            context->shoot();
            break;
        case 'r':
        case 'R':
            context->remove_shoot();
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
    time_left = time_maze - (((double) t) / (1000));
    if (last_t == 0) {
        last_t = t;
    } else {
        context->integrate(context->getMainCharacter(), t - last_t);
        context->integrate(context->getEnemyCharacter(), t - last_t);
        context->integrateBullet(t - last_t);
        last_t = t;
    }
    int num = rand() % 100;
    if (num == 7) {
        context->move_enemy(static_cast<Direction>(rand() % 5));
    }
    glutPostRedisplay();
}

void addSquare(int i, int j, struct Color color, int height) {
    glMatrixMode(GL_MODELVIEW);
    glPolygonMode(GL_FRONT, GL_FILL);
    glBindTexture(GL_TEXTURE_2D, TEXTURE_STONE);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS); // Up
    glNormal3f(0, 0, -1);
    glVertex3f(i * WIDTH / COLUMNS, j * HEIGHT / ROWS, height);
    glTexCoord2f(1.0, 0.0);
    glVertex3f((i + 1) * WIDTH / COLUMNS, j * HEIGHT / ROWS, height);
    glTexCoord2f(1.0, 1.0);
    glVertex3f((i + 1) * WIDTH / COLUMNS, (j + 1) * HEIGHT / ROWS, height);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(i * WIDTH / COLUMNS, (j + 1) * HEIGHT / ROWS, height);
    glEnd();

    glBegin(GL_QUADS); // Down
    glTexCoord2f(0.0, 0.0);
    glVertex3f(i * WIDTH / COLUMNS, j * HEIGHT / ROWS, FLOOR);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(i * WIDTH / COLUMNS, (j + 1) * HEIGHT / ROWS, FLOOR);
    glTexCoord2f(1.0, 1.0);
    glVertex3f((i + 1) * WIDTH / COLUMNS, (j + 1) * HEIGHT / ROWS, FLOOR);
    glTexCoord2f(1.0, 0.0);
    glVertex3f((i + 1) * WIDTH / COLUMNS, j * HEIGHT / ROWS, FLOOR);
    glEnd();

    glBegin(GL_QUADS); // Back Wall
    glNormal3f(0, 0.1, 0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(i * WIDTH / COLUMNS, ((j + 1) * HEIGHT / ROWS), height);
    glTexCoord2f(0.0, 1.0);
    glVertex3f((i + 1) * WIDTH / COLUMNS, (j + 1) * HEIGHT / ROWS, height);
    glTexCoord2f(1.0, 1.0);
    glVertex3f((i + 1) * WIDTH / COLUMNS, (j + 1) * HEIGHT / ROWS, FLOOR);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(i * WIDTH / COLUMNS, (j + 1) * HEIGHT / ROWS, FLOOR);
    glEnd();

    glBegin(GL_QUADS); // Front Wall
    glNormal3f(0, -0.1, 0.1);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(i * WIDTH / COLUMNS, j * HEIGHT / ROWS, FLOOR);
    glTexCoord2f(1.0, 0.0);
    glVertex3f((i + 1) * WIDTH / COLUMNS, j * HEIGHT / ROWS, FLOOR);
    glTexCoord2f(1.0, 1.0);
    glVertex3f((i + 1) * WIDTH / COLUMNS, j * HEIGHT / ROWS, height);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(i * WIDTH / COLUMNS, j * HEIGHT / ROWS, height);
    glEnd();

    glBegin(GL_QUADS); // Left Wall
    glNormal3f(-0.1, 0, 0.1);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(i * WIDTH / COLUMNS, j * HEIGHT / ROWS, height);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(i * WIDTH / COLUMNS, (j + 1) * HEIGHT / ROWS, height);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(i * WIDTH / COLUMNS, (j + 1) * HEIGHT / ROWS, FLOOR);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(i * WIDTH / COLUMNS, j * HEIGHT / ROWS, FLOOR);
    glEnd();

    glBegin(GL_QUADS); // Right Wall
    glNormal3f(+0.1, 0,0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f((i + 1) * WIDTH / COLUMNS, j * HEIGHT / ROWS, height);
    glTexCoord2f(0.0, 1.0);
    glVertex3f((i + 1) * WIDTH / COLUMNS, j * HEIGHT / ROWS, FLOOR);
    glTexCoord2f(1.0, 1.0);
    glVertex3f((i + 1) * WIDTH / COLUMNS, (j + 1) * HEIGHT / ROWS, FLOOR);
    glTexCoord2f(1.0, 0.0);
    glVertex3f((i + 1) * WIDTH / COLUMNS, (j + 1) * HEIGHT / ROWS, height);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glNormal3f(0, 0, -1);
}

void addPath(int i, int j, Color color, float height) {
    glMatrixMode(GL_MODELVIEW);
    glBindTexture(GL_TEXTURE_2D, TEXTURE_GRASS);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    glNormal3f(0, 0, -1);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(i * WIDTH / COLUMNS, j * HEIGHT / ROWS, height);
    glTexCoord2f(1, 0.0);
    glVertex3f((i + 1) * WIDTH / COLUMNS, j * HEIGHT / ROWS, height);
    glTexCoord2f(1.0, 1.0);
    glVertex3f((i + 1) * WIDTH / COLUMNS, (j + 1) * HEIGHT / ROWS, height);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(i * WIDTH / COLUMNS, (j + 1) * HEIGHT / ROWS, height);
    glEnd();


    glDisable(GL_TEXTURE_2D);
}

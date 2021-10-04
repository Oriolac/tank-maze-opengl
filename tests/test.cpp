#include "../src/kruskal.cpp"

using namespace std;

#define assertEquals(x, y) if((x) != (y)) {std::cout << "Failed: " << __FUNCTION__ << " in line " << __LINE__ << "\n\tExpected: " << (x) << " Actual: " << (y) << "\n"; return -1;}
#define ADD(x) if (x() == -1) {std::cout << "FAIL\n"; return -1;}
#define TEST(x) int x()

TEST(isAroundEmptyGraphTest) {
    GraphKruskal g(4, 4);
    assertEquals(true, g.isAround(0, 1));
    assertEquals(false, g.isAround(0, 3));
    return 1;
}

TEST(isAroundKruskalGraphTest) {
    GraphKruskal g = createLaberinthWithKruskal(2, 2);
    assertEquals(true, g.isAround(0, 1));
    assertEquals(false, g.isAround(0, 3));
    return 1;
}

TEST(toPositionTest) {
    GraphKruskal g(4, 3);
    assertEquals(0, g.toPosition(0,0));
    assertEquals(1, g.toPosition(1,0));
    assertEquals(2, g.toPosition(2,0));
    assertEquals(3, g.toPosition(3,0));
    assertEquals(-1, g.toPosition(4,0));
    assertEquals(4, g.toPosition(0,1));
    assertEquals(5, g.toPosition(1,1));
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            assertEquals(i + j * 4, g.toPosition(i, j))
        }
    }
    return 1;
}

TEST(createWithKruskalTest) {
    GraphKruskal g = createLaberinthWithKruskal(1, 1);
    g.printInitial();
    g.start();
    g.printMaze();
    return 1;
}

TEST(toCoordinatesTest) {
    GraphKruskal g2 = createLaberinthWithKruskal(2, 2);
    pair<int, int> *x = g2.toCoordinates(5);
    assertEquals(1,x->first);
    assertEquals(1,x->second);
    GraphKruskal g4 = createLaberinthWithKruskal(4, 4);
    x = g4.toCoordinates(7);
    assertEquals(1,x->first);
    assertEquals(1,x->second);
    x = g4.toCoordinates(8);
    assertEquals(2,x->first);
    assertEquals(1,x->second);
    return 1;
}

TEST(toPositionKruskalTest) {
    GraphKruskal g2 = createLaberinthWithKruskal(2, 2);
    assertEquals(5, g2.toPosition(1,1));
    assertEquals(6, g2.toPosition(2,1));
    assertEquals(9, g2.toPosition(1,2));
    assertEquals(10, g2.toPosition(2,2));
    return 1;
}

int main() {
    ADD(createWithKruskalTest);
    ADD(isAroundEmptyGraphTest);
    ADD(toPositionTest);
    ADD(isAroundKruskalGraphTest);
    ADD(toCoordinatesTest);
    ADD(toPositionKruskalTest);
    printf("All okey!\n");
}
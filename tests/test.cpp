#include "../src/kruskal.cpp"

using namespace std;

#define assertEquals(x, y) if((x) != (y)) {std::cout << "Failed: " << __FUNCTION__ << " in line " << __LINE__ << "\n\tExpected: " << (x) << " Actual: " << (y) << "\n"; return -1;}
#define ADD(x) if (x() == -1) {std::cout << "FAIL\n"; return -1;}
#define TEST(x) int x()

TEST(isAroundTest) {
    assertEquals(true, isAround(0, 1, 4, 3));
    assertEquals(false, isAround(0, 3, 4, 3));
    return 1;
}

TEST(toPositionTest) {
    Graph g(4, 3);
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

int main() {
    ADD(isAroundTest);
    ADD(toPositionTest);
    printf("All okey!\n");
}
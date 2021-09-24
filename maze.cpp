#include <cstdio>
#include <cstdlib>

#define DEFAULT_ROWS 20
#define DEFAULT_COLS 20

class Dimensions {
public:
    const int rows;
    const int cols;

    Dimensions(int x, int y) : rows(x), cols(y) {}
};

enum TypeTile {
    Wall, Path
};

int getLongFromStr(char *const *argv, int pos);
Dimensions getDimensions(int argc, char **argv);

int main(int argc, char **argv) {
    if (argc != 1 && argc != 3) {
        printf("Usage:\n\t./maze [<rows>=20 <cols>=20]\n");
        return 0;
    }
    Dimensions dimensions = getDimensions(argc, argv);
    printf("%ix%i\n", dimensions.rows, dimensions.cols);
}

int getLongFromStr(char *const *argv, int pos) {
    int res = (int) strtol(argv[pos], nullptr, 10);
    return res == 0 ? DEFAULT_ROWS : res;
}

Dimensions getDimensions(int argc, char **argv) {
    int rows, cols;
    if (argc < 3) {
        rows = DEFAULT_ROWS;
        cols = DEFAULT_COLS;
    } else {
        rows = getLongFromStr(argv, 1);
        cols = getLongFromStr(argv, 2);
    }
    return {rows, cols};
}

#define DEFAULT_ROWS 20
#define DEFAULT_COLS 20


int getLongFromStr(char *const *argv, int pos) {
    int res = (int) strtol(argv[pos], nullptr, 10);
    return res;
}

class Dimensions {
public:
    const int rows;
    const int cols;
};

Dimensions getDimensions(int argc, char **argv);

Dimensions getDimensions(int argc, char **argv) {
    int rows, cols;
    if (argc < 3) {
        rows = DEFAULT_ROWS;
        cols = DEFAULT_COLS;
    } else {
        cols = getLongFromStr(argv, 1);
        cols = cols == 0 ? DEFAULT_COLS : cols;
        rows = getLongFromStr(argv, 2);
        rows = rows == 0 ? DEFAULT_COLS : rows;
    }
    return {rows, cols};
}
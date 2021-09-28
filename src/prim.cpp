#include <iostream>
#include <vector>
#include <algorithm>

#define INF 9999999

std::vector<int> returnVector(int n, int i);

bool isAway(int i, int j);

class Graph {
private:
    std::vector<std::vector<int>> adjacency;
    const int N;
    const int xDim;
    const int yDim;
public:
    Graph(int xDim, int yDim) : N(xDim * yDim), xDim(xDim), yDim(yDim) {
        for (int i = 0; i < N; i++) {
            adjacency.push_back(returnVector(N, i));
        }
        printf("%ld\n", adjacency.size());
    }

    void print_adjacency() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%i", adjacency[i][j]);
            }
            printf("\n");
        }
    }

    bool isAround(int i, int j) const {
        bool isVerticallyAround = i == j + xDim || i == j - xDim;
        bool isHorizontallyAround = false;
        if (i / yDim == j / yDim)
            isHorizontallyAround = i == j + 1 || i == j - 1;
        return isVerticallyAround or isHorizontallyAround;
    }

    std::vector<int> returnVector(int n, int i) const {
        int tmpArray[n];
        for (int j = 0; j < n; j++) {
            int tmp;
            if (isAround(i, j))
                tmp = 1;
            else
                tmp = 0;
            tmpArray[j] = tmp;
        }
        return {tmpArray, tmpArray + sizeof tmpArray / sizeof tmpArray[0]};
    }

    void kruskal() {
        int uRep, vRep;
        sort(this->adjacency.begin(), this->adjacency.end());
        for (int i = 0; i < adjacency.size(); i++) {
        }
    }

};

int start() {

}


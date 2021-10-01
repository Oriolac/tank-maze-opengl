import random

class Maze:

    def __init__(self, cols, rows):
        self.rows = rows
        self.cols = cols
        self.nums = rows * cols
        self.walls = set()
        self.paths = set()

    def initial_point(self):
        return self.to_pos(self, 1, 1)


    def to_coord(self, pos):
        return (pos % self.cols, pos // self.cols)

    def to_pos(self, x, y):
        if (x < 0 or x >= self.cols or y < 0 or y >= self.rows):
            return -1
        return x + y * self.cols;

    def directions(self, pos):
        x, y = self.to_coord(pos)
        res = []
        for i in [-1,0,1]:
            for j in [-1,0,1]:
                if i != 0 and j != 0:
                    res.append((x+i, y+j))
        res = list(filter(lambda x: x not in self.walls, map(lambda x: self.to_pos(x[0], x[1]), res)))
        return random.shuffle(res)


    def dfs(self):
        visited = set()
        stack = [self.initial_point()]
        while len(stack) != 0:
            node = stack.pop(0)
            if node in self.walls:
                continue
            visited.add(node)
            for next in self.directions(node):
                stack.append(node)
        

    def print(self):
        pass


if __name__ == "__main__":
    maze = Maze(5,5)
    assert maze.to_pos(1,1) == 6
    assert maze.to_coord(6) == (1,1)
    assert maze.to_coord(7) == (2,1)

import random
import time


class Maze:

    def __init__(self, cols, rows):
        self.rows = rows
        self.cols = cols
        self.nums = rows * cols
        self.walls = set()
        self.paths = set()

    def initial_point(self):
        return self.to_pos(1, 1)

    def in_bounds(self, x, y):
        if self.to_pos(x, y) in self.walls:
            return False
        return x >= 0 and y >= 0 and x < self.cols and y < self.rows

    def to_coord(self, pos):
        return (pos % self.cols, pos // self.cols)

    def to_pos(self, x, y):
        if (x < 0 or x >= self.cols or y < 0 or y >= self.rows):
            return -1
        return x + y * self.cols;

    def directions(self, node):
        dirs = [(0, 1), (1,0), (-1, 0), (0, -1)]
        res = []
        for move in dirs:
            x, y = self.to_coord(node)
            nextX, nextY = self.move_by_pos(x, y, move)
            furX, furY = self.move_by_pos(nextX, nextY, move)
            if self.in_bounds(nextX, nextY) and self.in_bounds(furX, furY):
                res.append(move)
        return [res[0]] if len(res) > 0 else []

    def move_by_pos(self, x, y, move):
        newX, newY = (x + move[0], y + move[1])
        newPos = self.to_pos(newX, newY)
        return (-10, -10) if newPos == -1 or newPos in self.walls else (newX, newY)

    def dfs(self):
        stack = [self.initial_point()]
        while len(stack) != 0:
            print(stack)
            node = stack.pop(0)
            if node in self.walls or node in self.paths:
                continue
            print(node)
            self.paths.add(node)
            for move in self.directions(node):
                x, y = self.to_coord(node)
                nextX, nextY = self.move_by_pos(x, y, move)
                furX, furY = self.move_by_pos(nextX, nextY, move)
                nextPos = self.to_pos(nextX, nextY)
                furPos = self.to_pos(furX, furY)
                print(nextPos, furPos, "in bounds")
                stack.insert(0, nextPos)
                self.paths.add(nextPos)
                stack.insert(0, furPos)

    def generate(self):
        for i in range(self.cols):
            self.walls.add(i)
            self.walls.add(i + self.cols * self.rows - self.cols)
        for i in range(self.rows):
            self.walls.add(i * self.cols)
            self.walls.add(i * self.cols + self.cols - 1)
        print(self.walls)
        self.dfs()

    def print(self):
        for i in range(self.cols):
            for j in range(self.rows):
                pos = self.to_pos(i, j)
                psrt = " " if pos in self.paths else "X"
                print(psrt, end="")
            print()

if __name__ == "__main__":
    maze = Maze(5,5)
    assert maze.to_pos(1,1) == 6
    assert maze.to_coord(6) == (1,1)
    assert maze.to_coord(7) == (2,1)

    maze = Maze(5,5)
    maze.generate()
    maze.print()

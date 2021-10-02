import random
import itertools
import time

class Maze:

    def __init__(self, cols = 20, rows = 20, x_size=400, y_size = 400):
        self.cols = cols
        self.rows = rows
        self.x_size = x_size
        self.y_size = y_size
        self.directions = [(1,0), (-1,0), (0,1), (0,-1)]

    def initMaze(self):
        maze =  []
        for i in range(self.rows):
            row = []
            for j in range(self.cols):
                row.append("#")
            maze.append(row)
        return maze
        
    def createMaze(self, maze, visited = []):
        curr_node = (1,1)
        curr_direction = (-1,0)
        maze[curr_node[1]][curr_node[0]] = " "
        visited.append(curr_node)
        while (visited != []):
            curr_node = visited.pop()
            possibleDirections = self.getPossibleNextDirections(curr_node, maze)
            if possibleDirections != []:
                curr_direction = self.getDirection(curr_direction, possibleDirections)
                next_node = (curr_node[0] + curr_direction[0], curr_node[1] + curr_direction[1])
                maze[next_node[1]][next_node[0]] = " "
                visited.append(curr_node)
                visited.append(next_node)
        return maze
            

    def getPossibleNextDirections(self, curr_node, maze):
        possible_directions = []
        for direction in self.directions:
            if (self.inScope(curr_node, direction, maze) and self.nextIsWall(curr_node, direction, maze) and self.checkNoblocks(curr_node, direction, maze)):
                possible_directions.append(direction)
        return possible_directions

    def inScope(self, curr_node, direction, maze):
        return (curr_node[1] + direction[1] * 2 >= 0)  and (curr_node[1] + direction[1] * 2 < self.cols) and (curr_node[0] + direction[0] * 2 >= 0)  and (curr_node[0] + direction[0] * 2 < self.rows) 

    def nextIsWall(self, curr_node, direction, maze):
        return maze[curr_node[1]+direction[1]][curr_node[0]+direction[0]] == "#"
    
    def checkNoblocks(self, curr_node, direction, maze):
        next_node = (curr_node[0] + direction[0], curr_node[1] + direction[1])
        return not self.checkTopLeftCorner(next_node, maze) and not self.checkTopRightCorner(next_node, maze) and not self.checkDownLeftCorner(next_node, maze) and not self.checkDownRightCorner(next_node, maze)
        
    def checkTopLeftCorner(self, next_node, maze):
        return maze[next_node[1]][next_node[0]-1] == " " and maze[next_node[1]-1][next_node[0]-1] == " " and maze[next_node[1]-1][next_node[0]] == " "

    def checkTopRightCorner(self, next_node, maze):
        return maze[next_node[1]][next_node[0]+1] == " " and maze[next_node[1]-1][next_node[0]+1] == " " and maze[next_node[1]-1][next_node[0]] == " "

    def checkDownLeftCorner(self, next_node, maze):
        return maze[next_node[1]][next_node[0]-1] == " " and maze[next_node[1]+1][next_node[0]-1] == " " and maze[next_node[1]+1][next_node[0]] == " "

    def checkDownRightCorner(self, next_node, maze):
        return maze[next_node[1]][next_node[0]+1] == " " and maze[next_node[1]+1][next_node[0]+1] == " " and maze[next_node[1]+1][next_node[0]] == " "

    def getDirection(self, curr_direction, possible_directions):
        list_directions = []
        for i in possible_directions:
            print("curr", i)
            if i == curr_direction:
                list_directions.append(i)
                list_directions.append(i)
            else:
                list_directions.append(i)
        res = random.choice(list_directions)
        return res

    def printMaze(self, maze):
        for row in maze:
            for cell in row:
                print(cell, end='')
            print()

if __name__ == '__main__':
    mazeObj = Maze()
    maze = mazeObj.initMaze()
    maze = mazeObj.createMaze(maze)
    mazeObj.printMaze(maze)

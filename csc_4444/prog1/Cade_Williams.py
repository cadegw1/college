# CSC 4444 - Artificial Intelligence
# Cade Williams - Project 1
import numpy as np

# Initializing environment with five dirty squares in the top row of the grid
grid = np.array([[False, False, False, False, False],
                [True, True, True, True, True],
                [True, True, True, True, True],
                [True, True, True, True, True],
                [True, True, True, True, True]])


class Agent:

    def __init__(self):
        self.position = [0, 4]  # (x, y) pair with 0-based columns and rows
        self.time = 0
        self.cost = 0

    def move(self, direction):
        if direction == "Left" and self.position[0] != 0:
            self.position[0] -= 1
        elif direction == "Right" and self.position[0] != 4:
            self.position[0] += 1
        elif direction == "Up" and self.position[1] != 0:
            self.position[1] -= 1
        elif direction == "Down" and self.position[1] != 4:
            self.position[1] += 1
        self.time += 1
        self._cost

    def suck(self):
        grid[self.position[1]][self.position[0]] = True
        self.time += 1
        self._cost

    def _cost(self):
        for row in grid:
            for column in grid:
                if not grid[column][row]:
                    self.cost += 2


if __name__ == "__main__":
    a = Agent()
    a.move("Up")
    a.move("Up")
    a.move("Up")
    a.move("Up")
    a.suck()
    print(grid[0][1])


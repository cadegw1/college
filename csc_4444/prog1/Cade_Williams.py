# CSC 4444 - Artificial Intelligence
# Cade Williams - Project 1
import numpy as np

# Initializing environment with five dirty squares in the top row of the grid
env = np.array([[False, False, False, False, False],        # [0, 1, 2, 3, 4]
                [True, True, True, True, True],             # [1, x, x, x, x]
                [True, True, True, True, True],             # [2, x, x, x, x]
                [True, True, True, True, True],             # [3, x, x, x, x]
                [True, True, True, True, True]])            # [4, x, x, x, x]


class Agent:

    # initializes the agent at a position, time = 0, and cost = 0
    def __init__(self):
        self.position = [0, 4]  # (x, y) pair with 0-based columns and rows
        self.time = 0
        self.cost = 0

    # method to traverse through the environment
    def move(self, direction):
        if direction == "Left" and self.position[0] != 0:
            self.position[0] -= 1
        elif direction == "Right" and self.position[0] != 4:
            self.position[0] += 1
        elif direction == "Up" and self.position[1] != 0:
            self.position[1] -= 1
        elif direction == "Down" and self.position[1] != 4:
            self.position[1] += 1
        else:
            print("ERROR: Agent in unknown position")
        self.time += 1
        self.incur_cost()

    def suck(self):
        env[self.position[1]][self.position[0]] = True     # env[y][x]
        self.time += 1
        self.incur_cost()

    # method to increment cost at the end of each time step
    def incur_cost(self):
        for row in env:
            for element in row:
                if not element:
                    self.cost += 2


if __name__ == "__main__":
    a = Agent()
    a.move("Up")
    a.move("Up")
    a.move("Up")
    a.move("Up")
    a.suck()
    print(env[0][0], a.time, a.cost)


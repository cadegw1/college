# CSC 4444 - Artificial Intelligence
# Cade Williams - Project 1
import search as s


class FullyObservableVacuumProblem(s.Problem):

    def __init__(self, initial, g):
        self.initial = initial
        self.goal = g

    def actions(self, state):
        return ["Left", "Right", "Up", "Down", "Suck"]

    def result(self, state, agent_location, action):
        x, y = agent_location
        if x == 0 and action == "Left":
            return state
        elif x == 4 and action == "Right":
            return state
        elif y == 0 and action == "Down":
            return state
        elif y == 4 and action == "Up":
            return state
        elif action == "Suck" and state[agent_location] == 'Clean':
            return state
        else:
            if action == "Left":
                x -= 1
            elif action == "Right":
                x += 1
            elif action == "Down":
                y -= 1
            elif action == "Up":
                y += 1
            elif action == "Suck":
                state[agent_location] = 'Clean'
        return state

    def goal_test(self, state):
        # is_goal = True
        # for square in state:
        #     if state[square] == 'Dirty':
        #         is_goal = False
        # return is_goal
        return state == self.goal

    def path_cost(self, c, state1, action, state2):
        for square in state2:
            if state2[square] == 'Dirty':
                c += 2
        return c

    def h(self, args):
        return 9

    def value(self, state):
        return


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


if __name__ == '__main__':
    """Initializing the environment with a dictionary
    ex: (x, y): 'Status of square'"""
    env = {(0, 4): 'Dirty', (1, 4): 'Dirty', (2, 4): 'Dirty', (3, 4): 'Dirty', (4, 4): 'Dirty',
           (0, 3): 'Clean', (1, 3): 'Clean', (2, 3): 'Clean', (3, 3): 'Clean', (4, 3): 'Clean',
           (0, 2): 'Clean', (1, 2): 'Clean', (2, 2): 'Clean', (3, 2): 'Clean', (4, 2): 'Clean',
           (0, 1): 'Clean', (1, 1): 'Clean', (2, 1): 'Clean', (3, 1): 'Clean', (4, 1): 'Clean',
           (0, 0): 'Clean', (1, 0): 'Clean', (2, 0): 'Clean', (3, 0): 'Clean', (4, 0): 'Clean'}

    goal = {(0, 4): 'Clean', (1, 4): 'Clean', (2, 4): 'Clean', (3, 4): 'Clean', (4, 4): 'Clean',
            (0, 3): 'Clean', (1, 3): 'Clean', (2, 3): 'Clean', (3, 3): 'Clean', (4, 3): 'Clean',
            (0, 2): 'Clean', (1, 2): 'Clean', (2, 2): 'Clean', (3, 2): 'Clean', (4, 2): 'Clean',
            (0, 1): 'Clean', (1, 1): 'Clean', (2, 1): 'Clean', (3, 1): 'Clean', (4, 1): 'Clean',
            (0, 0): 'Clean', (1, 0): 'Clean', (2, 0): 'Clean', (3, 0): 'Clean', (4, 0): 'Clean'}

    problem = FullyObservableVacuumProblem(env, goal)
    s.astar_search(problem, problem.h)



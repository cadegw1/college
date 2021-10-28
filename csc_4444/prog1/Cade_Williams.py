# CSC 4444 - Artificial Intelligence
# Cade Williams - Project 1
import search as s


class VacuumProblem(s.Problem):

    def __init__(self, initial, environment, goal=False):
        super().__init__(initial, goal)
        self.env = environment
        self.dirty_squares = self.get_dirty_squares()

    def get_dirty_squares(self):
        dirty_square_list = []
        for square in self.env:
            if self.env[square] == 'Dirty':
                dirty_square_list.append(square)
        return dirty_square_list

    def actions(self, state):
        x, y = state
        possible_actions = ['Suck', 'Left', 'Right', 'Down', 'Up']
        # if self.env[state] == 'Dirty':
        #     return ['Suck']
        if x-1 < 0:
            possible_actions.remove('Left')
        if x+1 > 4:
            possible_actions.remove('Right')
        if y-1 < 0:
            possible_actions.remove('Down')
        if y+1 > 4:
            possible_actions.remove('Up')
        return possible_actions

    def result(self, state, action):
        x, y = state
        if action == "Left":
            x -= 1
        elif action == "Right":
            x += 1
        elif action == "Down":
            y -= 1
        elif action == "Up":
            y += 1
        elif action == "Suck":
            self.env[(x, y)] = 'Clean'
            self.dirty_squares = self.get_dirty_squares()
        return x, y

    def goal_test(self, environment):
        self.dirty_squares = self.get_dirty_squares()
        return not self.dirty_squares

    # def path_cost(self, c, state1, action, state2):
    #     if action == 'Suck':
    #         c += 1 + ((len(self.dirty_squares) - 1) * 2)
    #     elif action in ['Left', 'Right', 'Down', 'Up']:
    #         c += 1 + (len(self.dirty_squares) * 2)
    #     return c

    def h1(self, node):
        x1, y1 = node.state
        first = True
        heuristic = 0
        for square in self.dirty_squares:
            x2, y2 = square
            new_heuristic = abs((x1 - x2)) + abs((y1 - y2))
            if first:
                heuristic = new_heuristic
                first = False
            elif heuristic > new_heuristic:
                heuristic = new_heuristic
        return heuristic + len(self.dirty_squares)

    def h2(self, node):
        x1, y1 = node.state
        first = True
        heuristic = 0
        for square in self.dirty_squares:
            x2, y2 = square
            new_heuristic = abs((x1 - x2)) + abs((y1 - y2))
            if first:
                heuristic = new_heuristic
                first = False
            elif heuristic < new_heuristic:
                heuristic = new_heuristic
        return heuristic + len(self.dirty_squares)


if __name__ == '__main__':
    """Initializing the environment with a dictionary
    ex: (x, y): 'Status of square'"""
    env1 = {(0, 4): 'Dirty', (1, 4): 'Dirty', (2, 4): 'Dirty', (3, 4): 'Dirty', (4, 4): 'Dirty',
            (0, 3): 'Clean', (1, 3): 'Clean', (2, 3): 'Clean', (3, 3): 'Clean', (4, 3): 'Clean',
            (0, 2): 'Clean', (1, 2): 'Clean', (2, 2): 'Clean', (3, 2): 'Clean', (4, 2): 'Clean',
            (0, 1): 'Clean', (1, 1): 'Clean', (2, 1): 'Clean', (3, 1): 'Clean', (4, 1): 'Clean',
            (0, 0): 'Clean', (1, 0): 'Clean', (2, 0): 'Clean', (3, 0): 'Clean', (4, 0): 'Clean'}

    print("A* Search with heuristic 1\r\n==========================")
    problem_with_h1 = VacuumProblem((0, 0), env1)
    node = s.astar_search(problem_with_h1, problem_with_h1.h1, display=True)
    print("\tPath: {}".format(node.path()))
    print("\tActions: {}".format(node.solution()))
    cost = []
    for n in node.path():
        cost.append(n.path_cost)
    print("\tCost: {}\r\n".format(cost))

    env2 = {(0, 4): 'Dirty', (1, 4): 'Dirty', (2, 4): 'Dirty', (3, 4): 'Dirty', (4, 4): 'Dirty',
            (0, 3): 'Clean', (1, 3): 'Clean', (2, 3): 'Clean', (3, 3): 'Clean', (4, 3): 'Clean',
            (0, 2): 'Clean', (1, 2): 'Clean', (2, 2): 'Clean', (3, 2): 'Clean', (4, 2): 'Clean',
            (0, 1): 'Clean', (1, 1): 'Clean', (2, 1): 'Clean', (3, 1): 'Clean', (4, 1): 'Clean',
            (0, 0): 'Clean', (1, 0): 'Clean', (2, 0): 'Clean', (3, 0): 'Clean', (4, 0): 'Clean'}

    print("A* Search with heuristic 2\r\n==========================")
    problem_with_h2 = VacuumProblem((0, 0), env2)
    node = s.astar_search(problem_with_h2, problem_with_h2.h2, display=True)
    print("\tPath: {}".format(node.path()))
    print("\tActions: {}\r\n".format(node.solution()))





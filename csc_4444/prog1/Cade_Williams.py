# CSC 4444 - Artificial Intelligence
# Cade Williams - Project 1
import search as s


class VacuumProblem(s.Problem):

    def __init__(self, initial, goal=True):
        super().__init__(initial, goal)

    def actions(self, state):
        x, y = state
        possible_actions = ['Suck', 'Left', 'Right', 'Down', 'Up']

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
            # TODO: add something here
            pass
        return x, y

    def goal_test(self, state):
        is_goal = True
        for square in state:
            if state[square] == 'Dirty':
                is_goal = False
        return is_goal
        return state == self.goal

    def h(self, node):
        return 9


if __name__ == '__main__':
    """Initializing the environment with a dictionary
    ex: (x, y): 'Status of square'"""
    env = {(0, 4): 'Dirty', (1, 4): 'Dirty', (2, 4): 'Dirty', (3, 4): 'Dirty', (4, 4): 'Dirty',
           (0, 3): 'Clean', (1, 3): 'Clean', (2, 3): 'Clean', (3, 3): 'Clean', (4, 3): 'Clean',
           (0, 2): 'Clean', (1, 2): 'Clean', (2, 2): 'Clean', (3, 2): 'Clean', (4, 2): 'Clean',
           (0, 1): 'Clean', (1, 1): 'Clean', (2, 1): 'Clean', (3, 1): 'Clean', (4, 1): 'Clean',
           (0, 0): 'Clean', (1, 0): 'Clean', (2, 0): 'Clean', (3, 0): 'Clean', (4, 0): 'Clean'}
    action_list = ['Suck', 'Left', 'Right', 'Down', 'Up']

    graph_dict = {}
    for x in range(0, 5):
        for y in range(0, 5):
            next_states = {'Suck': [(x, y)], 'Left': [(x-1, y)], 'Right': [(x+1, y)],
                           'Down': [(x, y-1)], 'Up': [(x, y+1)]}
            # next_states = [(x-1, y), (x+1, y), (x, y-1), (x, y+1)]
            graph_dict[(x, y)] = {}
            for action in action_list:
                tx, ty = next_states[action][0]
                if tx < 0 or tx > 4 or ty < 0 or ty > 4:
                    del next_states[action]
                graph_dict[(x, y)] = next_states

    new_problem = VacuumProblem((0, 0))
    print(s.astar_search(new_problem, new_problem.h))
    #
    # graph = s.Graph(graph_dict=graph_dict)
    # problem = s.GraphProblem(initial=(0, 0), goal=True, graph=graph)
    # print(s.astar_search(problem, problem.h))





# CSC 4444 - Artificial Intelligence
# Cade Williams - Project 1
# Packages - aima-python
import search as s


class VacuumProblem(s.Problem):

    def __init__(self, initial, goal=()):
        super().__init__(initial, goal)
        self.cost = 0

    def actions(self, state):
        # Returns list of possible actions in current state
        x, y = state[0]
        possible_actions = ['Suck', 'Left', 'Right', 'Down', 'Up']
        if x == 1:
            possible_actions.remove('Left')
        if x == 5:
            possible_actions.remove('Right')
        if y == 1:
            possible_actions.remove('Down')
        if y == 5:
            possible_actions.remove('Up')
        if (x, y) not in state[1]:
            possible_actions.remove('Suck')
        return possible_actions

    def result(self, state, action):
        # Returns resulting state of action in given state
        x, y = state[0]
        result_state = list(state)
        if action == "Left":
            x -= 1
        elif action == "Right":
            x += 1
        elif action == "Down":
            y -= 1
        elif action == "Up":
            y += 1
        elif action == "Suck":
            result_state[1] = list(state[1])
            result_state[1].remove((x, y))
            result_state[1] = tuple(result_state[1])
        result_state[0] = list(state[0])
        result_state[0] = [x, y]
        result_state[0] = tuple(result_state[0])
        return tuple(result_state)

    def goal_test(self, state):
        return state[1] == self.goal

    def path_cost(self, c, state1, action, state2):
        c += 1 + 2 * (len(state2[1]))
        return c

    def h1(self, node):
        # heuristic function 1 - (distance to closest dirty square) + (number of dirty squares)
        x1, y1 = node.state[0]
        first = True
        heuristic = 0
        dirty_squares = list(node.state[1])
        for square in dirty_squares:
            x2, y2 = square
            new_heuristic = abs((x1 - x2)) + abs((y1 - y2))
            if first:
                heuristic = new_heuristic
                first = False
            elif heuristic > new_heuristic:
                heuristic = new_heuristic
        return heuristic + len(node.state[1])

    def h2(self, node):
        # heuristic function 2 - (distance to furthest dirty square) + (number of dirty squares)
        x1, y1 = node.state[0]
        first = True
        heuristic = 0
        dirty_squares = list(node.state[1])
        for square in dirty_squares:
            x2, y2 = square
            new_heuristic = abs((x1 - x2)) + abs((y1 - y2))
            if first:
                heuristic = new_heuristic
                first = False
            elif heuristic < new_heuristic:
                heuristic = new_heuristic
        return heuristic + len(node.state[1])


if __name__ == '__main__':
    initially_dirty_squares = ((1, 5), (2, 5), (3, 5), (4, 5), (5, 5))

    print("A* Search with heuristic 1\r\n=============================================================================")
    problem_with_h1 = VacuumProblem(((1, 1), initially_dirty_squares))
    node = s.astar_search(problem_with_h1, problem_with_h1.h1, display=True)
    print("\tPath: {}".format(node.path()))
    print("\tActions: {}".format(node.solution()))
    cost = []
    for n in node.path():
        cost.append(n.path_cost)
    print("\tCost: {}\r\n".format(cost))

    print("A* Search with heuristic 2\r\n=============================================================================")
    problem_with_h2 = VacuumProblem(((1, 1), initially_dirty_squares))
    node = s.astar_search(problem_with_h2, problem_with_h2.h2, display=True)
    print("\tPath: {}".format(node.path()))
    print("\tActions: {}".format(node.solution()))
    cost = []
    for n in node.path():
        cost.append(n.path_cost)
    print("\tCost: {}\r\n".format(cost))





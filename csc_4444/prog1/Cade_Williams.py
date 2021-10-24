# CSC 4444 - Artificial Intelligence
# Cade Williams - Project 1
import agents as a
import search as s


if __name__ == "__main__":
    # Initializing environment with five dirty squares in the top row of the grid
    env = np.array([[False, False, False, False, False],    # [0, 1, 2, 3, 4]
                    [True, True, True, True, True],         # [1, x, x, x, x]
                    [True, True, True, True, True],         # [2, x, x, x, x]
                    [True, True, True, True, True],         # [3, x, x, x, x]
                    [True, True, True, True, True]])        # [4, x, x, x, x]
    a = Agent(env)
    a.move("Up")
    a.move("Up")
    a.move("Up")
    a.move("Up")
    a.suck()
    print(env[0][0], a.time, a.cost)


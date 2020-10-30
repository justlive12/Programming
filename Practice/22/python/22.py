maze = [
    "####B######################",
    "# #       #   #      #    #",
    "# # # ###### #### ####### #",
    "# # # #       #   #       #",
    "#   # # ######### # ##### #",
    "# # # #   #       #     # #",
    "### ### ### ############# #",
    "# #   #     # #           #",
    "# # #   ####### ###########",
    "# # # #       # #         C",
    "# # ##### ### # # ####### #",
    "# # #     ### # #       # #",
    "#   ##### ### # ######### #",
    "######### ### #           #",
    "# ####### ### #############",
    "A           #   ###   #   #",
    "# ############# ### # # # #",
    "# ###       # # ### # # # #",
    "# ######### # # ### # # # F",
    "#       ### # #     # # # #",
    "# ######### # ##### # # # #",
    "# #######   #       #   # #",
    "# ####### ######### #######",
    "#         #########       #",
    "#######E############D######"
]
visited = []
exits = []


def bad_point(x, y):
    return y < 0 or x < 0 or x >= len(maze[0]) or y >= len(maze) or maze[y][
        x] == "#"


def wander_the_maze(x, y):
    if bad_point(x, y):
        return

    if (x, y) in visited:
        return

    visited.append((x, y))

    if maze[y][x] != " " and maze[y][x] not in exits:
        exits.append(maze[y][x])

    wander_the_maze(x - 1, y)
    wander_the_maze(x + 1, y)
    wander_the_maze(x, y + 1)
    wander_the_maze(x, y - 1)

x, y = map(int, input("Введите координаты x, y: ").split())
wander_the_maze(x, y)

if bad_point(x, y):
    print("Не верные координаты")
else:
    if (len(exits) == 0):
        print("Выхода нет")
    else:
        for exit in exits:
            print(exit, end=' ')
        print()
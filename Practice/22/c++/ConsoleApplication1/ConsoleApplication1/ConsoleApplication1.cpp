#include "pch.h"
#include <iostream>
#include <vector>    
#include <algorithm>  
#include <iterator>   

using namespace std;
using visits_t = std::vector<std::pair<int, int>>;
using exits_t = std::vector<char>;

const string maze[] = {
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
};

bool bad_point(int x, int y) {
	return x < 0 || x >= maze[0].length()
		|| y < 0 || y >= size(maze)
		|| maze[y][x] == '#';
}

void wander_the_maze(visits_t& visited, exits_t& exits, int x, int y) {

	if (bad_point(x, y)) {
		return;
	}

	if (find(visited.begin(), visited.end(), make_pair(x, y)) != visited.end()) {
		return;
	}

	visited.push_back(std::make_pair(x, y));

	if (maze[y][x] != ' ' && find(exits.begin(), exits.end(), maze[y][x]) == exits.end()) {
		exits.push_back(maze[y][x]);
	}

	wander_the_maze(visited, exits, x - 1, y);
	wander_the_maze(visited, exits, x + 1, y);
	wander_the_maze(visited, exits, x, y + 1);
	wander_the_maze(visited, exits, x, y - 1);

}

int main() {
	setlocale(LC_ALL, "ru");

	visits_t visited;
	exits_t  exits;

	int x, y;
	cout << "Введите координаты x, y: ";
	cin >> x >> y;

	if (bad_point(x, y)) {
		cout << "Неверные координаты" << endl;
	}
	else {
		wander_the_maze(visited, exits, x, y);

		if (exits.size() != 0) {
			for (char e : exits) {
				cout << e << " ";
			}
		}
		else {
			cout << "Выходов нет";
		}   cout << endl;
	}

}
#include "Chess.h"


using namespace sf;
using std::string;
using std::to_string;

//-------------
#define LENGTH 8
//------------------
#define PAWN 1
#define ROOK 2
#define KNIGHT 3
#define BITSHOP 4
#define QUEEN 5
#define KING 6


#define WHITE -1
#define BLACK 1



struct POS {
	int x = -1, y = -1;
}p_cur, t_transform;


struct FIG {
	int Pawn = PAWN,
		Rook = ROOK,
		Knight = KNIGHT,
		Bishop = BITSHOP,
		Queen = QUEEN,
		King = KING;
}figs;


struct STATUS {
	POS p_old,
		p_new,
		p_attak;
	int ok,
		attak,
		whose_move,
		fig,
		figNum;

}status;

int  size = 100, move = 0, x, y;
int shah = 0;
int mat = 0;
int mutare = 0;
int transformation = 0;


int board[LENGTH][LENGTH] =
{ 2, 3, 4, 5, 6, 4, 3, 2,
  1, 1, 1, 1, 1, 1, 1, 1,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
 -1,-1,-1,-1,-1,-1,-1,-1,
 -2,-3,-4,-5,-6,-4,-3,-2,
};


int PawnsJump[4][8] = {
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0 };


int RooksMove[2][2] = {
	0,0,
	0,0
};

int KingsMove[2] = {
	0,0
};


POS Get_Pos(int Board[8][8], int Figure, int Colour) {
	POS ret;
	for (int i = 0; i < LENGTH; i++)
		for (int j = 0; j < LENGTH; j++) {
			if (Board[i][j] == Colour * Figure) {
				ret.x = i;
				ret.y = j;
				return ret;
			}
		}
	return ret;
}



void Chess_move(struct STATUS& status, int board[8][8]) {


	int Figure = status.fig;
	POS Old_p = status.p_old,
		New_p = status.p_new;

	status.ok = 0;
	status.attak = 0;
	status.p_attak.x = -1;
	status.p_attak.y = -1;

	int end = 0;
	if (Figure == figs.Pawn && end == 0) {
		int curent_vec = (status.whose_move == WHITE) ? 6 : 1;

		if (Old_p.y == curent_vec) {
			if (New_p.y == Old_p.y + status.whose_move * 1 &&
				New_p.x == Old_p.x &&
				board[Old_p.y + status.whose_move * 1][Old_p.x] == 0) {
				status.ok = 1;
				status.attak = 0;
			}
			if (New_p.y == Old_p.y + status.whose_move * 2 &&
				New_p.x == Old_p.x &&
				board[Old_p.y + status.whose_move * 1][Old_p.x] == 0 &&
				board[Old_p.y + status.whose_move * 2][Old_p.x] == 0) {
				PawnsJump[status.whose_move][Old_p.x] = 1;
				status.ok = 1;
				status.attak = 0;
			}
		}
		else if (New_p.y == Old_p.y + status.whose_move * 1 &&
			New_p.x == Old_p.x &&
			board[Old_p.y + status.whose_move * 1][Old_p.x] == 0) {
			status.ok = 1;
			status.attak = 0;
			if (PawnsJump[status.whose_move][Old_p.x] == 1)
				if (PawnsJump[2 + status.whose_move][Old_p.x] == 0)
					PawnsJump[2 + status.whose_move][Old_p.x] += 1;
				else if (PawnsJump[2 + status.whose_move][Old_p.x] >= 1) {
					PawnsJump[2 + status.whose_move][Old_p.x] = 0;
					PawnsJump[status.whose_move][Old_p.x] = 0;
				}
			//return status;
		}
		//Правила для атаки
		if (New_p.y == Old_p.y + status.whose_move * 1 && New_p.x == Old_p.x - 1) {
			if (status.whose_move == WHITE && board[New_p.y][New_p.x] > 0 ||
				status.whose_move == BLACK && board[New_p.y][New_p.x] < 0) {
				status.ok = 1;
				status.attak = 1;
				status.p_attak.x = New_p.x;
				status.p_attak.y = New_p.y;
				if (PawnsJump[status.whose_move][Old_p.x] == 1)
					PawnsJump[status.whose_move][Old_p.x] = 0;
			}
			if (board[New_p.y][New_p.x] == 0 &&
				PawnsJump[status.whose_move][Old_p.x] == 1 &&
				PawnsJump[2 + status.whose_move][Old_p.x] == 1 &&
				(status.whose_move == WHITE && board[Old_p.y][New_p.x] > 0 ||
					status.whose_move == BLACK && board[Old_p.y][New_p.x] < 0)) {
				status.ok = 1;
				status.attak = 1;
				status.p_attak.x = New_p.x;
				status.p_attak.y = Old_p.y;
				if (PawnsJump[status.whose_move][Old_p.x] == 1) {
					PawnsJump[status.whose_move][Old_p.x] = 0;
					PawnsJump[2 + status.whose_move][Old_p.x] = 0;
				}
			}
		}
		if (New_p.y == Old_p.y + status.whose_move * 1 && New_p.x == Old_p.x + 1) {
			if (status.whose_move == WHITE && board[New_p.y][New_p.x] > 0 ||
				status.whose_move == BLACK && board[New_p.y][New_p.x] < 0) {
				status.ok = 1;
				status.attak = 1;
				status.p_attak.x = New_p.x;
				status.p_attak.y = New_p.y;
				//Правило удаления пешки из списка прыгнувших
				if (PawnsJump[status.whose_move][Old_p.x] == 1)
					PawnsJump[status.whose_move][Old_p.x] = 0;
				//return status;
			}
			if (board[New_p.y][New_p.x] == 0 &&
				PawnsJump[status.whose_move][Old_p.x] == 1 &&
				PawnsJump[2 + status.whose_move][Old_p.x] == 1 &&
				(status.whose_move == WHITE && board[Old_p.y][New_p.x] > 0 ||
					status.whose_move == BLACK && board[Old_p.y][New_p.x] < 0)) {
				status.ok = 1;
				status.attak = 1;
				status.p_attak.x = New_p.x;
				status.p_attak.y = Old_p.y;
				//Правило удаления пешки из списка прыгнувших
				if (PawnsJump[status.whose_move][Old_p.x] == 1) {
					PawnsJump[status.whose_move][Old_p.x] = 0;
					PawnsJump[2 + status.whose_move][Old_p.x] = 0;
				}
				//return status;
			}
		}

		if (New_p.y == ((status.whose_move == WHITE) ? 0 : 7)) {
			status.figNum = (status.whose_move == WHITE) ? -666 : 666;
		}
		end = 1;
	}
	if (Figure == figs.Rook && end == 0) {
		//Определение направления движения
		int start = -1, stop = -1;
		int stand = -1;//0-x,1-y
		int left_or_right = -1;
		if (status.p_old.x == status.p_new.x &&
			status.p_old.y != status.p_new.y ||
			status.p_old.x != status.p_new.x &&
			status.p_old.y == status.p_new.y) {
			if (status.p_old.x == status.p_new.x) {
				stand = 0;
				start = status.p_old.y;
				stop = status.p_new.y;
				if (status.p_old.y < status.p_new.y) {
					left_or_right = 1;
				}
				else if (status.p_old.y > status.p_new.y) {
					left_or_right = 0;
				}
			}
			else if (status.p_old.y == status.p_new.y) {
				stand = 1;
				start = status.p_old.x;
				stop = status.p_new.x;
				if (status.p_old.x < status.p_new.x) {
					left_or_right = 1;
				}
				else if (status.p_old.x > status.p_new.x) {
					left_or_right = 0;
				}
			}

			//Проверяем пусто ли на его пути
			int good = 1;
			if (left_or_right == 1) {
				for (int i = start; i < stop; i++) {
					if (((stand == 0) ? board[i][status.p_old.x] : board[status.p_old.y][i]) != 0 &&
						(i < stop)) {
						good = 0;
						break;
					}
				}
			}
			else if (left_or_right == 0) {
				for (int i = start - 1; i > stop; i--) {
					if (((stand == 0) ? board[i][status.p_old.x] : board[status.p_old.y][i]) != 0 &&
						(i > stop)) {
						good = 0;
						break;
					}
				}
			}

			if (good == 1) {
				if (((stand == 0) ? board[stop][status.p_old.x] : board[status.p_old.y][stop]) == 0)
					good = 1;
				else if (((stand == 0) ? board[stop][status.p_old.x] : board[status.p_old.y][stop]) > 0 &&
					status.whose_move == WHITE ||
					((stand == 0) ? board[stop][status.p_old.x] : board[status.p_old.y][stop]) < 0 &&
					status.whose_move == BLACK) {
					status.attak = 1;
					status.p_attak.x = status.p_new.x;
					status.p_attak.y = status.p_new.y;
					good = 1;
				}
				else
					good = 0;
			}

			if (good == 1) {
				if (status.p_old.x == 0 || status.p_old.x == 7)
					if (RooksMove[status.whose_move][(status.p_old.x == 0) ? 0 : 7] == 0)
						RooksMove[status.whose_move][(status.p_old.x == 0) ? 0 : 7] = 1;
				status.ok = 1;
			}
			//else
			//	status.ok = 0;
			/*
			std::cout << "_____" << std::endl;
			std::cout << good << std::endl;
			std::cout << "-----" << std::endl;
			*/
		}

		end = 1;
	}
	if (Figure == figs.Bishop && end == 0) {
		int good = 0;
		int ox = status.p_old.x;
		int oy = status.p_old.y;
		int nx = status.p_new.x;
		int ny = status.p_new.y;

		if (nx - ox == ny - oy) {
			if (nx > ox && ny > oy) {
				for (int i = oy, j = ox; i < ny || j < nx; i++, j++)
					if (board[i][j] == 0)
						good = 1;
					else if (board[i][j] != 0) {
						good = 0;
						break;
					}
			}
		}
		if (nx - ox == oy - ny) {
			if (nx > ox && ny < oy) {
				for (int i = oy, j = ox; i > ny || j < nx; i--, j++)
					if (board[i][j] == 0)
						good = 1;
					else if (board[i][j] != 0) {
						good = 0;
						break;
					}
			}
		}
		if (ox - nx == ny - oy) {
			if (nx < ox && ny > oy) {
				for (int i = oy, j = ox; i < ny || j > nx; i++, j--)
					if (board[i][j] == 0)
						good = 1;
					else if (board[i][j] != 0) {
						good = 0;
						break;
					}
			}
		}
		if (ox - nx == oy - ny) {
			if (nx < ox&& ny < oy) {
				for (int i = oy, j = ox; i > ny || j > nx; i--, j--)
					if (board[i][j] == 0)
						good = 1;
					else if (board[i][j] != 0) {
						good = 0;
						break;
					}
			}
		}

		//----------------------

		if (good == 1) {
			if (board[ny][nx] == 0) {
				good = 1;
			}
			else if ((status.whose_move == WHITE && board[ny][nx] > 0) ||
				(status.whose_move == BLACK && board[ny][nx] < 0)) {
				good = 1;
				status.attak = 1;
				status.p_attak.x = status.p_new.x;
				status.p_attak.y = status.p_new.y;
			}
			else
				good = 0;
		}

		if (good == 1) {
			status.ok = 1;
		}
		end = 1;
		//return status;
	}
	if (Figure == figs.Queen && end == 0) {
		int good = 0;
		int ox = status.p_old.x;
		int oy = status.p_old.y;
		int nx = status.p_new.x;
		int ny = status.p_new.y;

		//Определение направления движения
		int start = -1, stop = -1;
		int stand = -1;//0-x,1-y
		int left_or_right = -1;
		if (status.p_old.x == status.p_new.x &&
			status.p_old.y != status.p_new.y ||
			status.p_old.x != status.p_new.x &&
			status.p_old.y == status.p_new.y) {
			//rook
			if (status.p_old.x == status.p_new.x) {
				stand = 0;
				start = status.p_old.y;
				stop = status.p_new.y;
				if (status.p_old.y < status.p_new.y) {
					left_or_right = 1;
				}
				else if (status.p_old.y > status.p_new.y) {
					left_or_right = 0;
				}
			}
			else if (status.p_old.y == status.p_new.y) {
				stand = 1;
				start = status.p_old.x;
				stop = status.p_new.x;
				if (status.p_old.x < status.p_new.x) {
					left_or_right = 1;
				}
				else if (status.p_old.x > status.p_new.x) {
					left_or_right = 0;
				}
			}

			//Проверяем пусто ли на его пути
			int good = 1;
			if (left_or_right == 1) {
				for (int i = start; i < stop; i++) {
					if (((stand == 0) ? board[i][status.p_old.x] : board[status.p_old.y][i]) != 0 &&
						(i < stop)) {
						good = 0;
						break;
					}
				}
			}
			else if (left_or_right == 0) {
				for (int i = start - 1; i > stop; i--) {
					if (((stand == 0) ? board[i][status.p_old.x] : board[status.p_old.y][i]) != 0 &&
						(i > stop)) {
						good = 0;
						break;
					}
				}
			}

			//Проверяем пусто ли в конечной точки или же там находится фигура которую можно съесть
			if (good == 1) {
				if (((stand == 0) ? board[stop][status.p_old.x] : board[status.p_old.y][stop]) == 0)
					good = 1;
				else if (((stand == 0) ? board[stop][status.p_old.x] : board[status.p_old.y][stop]) > 0 &&
					status.whose_move == WHITE ||
					((stand == 0) ? board[stop][status.p_old.x] : board[status.p_old.y][stop]) < 0 &&
					status.whose_move == BLACK) {
					status.attak = 1;
					status.p_attak.x = status.p_new.x;
					status.p_attak.y = status.p_new.y;
					good = 1;
				}
				else
					good = 0;
			}
			if (good == 1) {
				status.ok = 1;
			}
		}
		else {
			//bishop

			if (nx - ox == ny - oy) {
				if (nx > ox && ny > oy) {
					for (int i = oy, j = ox; i < ny || j < nx; i++, j++)
						if (board[i][j] == 0)
							good = 1;
						else if (board[i][j] != 0) {
							good = 0;
							break;
						}
				}
			}
			if (nx - ox == oy - ny) {
				if (nx > ox && ny < oy) {
					for (int i = oy, j = ox; i > ny || j < nx; i--, j++)
						if (board[i][j] == 0)
							good = 1;
						else if (board[i][j] != 0) {
							good = 0;
							break;
						}
				}
			}
			if (ox - nx == ny - oy) {
				if (nx < ox && ny > oy) {
					for (int i = oy, j = ox; i < ny || j > nx; i++, j--)
						if (board[i][j] == 0)
							good = 1;
						else if (board[i][j] != 0) {
							good = 0;
							break;
						}
				}
			}
			if (ox - nx == oy - ny) {
				if (nx < ox&& ny < oy) {
					for (int i = oy, j = ox; i > ny || j > nx; i--, j--)
						if (board[i][j] == 0)
							good = 1;
						else if (board[i][j] != 0) {
							good = 0;
							break;
						}
				}
			}


			//----------------------

			if (good == 1) {
				if (board[ny][nx] == 0) {
					good = 1;
				}
				else if ((status.whose_move == WHITE && board[ny][nx] > 0) ||
					(status.whose_move == BLACK && board[ny][nx] < 0)) {
					good = 1;
					status.attak = 1;
					status.p_attak.x = status.p_new.x;
					status.p_attak.y = status.p_new.y;
				}
				else
					good = 0;
			}

			if (good == 1) {
				status.ok = 1;
			}
		}


		//----------------------


		end = 1;
		//return status;
	}
	if (Figure == figs.Knight && end == 0) {
		int good = 0;
		int ox = status.p_old.x;
		int oy = status.p_old.y;
		int nx = status.p_new.x;
		int ny = status.p_new.y;
		if (oy - 2 >= 0 && ox - 1 >= 0 && ny == oy - 2 && nx == ox - 1) {
			good = 1; 
		}
		if (oy - 2 >= 0 && ox + 1 < LENGTH && ny == oy - 2 && nx == ox + 1) {
			good = 1; 
		}
		if (oy - 1 >= 0 && ox + 2 < LENGTH && ny == oy - 1 && nx == ox + 2) {
			good = 1; 
		}
		if (oy + 1 >= 0 && ox + 2 < LENGTH && ny == oy + 1 && nx == ox + 2) {
			good = 1; 
		}
		if (oy + 2 < LENGTH && ox + 1 < LENGTH && ny == oy + 2 && nx == ox + 1) {
			good = 1; 
		}
		if (oy + 2 < LENGTH && ox - 1 >= 0 && ny == oy + 2 && nx == ox - 1) {
			good = 1; 
		}
		if (oy + 1 < LENGTH && ox - 2 >= 0 && ny == oy + 1 && nx == ox - 2) {
			good = 1; 
		}
		if (oy - 1 >= 0 && ox - 2 >= 0 && ny == oy - 1 && nx == ox - 2) {
			good = 1;
		}

		if (good == 1) {
			if (board[ny][nx] == 0) {
				good = 1;
			}
			else if ((status.whose_move == WHITE && board[ny][nx] > 0) ||
				(status.whose_move == BLACK && board[ny][nx] < 0)) {
				good = 1;
				status.attak = 1;
				status.p_attak.x = status.p_new.x;
				status.p_attak.y = status.p_new.y;
			}
			else
				good = 0;
		}

		if (good == 1) {
			status.ok = 1;
		}

		end = 1;
		//return status;
	}
	if (Figure == figs.King && end == 0) {
		//white

		int ox = status.p_old.x,
			oy = status.p_old.y,
			nx = status.p_new.x,
			ny = status.p_new.y,
			in_board = board[status.p_new.y][status.p_new.x];
		int good = 0;


		if (ox - 1 == nx &&
			oy - 1 == ny) {
			good = 1;
		}
		if (ox - 1 == nx &&
			oy == ny) {
			good = 1;
		}
		if (ox - 1 == nx &&
			oy + 1 == ny) {
			good = 1;
		}
		if (ox == nx &&
			oy + 1 == ny) {
			good = 1;
		}

		if (ox + 1 == nx &&
			oy + 1 == ny) {
			good = 1;
		}
		if (ox + 1 == nx &&
			oy == ny) {
			good = 1;
		}
		if (ox + 1 == nx &&
			oy - 1 == ny) {
			good = 1;
		}
		if (ox == nx &&
			oy - 1 == ny) {
			good = 1;
		}


		int curent_vec = (status.whose_move == WHITE) ? 7 : 0;
		if (board[curent_vec][5] == 0 &&
			board[curent_vec][6] == 0 &&
			ny == curent_vec && nx == 6) {
			if (KingsMove[status.whose_move] == 0 && RooksMove[status.whose_move][1] == 0)
				good = 1;
		}
		
		if (board[curent_vec][3] == 0 &&
			board[curent_vec][2] == 0 &&
			board[curent_vec][1] == 0 &&
			ny == curent_vec && nx == 2) {
			if (KingsMove[status.whose_move] == 0 && RooksMove[status.whose_move][0] == 0)
				good = 1;
		}
		
		if (good == 1) {
			if (in_board == 0)
				good = 1;
			else if (in_board > 0 && status.whose_move == WHITE ||
				in_board < 0 && status.whose_move == BLACK) {
				status.attak = 1;
				status.p_attak.x = status.p_new.x;
				status.p_attak.y = status.p_new.y;
				good = 1;
			}
			else {
				good = 0;
			}
		}

		if (good == 1)
			if (status.p_old.x == 4 && (status.p_old.y == 0 ||
				status.p_old.y == 7))
				if (KingsMove[status.whose_move] == 0)
					KingsMove[status.whose_move] = 1;

		if (good == 1) {
			status.ok = 1;
			//int ok = WhiteKingCheck(ox - 1, oy - 1);
		}
		end = 1;
		//return status;
	}

	/*
	WIK p_kings=where_is_kings(board);
	std::cout << "b_king[" << wik.b_king.x << "][" << wik.b_king.y << "]" << std::endl;
	std::cout << "w_king[" << wik.w_king.x << "][" << wik.w_king.y << "]" << std::endl;
	*/
	if (end == 0)
		status.ok = 0;
	//return status;
}


POS find_pos_king(int whose_move, int board[8][8]) {
	POS p;
	for (int i = 0; i < LENGTH; i++) {
		for (int j = 0; j < LENGTH; j++) {
			if (board[i][j] == figs.King * whose_move) {
				p.x = j;
				p.y = i;
				break;
			}
		}
	}
	return p;
}


int KingCheck(int whose_move, POS p_king, int Board[8][8]) {
	int ret = 0;
	STATUS check;
	check.fig = 0;

	for (int i = 0; i < LENGTH; i++) {
		for (int j = 0; j < LENGTH; j++) {
			if (Board[i][j] != 0) {
				if (Board[i][j] == figs.Pawn * whose_move) {
					check.fig = figs.Pawn;
					check.figNum = figs.Pawn * whose_move;
				}
				if (Board[i][j] == figs.Rook * whose_move) {
					check.fig = figs.Rook;
					check.figNum = figs.Rook * whose_move;
				}
				if (Board[i][j] == figs.Knight * whose_move) {
					check.fig = figs.Knight;
					check.figNum = figs.Knight * whose_move;
				}
				if (Board[i][j] == figs.Bishop * whose_move) {
					check.fig = figs.Bishop;
					check.figNum = figs.Bishop * whose_move;
				}
				if (Board[i][j] == figs.Queen * whose_move) {
					check.fig = figs.Queen;
					check.figNum = figs.Queen * whose_move;
				}
				if (Board[i][j] == figs.King * whose_move) {
					check.fig = figs.King;
					check.figNum = figs.King * whose_move;
				}
				if (check.fig != 0) {
					check.p_old.x = j;
					check.p_old.y = i;
					check.p_new.x = p_king.x;
					check.p_new.y = p_king.y;
					check.whose_move = whose_move;
					int saveF = Board[i][j];
					Board[i][j] = 0;
					Chess_move(check, Board);
					ret += check.ok;
					check.fig = 0;
					Board[i][j] = saveF;
				}
			}
		}
	}
	return ret;

}

int check_mat(int whose_move, POS p_king, int brd[8][8]) {
	STATUS check;
	check.fig = 0;
	int end = 1;

	for (int i = 0; i < LENGTH; i++) {
		for (int j = 0; j < LENGTH; j++) {
			if (brd[i][j] != 0 && end == 1) {
				if (brd[i][j] == figs.Pawn * whose_move) {
					check.fig = figs.Pawn;
					check.figNum = figs.Pawn * whose_move;
				}
				else if (brd[i][j] == figs.Rook * whose_move) {
					check.fig = figs.Rook;
					check.figNum = figs.Rook * whose_move;
				}
				else if (brd[i][j] == figs.Knight * whose_move) {
					check.fig = figs.Knight;
					check.figNum = figs.Knight * whose_move;
				}
				else if (brd[i][j] == figs.Bishop * whose_move) {
					check.fig = figs.Bishop;
					check.figNum = figs.Bishop * whose_move;
				}
				else if (brd[i][j] == figs.Queen * whose_move) {
					check.fig = figs.Queen;
					check.figNum = figs.Queen * whose_move;
				}
				else if (brd[i][j] == figs.King * whose_move) {
					check.fig = figs.King;
					check.figNum = figs.King * whose_move;
				}
				if (check.fig != 0) {
					for (int i1 = 0; i1 < LENGTH; i1++)
						for (int j1 = 0; j1 < LENGTH; j1++) {
							check.p_old.x = j;
							check.p_old.y = i;
							check.p_new.x = j1;
							check.p_new.y = i1;
							//check.whose_move = (whose_move == WHITE) ? BLACK : WHITE;
							check.whose_move = whose_move;

							Chess_move(check, brd);

							if (check.ok == 1) {
								//std::cout << "ok" << std::endl;

								int saveF_old = 0;
								int saveF_new = 0;
								saveF_old = brd[i][j];
								saveF_new = brd[i1][j1];
								brd[i][j] = 0;
								brd[i1][j1] = saveF_old;

								POS p_king2 = find_pos_king(whose_move, brd);
								int shah_check = KingCheck((whose_move == WHITE) ? BLACK : WHITE, p_king2, brd);

								brd[i][j] = saveF_old;
								brd[i1][j1] = saveF_new;
								//std::cout << "shah_check " << shah_check << std::endl;

								if (shah_check == 0) {
									return 0;
									//end = 0;
									//break;
								}
								/*
								//POS p_king = find_pos_king(whose_move, brd);
								int shahh = KingCheck(whose_move, p_king, brd);
								if (shah != 0) {
									std::cout << "find" << std::endl;
									ret = 1;
									break;
								}
								*/
							}
						}
					check.fig = 0;
				}
			}
		}
	}
	return 1;

}

//--------------

struct Auth my_auth;
//Функция инициализации начальных параметров

std::string user1 = "user1:", user2 = "user2:", name_user1 = "", name_user2 = "";
std::string s_exp = "exp:", s_exp_user1 = "", s_exp_user2 = "";
std::string s_about = "[--------------------]";
void inicialise() {


	figs.Pawn = 1;
	figs.Rook = 2;
	figs.Knight = 3;
	figs.Bishop = 4;
	figs.Queen = 5;
	figs.King = 6;
	status.whose_move = WHITE;

	std::string s = my_auth.Login;

	std::string answer = "";
	std::vector<string> ans;

	name_user1 = my_auth.Login;
	name_user2 = my_auth.Login_user2;
	
	answer = new_cmd(my_auth.ip, my_auth.port, "0000000|statistic_u|" + my_auth.Login + "|" + my_auth.Password + "|" + my_auth.Login);
	ans = split(answer, "-");
	//std::cout << "ans1:" << ans[0] << "\n";
	ans = split(ans[0], "=");
	//std::cout << "ans2:" << ans[0] << "\n";
	s_exp_user1 = ans[0];
	answer = new_cmd(my_auth.ip, my_auth.port, "0000000|statistic_u|" + my_auth.Login + "|" + my_auth.Password + "|" + my_auth.Login_user2);
	//Парсинг 
	//std::cout << "answer:" << answer << "\n";
	ans = split(answer, "-");
	//std::cout << "ans1:" << ans[0] << "\n";
	ans = split(ans[0], "=");
	//std::cout << "ans2:" << ans[0] << "\n";
	s_exp_user2 = ans[0];
	//Получить общий пароль игровой сессии
	answer = new_cmd(my_auth.ip, my_auth.port, "0000000|room_pass|" + my_auth.Login + "|" + my_auth.Password + "|" + my_auth.name_server);
	//Парсинг 
	//std::cout << "answer:" << answer << "\n";
	ans = split(answer, "-");
	//std::cout << "ans1:" << ans[0] << "\n";
	ans = split(ans[0], "=");
	//std::cout << "ans2:" << ans[0] << "\n";
	my_auth.room_password = ans[0];

	//Установкаа того кто ходит
	//Если сервер то белый автоматом
	if (my_auth.whomai == -1)
		my_auth.whomai = WHITE;
	else
		my_auth.whomai = BLACK;

	status.whose_move = WHITE;

}
struct Auth Game_single(RenderWindow& window, struct Auth ath) {
	my_auth = ath;

	inicialise();

	int board_init[LENGTH][LENGTH] =
	{ 2, 3, 4, 5, 6, 4, 3, 2,
	  1, 1, 1, 1, 1, 1, 1, 1,
	  0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0,
	 -1,-1,-1,-1,-1,-1,-1,-1,
	 -2,-3,-4,-5,-6,-4,-3,-2,
	};
	int board2[LENGTH][LENGTH] =
	{ 0, 0, 0, 1, 6, 1, 0, 0,
	  0, 0, 0, 1, 0, 1, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, -5, 0, 0,
	  0, 0, 0, 0, -6, 0, 0, 0,
	};
	for (int i = 0; i < LENGTH; i++)
		for (int j = 0; j < LENGTH; j++)
			board[i][j] = board_init[i][j];

	//icon и шрифт
	//-----------
	//Setting icon
	sf::Image WindowIcon;
	if (!WindowIcon.loadFromFile("files/icon.png"))
		std::cout << "cant load texture from file " << std::endl;
	else
		window.setIcon(128, 128, WindowIcon.getPixelsPtr());
	//-----------
	//Шрифт
	sf::Font font;
	sf::Font& refFont = font;
	if (!font.loadFromFile("files/normal.otf")) {
		std::cout << "cant load font" << std::endl;
	}
	//-----------
	//Инициализация текстур
	Texture Textr_Board,
		Textr_W_Pawn_Transf, Textr_B_Pawn_Transf,
		Textr_W_Pawn, Textr_B_Pawn,
		Textr_W_Rook, Textr_B_Rook,
		Textr_W_Knight, Textr_B_Knight,
		Textr_W_Bishop, Textr_B_Bishop,
		Textr_W_Queen, Textr_B_Queen,
		Textr_W_King, Textr_B_King;

	Textr_Board.loadFromFile("files/Board.png");
	Textr_B_Pawn_Transf.loadFromFile("files/TransformationBlack.png");
	Textr_W_Pawn_Transf.loadFromFile("files/TransformationWhite.png");
	Textr_B_Pawn.loadFromFile("files/BlackPawn.png");
	Textr_W_Pawn.loadFromFile("files/WhitePawn.png");
	Textr_B_Rook.loadFromFile("files/BlackRook.png");
	Textr_W_Rook.loadFromFile("files/WhiteRook.png");
	Textr_B_Knight.loadFromFile("files/BlackKnight.png");
	Textr_W_Knight.loadFromFile("files/WhiteKnight.png");
	Textr_B_Bishop.loadFromFile("files/BlackBishop.png");
	Textr_W_Bishop.loadFromFile("files/WhiteBishop.png");
	Textr_B_Queen.loadFromFile("files/BlackQueen.png");
	Textr_W_Queen.loadFromFile("files/WhiteQueen.png");
	Textr_B_King.loadFromFile("files/BlackKing.png");
	Textr_W_King.loadFromFile("files/WhiteKing.png");

	Sprite Board(Textr_Board);
	Sprite B_Pawn_Transf(Textr_B_Pawn_Transf);
	Sprite W_Pawn_Transf(Textr_W_Pawn_Transf);
	Sprite B_Pawn(Textr_B_Pawn);
	Sprite W_Pawn(Textr_W_Pawn);
	Sprite B_Rook(Textr_B_Rook);
	Sprite W_Rook(Textr_W_Rook);
	Sprite B_Knight(Textr_B_Knight);
	Sprite W_Knight(Textr_W_Knight);
	Sprite B_Bishop(Textr_B_Bishop);
	Sprite W_Bishop(Textr_W_Bishop);
	Sprite B_Queen(Textr_B_Queen);
	Sprite W_Queen(Textr_W_Queen);
	Sprite B_King(Textr_B_King);
	Sprite W_King(Textr_W_King);
	Sprite MoveImages;

	float dx = 0, dy = 0;
	int CurrentFigureNum = 0;
	int x_start = 50;
	int y_start = 50;

	int end_game = 0;
	int Click = 0;
	int FigSave = 0;
	int shag = status.whose_move;
	int whose_move_save = status.whose_move;
	string board_str = "";
	sf::Clock clock_shag;
	sf::Clock clock_listen;

	sf::Text TextBox_name_user1(name_user1, font, 18);
	sf::Text TextBox_name_user2(name_user2, font, 18);
	sf::Text TextBox_s_exp_user1(s_exp_user1, font, 18);
	sf::Text TextBox_s_exp_user2(s_exp_user2, font, 18);
	sf::Text TextBox_s_about(s_about, font, 18);
	TextBox_name_user1.setFillColor(sf::Color::White);
	TextBox_name_user2.setFillColor(sf::Color::White);
	TextBox_s_exp_user1.setFillColor(sf::Color::White);
	TextBox_s_exp_user2.setFillColor(sf::Color::White);
	TextBox_s_about.setFillColor(sf::Color::White);
	TextBox_name_user1.setStyle(sf::Text::Bold | sf::Text::Underlined);
	TextBox_name_user2.setStyle(sf::Text::Bold | sf::Text::Underlined);
	TextBox_s_exp_user1.setStyle(sf::Text::Bold | sf::Text::Underlined);
	TextBox_s_exp_user2.setStyle(sf::Text::Bold | sf::Text::Underlined);
	TextBox_s_about.setStyle(sf::Text::Bold | sf::Text::Underlined);
	TextBox_name_user1.setPosition(920, 25);
	TextBox_name_user2.setPosition(1050, 25);
	TextBox_s_exp_user1.setPosition(920, 64);
	TextBox_s_exp_user2.setPosition(1050, 64);
	TextBox_s_about.setPosition(950, 100);

	sf::Texture Texture_ready;
	Texture_ready.loadFromFile("files/ready.png");
	Sprite menu_ready(Texture_ready);
	menu_ready.setPosition(1000, 130);

	
	Event e;
	sf::Clock clock;
	sf::Time time1, time2;
	time1 = clock.getElapsedTime();
	my_auth.who_win = 0;

	int clk = 0;

	while (window.isOpen() && end_game == 0) {

		if (clk == 1 && clock.getElapsedTime().asSeconds() * 1000 - time1.asSeconds() * 1000 > 1) {

			system("cls");
			std::cout << "Cursor:[" << p_cur.x << "|" << p_cur.y << "]" << std::endl;
			std::cout << "xy:[" << x << "|" << y << "]" << std::endl;
			std::cout << std::endl;
			std::cout << "move=" << move << std::endl;
			std::cout << std::endl;
			std::cout << "status.whose_move=" << status.whose_move << std::endl;
			std::cout << std::endl;

			std::cout << "STATUS:" << std::endl;
			std::cout << "    ok=" << status.ok << std::endl;
			std::cout << "    attak=" << status.attak << std::endl;
			std::cout << "    whose_move=" << status.whose_move << std::endl;
			std::cout << "    fig=" << status.fig << std::endl;
			std::cout << "    figNum=" << status.figNum << std::endl;
			std::cout << "    p_old=[" << status.p_old.x << "|" << status.p_old.y << "]" << std::endl;
			std::cout << "    p_new=[" << status.p_new.x << "|" << status.p_new.y << "]" << std::endl;
			std::cout << "    p_attak=[" << status.p_attak.x << "|" << status.p_attak.y << "]" << std::endl;

			std::cout << "PawnsJump:" << std::endl;
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < LENGTH; j++) {
					std::cout << PawnsJump[i][j] << " ";
				}
				std::cout << std::endl;
			}

			std::cout << "RooksMove:" << std::endl;
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < 2; j++) {
					std::cout << RooksMove[i][j] << " ";
				}
				std::cout << std::endl;
			}

			std::cout << "KingsMove:" << std::endl;
			for (int j = 0; j < 2; j++) {
				std::cout << KingsMove[j] << " ";
			}

			std::cout << std::endl;
			POS p_king = find_pos_king((status.whose_move == 1) ? -1 : 1, board);
			std::cout << "p_king:[" << p_king.x << "|" << p_king.y << "]" << std::endl;
			int sss = KingCheck((status.whose_move == 1) ? -1 : 1, p_king, board);
			std::cout << "KingCheck:" << sss << std::endl;

			time1 = clock.getElapsedTime();
		}

		
		Vector2i pos = Mouse::getPosition(window);
		p_cur.x = pos.x - 50;
		p_cur.y = pos.y - 50;

		pos.y -= 50;
		pos.x -= 50;
		x = p_cur.x / size;
		y = p_cur.y / size;
		x = (x < 0) ? 0 : ((x > 7) ? 7 : x);
		y = (y < 0) ? 0 : ((y > 7) ? 7 : y);

		while (window.pollEvent(e)) {

			if (e.type == Event::Closed) {
				end_game = 1;
				window.close();

			}
			window.clear();
			if (e.type == Event::MouseButtonPressed) {
				std::cout << "x=" << sf::Mouse::getPosition(window).x << std::endl;
				std::cout << "y=" << sf::Mouse::getPosition(window).y << std::endl;
				if (e.key.code == Mouse::Left) {//&& Click==0) {//Левой
					Click = 1;

					if (board[y][x] != 0 && transformation == 0) {
						dx = p_cur.x - x * 100;
						dy = p_cur.y - y * 100;

						//status.whose_move=1 - BLAC
						//status.whose_move=-1 - WHITE
						if (board[y][x] == figs.Pawn * status.whose_move) {
							status.fig = figs.Pawn;
							status.figNum = figs.Pawn * status.whose_move;
							FigSave = status.figNum;
							status.p_old.x = x;
							status.p_old.y = y;
							status.p_new.x = x;
							status.p_new.y = y;
							MoveImages = (status.whose_move == WHITE) ? W_Pawn : B_Pawn;
							board[y][x] = 0;
							move = 1;
						}
						if (board[y][x] == figs.Rook * status.whose_move) {

							status.fig = figs.Rook;
							status.figNum = figs.Rook * status.whose_move;
							FigSave = status.figNum;
							status.p_old.x = x;
							status.p_old.y = y;
							status.p_new.x = x;
							status.p_new.y = y;
							MoveImages = (status.whose_move == WHITE) ? W_Rook : B_Rook;
							board[y][x] = 0;
							move = 1;
						}
						if (board[y][x] == figs.King * status.whose_move) {
							status.fig = figs.King;
							status.figNum = figs.King * status.whose_move;
							FigSave = status.figNum;
							status.p_old.x = x;
							status.p_old.y = y;
							status.p_new.x = x;
							status.p_new.y = y;
							MoveImages = (status.whose_move == WHITE) ? W_King : B_King;
							board[y][x] = 0;
							move = 1;
						}
						if (board[y][x] == figs.Knight * status.whose_move) {
							status.fig = figs.Knight;
							status.figNum = figs.Knight * status.whose_move;
							FigSave = status.figNum;
							status.p_old.x = x;
							status.p_old.y = y;
							status.p_new.x = x;
							status.p_new.y = y;
							MoveImages = (status.whose_move == WHITE) ? W_Knight : B_Knight;
							board[y][x] = 0;
							move = 1;
						}
						if (board[y][x] == figs.Bishop * status.whose_move) {
							status.fig = figs.Bishop;
							status.figNum = figs.Bishop * status.whose_move;
							FigSave = status.figNum;
							status.p_old.x = x;
							status.p_old.y = y;
							status.p_new.x = x;
							status.p_new.y = y;
							MoveImages = (status.whose_move == WHITE) ? W_Bishop : B_Bishop;
							board[y][x] = 0;
							move = 1;
						}
						if (board[y][x] == figs.Queen * status.whose_move) {
							status.fig = figs.Queen;
							status.figNum = figs.Queen * status.whose_move;
							FigSave = status.figNum;
							status.p_old.x = x;
							status.p_old.y = y;
							status.p_new.x = x;
							status.p_new.y = y;
							MoveImages = (status.whose_move == WHITE) ? W_Queen : B_Queen;
							board[y][x] = 0;
							move = 1;
						}
					}
				}
			}
			if (e.type == Event::MouseButtonReleased) {
				if (e.key.code == Mouse::Left) {
					Click = 0;

					//Перемещаем фигуру?
					if (move == 1 && transformation == 0) {
						status.p_new.x = x;
						status.p_new.y = y;
						if (status.p_new.x != status.p_old.x || status.p_new.y != status.p_old.y) {//То если новые координаты отличаются от старых
							Chess_move(status, board);
							//good = KingCheck(figs.King, status.whose_move, status.p_old, status.p_new, board);
							//std::cout << good << std::endl;

							if (status.ok == 1) {
								int saveF_old = 0;
								int saveF_new = 0;
								saveF_old = status.figNum;
								saveF_new = board[status.p_new.y][status.p_new.x];
								board[status.p_old.y][status.p_old.x] = 0;
								board[status.p_new.y][status.p_new.x] = saveF_old;

								POS p_king = find_pos_king(status.whose_move, board);
								int attack = (status.whose_move == WHITE) ? BLACK : WHITE;
								shah = KingCheck(attack, p_king, board);

								board[status.p_old.y][status.p_old.x] = saveF_old;
								board[status.p_new.y][status.p_new.x] = saveF_new;
								if (shah != 0) {
									status.ok = 0;
								}

							}

							if (status.ok == 1) {
								if (y == 0 && status.figNum == -666 || y == 7 && status.figNum == 666) {
									transformation = 1;
									t_transform.x = status.p_new.x;
									t_transform.y = status.p_new.y;
									status.ok = 2;
									board[status.p_new.y][status.p_new.x] = 0;
								}
							}
							
							if (status.ok == 1) {
								if (status.fig == figs.King &&
									abs(status.p_old.x - status.p_new.x) > 1) {
									board[status.p_old.y][status.p_old.x] = 0;
									board[status.p_new.y][status.p_new.x] = status.figNum;
									int left_or_right = (status.p_new.x > status.p_old.x) ? 7 : 0;
									board[status.p_old.y][left_or_right] = 0;
									board[status.p_old.y][(left_or_right == 7) ? 5 : 3] = figs.Rook * status.whose_move;
								}
							}

							if (status.ok == 1) {
								board[status.p_old.y][status.p_old.x] = 0;
								int who = 0;
								if (status.attak == 1) {
									who = board[status.p_attak.y][status.p_attak.x];
									board[status.p_attak.y][status.p_attak.x] = 0;
								}
								board[status.p_new.y][status.p_new.x] = status.figNum;
								shag = (shag == -1) ? 1 : -1;
							}
							else if (status.ok == 0) {
								board[status.p_old.y][status.p_old.x] = FigSave;
							}
						}
						else {
							board[status.p_old.y][status.p_old.x] = FigSave;
						}
						move = 0;
					}
					else if (transformation == 1) {
						int x1, y1, good = 0;
						x1 = (p_cur.x - status.p_new.x * size);
						y1 = (p_cur.y - status.p_new.y * size);
						/*
						std::cout << "______________" << std::endl;
						std::cout << "Cursor:[" << p_cur.x << "|" << p_cur.y << "]" << std::endl;
						std::cout << "xy:[" << x1 << "|" << y1 << "]" << std::endl;
						std::cout << "xy/2:[" << x/2 << "|" << y1/2 << "]" << std::endl;
						std::cout << "--------------" << std::endl;
						*/
						if (0 < x1 && x1 < 50 && 0 < y1 && y1 < 50) {
							//std::cout << 2 << std::endl;
							status.figNum = figs.Rook * status.whose_move;
							board[t_transform.y][t_transform.x] = status.figNum;
							good = 1;
						}
						else if (size > x1 && x1 > 50 && 0 < y1 && y1 < 50) {
							//std::cout << 5 << std::endl;
							status.figNum = figs.Queen * status.whose_move;
							board[t_transform.y][t_transform.x] = status.figNum;
							good = 1;
						}
						else if (0 < x1 && x1 < 50 && size>y1 && y1 > 50) {
							//std::cout << 4 << std::endl;
							status.figNum = figs.Bishop * status.whose_move;
							board[t_transform.y][t_transform.x] = status.figNum;
							good = 1;
						}
						else if (size > x1 && x1 > 50 && size > y1 && y1 > 50) {
							//std::cout << 3 << std::endl;
							status.figNum = figs.Knight * status.whose_move;
							board[t_transform.y][t_transform.x] = status.figNum;
							good = 1;
						}
						if (good == 1) {
							transformation = 0;
							board[status.p_old.y][status.p_old.x] = 0;
							board[status.p_new.y][status.p_new.x] = status.figNum;
							status.ok = 1;
							shag = (shag == -1) ? 1 : -1;
						}
					}
					if (status.ok == 1) {
						int attack = (status.whose_move == WHITE) ? BLACK : WHITE;
						POS p_king = find_pos_king(attack, board);
						shah = KingCheck(status.whose_move, p_king, board);
						std::cout << "shah:" << shah << std::endl;
						if (shah != 0) {
							POS p_king = find_pos_king(attack, board);
							mat = check_mat(attack, p_king, board);
							std::cout << "mat:" << mat << std::endl;
							if (mat != 0) {
								std::cout << "end_game:" << std::endl;
								end_game = 1;
								my_auth.who_win = status.whose_move;
								std::cout << "win:" << (my_auth.who_win == WHITE) ? "WHITE\n" : "BLACK\n";
							}
						}
					}
				}
				if (status.whose_move != shag) {
					board_str = ".";
					for (int i = 0; i < LENGTH; i++) {
						for (int j = 0; j < LENGTH; j++)
							board_str += std::to_string(board[i][j]) + ",";
						board_str[board_str.length() - 1] = '.';
					}
					clock_shag.restart();
				}
			}
			status.whose_move = shag;
		}



		window.clear();
		window.draw(Board);
		if (transformation == 1) {
			if (status.figNum == -666) {
				W_Pawn_Transf.setPosition(t_transform.x * size + x_start, t_transform.y * size + y_start);
				window.draw(W_Pawn_Transf);
			}
			else if (status.figNum == 666) {
				B_Pawn_Transf.setPosition(t_transform.x * size + x_start, t_transform.y * size + y_start);
				window.draw(B_Pawn_Transf);
			}
		}
		if (move == 1) {
			MoveImages.setPosition(p_cur.x - dx + 50, p_cur.y - dy + 50);
			window.draw(MoveImages);
		}
		for (int i = 0; i < LENGTH; i++) {
			for (int j = 0; j < LENGTH; j++) {
				if (board[i][j] != 0) {
					if (board[i][j] == figs.Pawn * BLACK) {
						B_Pawn.setPosition(j * size + x_start, i * size + y_start);
						window.draw(B_Pawn);
					}
					if (board[i][j] == figs.Pawn * WHITE) {
						W_Pawn.setPosition(j * size + x_start, i * size + y_start);
						window.draw(W_Pawn);
					}
					if (board[i][j] == figs.Rook * BLACK) {
						B_Rook.setPosition(j * size + x_start, i * size + y_start);
						window.draw(B_Rook);

					}
					if (board[i][j] == figs.Rook * WHITE) {
						W_Rook.setPosition(j * size + x_start, i * size + y_start);
						window.draw(W_Rook);

					}
					if (board[i][j] == figs.Knight * BLACK) {
						B_Knight.setPosition(j * size + x_start, i * size + y_start);
						window.draw(B_Knight);
					}
					if (board[i][j] == figs.Knight * WHITE) {
						W_Knight.setPosition(j * size + x_start, i * size + y_start);
						window.draw(W_Knight);
					}
					if (board[i][j] == figs.Bishop * BLACK) {
						B_Bishop.setPosition(j * size + x_start, i * size + y_start);
						window.draw(B_Bishop);
					}
					if (board[i][j] == figs.Bishop * WHITE) {
						W_Bishop.setPosition(j * size + x_start, i * size + y_start);
						window.draw(W_Bishop);
					}
					if (board[i][j] == figs.Queen * WHITE) {
						W_Queen.setPosition(j * size + x_start, i * size + y_start);
						window.draw(W_Queen);
					}
					if (board[i][j] == figs.Queen * BLACK) {
						B_Queen.setPosition(j * size + x_start, i * size + y_start);
						window.draw(B_Queen);
					}
					if (board[i][j] == figs.King * BLACK) {
						B_King.setPosition(j * size + x_start, i * size + y_start);
						window.draw(B_King);
					}
					if (board[i][j] == figs.King * WHITE) {
						W_King.setPosition(j * size + x_start, i * size + y_start);
						window.draw(W_King);
					}
				}
			}
		}


		TextBox_name_user1.setString(user1 + name_user1);
		TextBox_name_user2.setString(user2 + name_user2);
		TextBox_s_exp_user1.setString(s_exp + s_exp_user1);
		TextBox_s_exp_user2.setString(s_exp + s_exp_user2);
		TextBox_s_about.setString(s_about);
		window.draw(TextBox_name_user1);
		window.draw(TextBox_name_user2);
		window.draw(TextBox_s_exp_user1);
		window.draw(TextBox_s_exp_user2);
		window.draw(TextBox_s_about);
		window.draw(menu_ready);

		window.display();
	};
	return my_auth;

}
struct Auth Game(RenderWindow& window, struct Auth ath) {
	my_auth = ath;

	inicialise();

	int board_init[LENGTH][LENGTH] =
	{ 2, 3, 4, 5, 6, 4, 3, 2,
	  1, 1, 1, 1, 1, 1, 1, 1,
	  0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0,
	 -1,-1,-1,-1,-1,-1,-1,-1,
	 -2,-3,-4,-5,-6,-4,-3,-2,
	};
	int board2[LENGTH][LENGTH] =
	{ 0, 0, 0, 1, 6, 1, 0, 0,
	  0, 0, 0, 1, 0, 1, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, -5, 0, 0,
	  0, 0, 0, 0, -6, 0, 0, 0,
	};
	for (int i = 0; i < LENGTH; i++)
		for (int j = 0; j < LENGTH; j++)
			board[i][j] = board_init[i][j];

	
	sf::Image WindowIcon;
	if (!WindowIcon.loadFromFile("files/icon.png"))
		std::cout << "cant load texture from file " << std::endl;
	else
		window.setIcon(128, 128, WindowIcon.getPixelsPtr());
	sf::Font font;
	sf::Font& refFont = font;
	if (!font.loadFromFile("files/normal.otf")) {
		std::cout << "cant load font" << std::endl;
	}
	Texture Textr_Board,
		Textr_W_Pawn_Transf, Textr_B_Pawn_Transf,
		Textr_W_Pawn, Textr_B_Pawn,
		Textr_W_Rook, Textr_B_Rook,
		Textr_W_Knight, Textr_B_Knight,
		Textr_W_Bishop, Textr_B_Bishop,
		Textr_W_Queen, Textr_B_Queen,
		Textr_W_King, Textr_B_King;

	Textr_Board.loadFromFile("files/Board.png");
	Textr_B_Pawn_Transf.loadFromFile("files/TransformationBlack.png");
	Textr_W_Pawn_Transf.loadFromFile("files/TransformationWhite.png");
	Textr_B_Pawn.loadFromFile("files/BlackPawn.png");
	Textr_W_Pawn.loadFromFile("files/WhitePawn.png");
	Textr_B_Rook.loadFromFile("files/BlackRook.png");
	Textr_W_Rook.loadFromFile("files/WhiteRook.png");
	Textr_B_Knight.loadFromFile("files/BlackKnight.png");
	Textr_W_Knight.loadFromFile("files/WhiteKnight.png");
	Textr_B_Bishop.loadFromFile("files/BlackBishop.png");
	Textr_W_Bishop.loadFromFile("files/WhiteBishop.png");
	Textr_B_Queen.loadFromFile("files/BlackQueen.png");
	Textr_W_Queen.loadFromFile("files/WhiteQueen.png");
	Textr_B_King.loadFromFile("files/BlackKing.png");
	Textr_W_King.loadFromFile("files/WhiteKing.png");

	Sprite Board(Textr_Board);
	Sprite B_Pawn_Transf(Textr_B_Pawn_Transf);
	Sprite W_Pawn_Transf(Textr_W_Pawn_Transf);
	Sprite B_Pawn(Textr_B_Pawn);
	Sprite W_Pawn(Textr_W_Pawn);
	Sprite B_Rook(Textr_B_Rook);
	Sprite W_Rook(Textr_W_Rook);
	Sprite B_Knight(Textr_B_Knight);
	Sprite W_Knight(Textr_W_Knight);
	Sprite B_Bishop(Textr_B_Bishop);
	Sprite W_Bishop(Textr_W_Bishop);
	Sprite B_Queen(Textr_B_Queen);
	Sprite W_Queen(Textr_W_Queen);
	Sprite B_King(Textr_B_King);
	Sprite W_King(Textr_W_King);
	Sprite MoveImages;

	float dx = 0, dy = 0;
	int CurrentFigureNum = 0;
	int x_start = 50;
	int y_start = 50;

	int Click = 0;
	int FigSave = 0;
	int shag = status.whose_move;
	int whose_move_save = status.whose_move;
	string board_str = "";
	sf::Clock clock_shag;
	sf::Clock clock_listen;

	sf::Text TextBox_name_user1(name_user1, font, 18);
	sf::Text TextBox_name_user2(name_user2, font, 18);
	sf::Text TextBox_s_exp_user1(s_exp_user1, font, 18);
	sf::Text TextBox_s_exp_user2(s_exp_user2, font, 18);
	sf::Text TextBox_s_about(s_about, font, 18);
	TextBox_name_user1.setFillColor(sf::Color::White);
	TextBox_name_user2.setFillColor(sf::Color::White);
	TextBox_s_exp_user1.setFillColor(sf::Color::White);
	TextBox_s_exp_user2.setFillColor(sf::Color::White);
	TextBox_s_about.setFillColor(sf::Color::White);
	TextBox_name_user1.setStyle(sf::Text::Bold | sf::Text::Underlined);
	TextBox_name_user2.setStyle(sf::Text::Bold | sf::Text::Underlined);
	TextBox_s_exp_user1.setStyle(sf::Text::Bold | sf::Text::Underlined);
	TextBox_s_exp_user2.setStyle(sf::Text::Bold | sf::Text::Underlined);
	TextBox_s_about.setStyle(sf::Text::Bold | sf::Text::Underlined);
	TextBox_name_user1.setPosition(920, 25);
	TextBox_name_user2.setPosition(1070, 25);
	TextBox_s_exp_user1.setPosition(920, 64);
	TextBox_s_exp_user2.setPosition(1070, 64);
	TextBox_s_about.setPosition(950, 100);

	sf::Texture Texture_ready;
	Texture_ready.loadFromFile("files/ready.png");
	Sprite menu_ready(Texture_ready);

	menu_ready.setPosition(1000, 130);

	int end_game = 0;
	int vibor = 0;
	int left_release = 2;
	int exp_our = 0;
	int board_u2[LENGTH][LENGTH]; 
	int board_u1[LENGTH][LENGTH];
	int get_map = 0;
	int menuNum = 0;
	while (window.isOpen() && vibor == 0) {
		window.clear();
		menuNum = 0;

		
		Vector2i pos = Mouse::getPosition(window);
		p_cur.x = pos.x - 50;
		p_cur.y = pos.y - 50;

		pos.y -= 50;
		pos.x -= 50;
		
		x = p_cur.x / size;
		y = p_cur.y / size;
		x = (x < 0) ? 0 : ((x > 7) ? 7 : x);
		y = (y < 0) ? 0 : ((y > 7) ? 7 : y);
		Event ev1;
		while (window.pollEvent(ev1)) {
			switch (ev1.type) {
			case sf::Event::Closed:
				end_game = 1;
				vibor = 1;
				window.close();
				break;
			case Event::MouseButtonPressed:
				if (ev1.key.code == Mouse::Left) {
					std::cout << "x=" << sf::Mouse::getPosition(window).x << std::endl;
					std::cout << "y=" << sf::Mouse::getPosition(window).y << std::endl;
					Click = 1;
					left_release = 1;
				}
				break;
			case Event::MouseButtonReleased:
				if (ev1.key.code == Mouse::Left) {
					Click = 0;
					if (board[y][x] == figs.Pawn * my_auth.whomai && sf::Mouse::getPosition(window).x<850 && sf::Mouse::getPosition(window).y<850) {
						board[y][x] = 666 * my_auth.whomai;
						transformation = 1;
					}
					else if (transformation==1 && board[y][x] == 666 * my_auth.whomai) {
						int x1, y1, good = 0;
						x1 = (p_cur.x - x * size);
						y1 = (p_cur.y - y * size);
						exp_our = atoi(s_exp_user1.c_str());
						if (0 < x1 && x1 < 50 && 0 < y1 && y1 < 50) {
							if (exp_our >= 10) {
								board[y][x] = figs.Rook * my_auth.whomai;
								exp_our -= 10;
								good = 1;
							}
							else
								board[y][x] = figs.Pawn * my_auth.whomai;
						}
						else if (size > x1 && x1 > 50 && 0 < y1 && y1 < 50) {
							if (exp_our >= 30){
								board[y][x] = figs.Queen * my_auth.whomai;
								exp_our -= 30;
								good = 1;
							}
							else
								board[y][x] = figs.Pawn * my_auth.whomai;
						}
						else if (0 < x1 && x1 < 50 && size>y1 && y1 > 50) {
							if (exp_our >= 15){
								board[y][x] = figs.Bishop * my_auth.whomai;
								exp_our -= 15;
								good = 1;
							}
							else
								board[y][x] = figs.Pawn * my_auth.whomai;
						}
						else if (size > x1 && x1 > 50 && size > y1 && y1 > 50) {
							if (exp_our >= 10){
								board[y][x] = figs.Knight * my_auth.whomai;
								exp_our -= 10;
								good = 1;
							}
							else
								board[y][x] = figs.Pawn * my_auth.whomai;
						}
						if (good == 1) {
							s_exp_user1 = std::to_string(exp_our);
							transformation = 0;
						}
					}
					left_release = 0;
				
					if (IntRect(1022, 150, 50, 50).contains(Mouse::getPosition(window))) {
						menuNum = 1;
					}
					if (menuNum == 1) {
						vibor = 1;
						string answer = new_cmd(my_auth.ip, my_auth.port, "0000000|set_exp|" + my_auth.Login + "|" + my_auth.Password + "|" + my_auth.Login + "|" + s_exp_user1);
					}
				}

				break;
			}

		}
		


		window.clear();
		window.draw(Board);


		for (int i = 0; i < LENGTH; i++) {
			for (int j = 0; j < LENGTH; j++) {
				if (board[i][j] != 0) {
					if (board[i][j] == -666) {
						W_Pawn_Transf.setPosition(j * size + x_start, i * size + y_start);
						window.draw(W_Pawn_Transf);
					}
					else if (board[i][j] == 666) {
						B_Pawn_Transf.setPosition(j * size + x_start, i * size + y_start);
						window.draw(B_Pawn_Transf);
					}
					if (board[i][j] == figs.Pawn * BLACK) {
						B_Pawn.setPosition(j * size + x_start, i * size + y_start);
						window.draw(B_Pawn);
					}
					if (board[i][j] == figs.Pawn * WHITE) {
						W_Pawn.setPosition(j * size + x_start, i * size + y_start);
						window.draw(W_Pawn);
					}
					if (board[i][j] == figs.Rook * BLACK) {
						B_Rook.setPosition(j * size + x_start, i * size + y_start);
						window.draw(B_Rook);

					}
					if (board[i][j] == figs.Rook * WHITE) {
						W_Rook.setPosition(j * size + x_start, i * size + y_start);
						window.draw(W_Rook);

					}
					if (board[i][j] == figs.Knight * BLACK) {
						B_Knight.setPosition(j * size + x_start, i * size + y_start);
						window.draw(B_Knight);
					}
					if (board[i][j] == figs.Knight * WHITE) {
						W_Knight.setPosition(j * size + x_start, i * size + y_start);
						window.draw(W_Knight);
					}
					if (board[i][j] == figs.Bishop * BLACK) {
						B_Bishop.setPosition(j * size + x_start, i * size + y_start);
						window.draw(B_Bishop);
					}
					if (board[i][j] == figs.Bishop * WHITE) {
						W_Bishop.setPosition(j * size + x_start, i * size + y_start);
						window.draw(W_Bishop);
					}
					if (board[i][j] == figs.Queen * WHITE) {
						W_Queen.setPosition(j * size + x_start, i * size + y_start);
						window.draw(W_Queen);
					}
					if (board[i][j] == figs.Queen * BLACK) {
						B_Queen.setPosition(j * size + x_start, i * size + y_start);
						window.draw(B_Queen);
					}
					if (board[i][j] == figs.King * BLACK) {
						B_King.setPosition(j * size + x_start, i * size + y_start);
						window.draw(B_King);
					}
					if (board[i][j] == figs.King * WHITE) {
						W_King.setPosition(j * size + x_start, i * size + y_start);
						window.draw(W_King);
					}
				}
			}
		}


		TextBox_name_user1.setString(user1 + name_user1);
		TextBox_name_user2.setString(user2 + name_user2);
		TextBox_s_exp_user1.setString(s_exp + s_exp_user1);
		TextBox_s_exp_user2.setString(s_exp + s_exp_user2);
		TextBox_s_about.setString(s_about);
		window.draw(TextBox_name_user1);
		window.draw(TextBox_name_user2);
		window.draw(TextBox_s_exp_user1);
		window.draw(TextBox_s_exp_user2);
		window.draw(TextBox_s_about);
		window.draw(menu_ready);

		window.display();
	}

	inicialise();

	for (int q = 0; q < 2; q++) {
		if (my_auth.whomai == -1&& get_map==0|| my_auth.whomai == 1 && get_map == 1) {
			string ans = listen_cmd(my_auth.ip_my, my_auth.port_my, 0.2f);
			std::vector<string> answ;
			answ = split(ans, "=");
			if (answ[1] == my_auth.room_password && answ[2] == "1") {
				std::vector<string> rows, cells;
				rows = split(answ[3], ".");
				for (int i = 0; i < rows.size(); i++) {
					cells = split(rows[i], ",");
					for (int j = 0; j < cells.size(); j++) {
						int ss = atoi(cells[j].c_str());
						std::cout << ss << " ";
						board_u2[i][j] = ss;
					}
					std::cout << "\n";
				}
				get_map += 1;
			}
		}
		else if (my_auth.whomai == 1 && get_map == 0|| my_auth.whomai == -1 && get_map == 1) {
			string answer;
			board_str = ".";
			for (int i = 0; i < LENGTH; i++) {
				for (int j = 0; j < LENGTH; j++)
					board_str += std::to_string(board[i][j]) + ",";
				board_str[board_str.length() - 1] = '.';
			}
			string ans = "0";
			sf::Clock clock1, pause1;
			clock1.restart();
			while (ans == "0" && clock1.getElapsedTime().asSeconds() < 6) {
				if (pause1.getElapsedTime().asSeconds() >= 1) {
					answer = new_cmd(my_auth.ip_user2, my_auth.port_user2, "=" + my_auth.room_password + "=1=" + board_str + "=");
					std::vector<string> cou;
					cou = split(answer, "-");
					ans = cou[0];
					pause1.restart();
				}
			}
			if (ans == "1") {
				get_map += 1;
			}
		}
		if (get_map == 1 && my_auth.whomai == -1) {
			for (int i = 0; i < 2; i++)
				for (int j = 0; j < LENGTH; j++)
					board[i][j] = board_u2[i][j];
		}
		if (get_map == 2 && my_auth.whomai == 1) {
			for (int i = LENGTH-1; i >5; i--)
				for (int j = 0; j < LENGTH; j++)
					board[i][j] = board_u2[i][j];
		}
	}


	status.whose_move = WHITE;

	Event e;
	sf::Clock clock;
	sf::Time time1, time2;
	time1 = clock.getElapsedTime();
	my_auth.who_win = 0;
	int first_send = 1;
	int clk = 2;
	int start = 1;
	while (window.isOpen() && end_game == 0) {

		if (clk == 1 && clock.getElapsedTime().asSeconds() * 1000 - time1.asSeconds() * 1000 > 1) {

			system("cls");
			std::cout << "Cursor:[" << p_cur.x << "|" << p_cur.y << "]" << std::endl;
			std::cout << "xy:[" << x << "|" << y << "]" << std::endl;
			std::cout << std::endl;
			std::cout << "move=" << move << std::endl;
			std::cout << std::endl;
			std::cout << "status.whose_move=" << status.whose_move << std::endl;
			std::cout << std::endl;

			std::cout << "STATUS:" << std::endl;
			std::cout << "    ok=" << status.ok << std::endl;
			std::cout << "    attak=" << status.attak << std::endl;
			std::cout << "    whose_move=" << status.whose_move << std::endl;
			std::cout << "    fig=" << status.fig << std::endl;
			std::cout << "    figNum=" << status.figNum << std::endl;
			std::cout << "    p_old=[" << status.p_old.x << "|" << status.p_old.y << "]" << std::endl;
			std::cout << "    p_new=[" << status.p_new.x << "|" << status.p_new.y << "]" << std::endl;
			std::cout << "    p_attak=[" << status.p_attak.x << "|" << status.p_attak.y << "]" << std::endl;

			std::cout << "PawnsJump:" << std::endl;
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < LENGTH; j++) {
					std::cout << PawnsJump[i][j] << " ";
				}
				std::cout << std::endl;
			}

			std::cout << "RooksMove:" << std::endl;
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < 2; j++) {
					std::cout << RooksMove[i][j] << " ";
				}
				std::cout << std::endl;
			}

			std::cout << "KingsMove:" << std::endl;
			for (int j = 0; j < 2; j++) {
				std::cout << KingsMove[j] << " ";
			}

			std::cout << std::endl;
			POS p_king = find_pos_king((status.whose_move == 1) ? -1 : 1, board);
			std::cout << "p_king:[" << p_king.x << "|" << p_king.y << "]" << std::endl;
			int sss = KingCheck((status.whose_move == 1) ? -1 : 1, p_king, board);
			std::cout << "KingCheck:" << sss << std::endl;

			time1 = clock.getElapsedTime();
		}

		
		Vector2i pos = Mouse::getPosition(window);
		p_cur.x = pos.x - 50;
		p_cur.y = pos.y - 50;

		pos.y -= 50;
		pos.x -= 50;
		
		x = p_cur.x / size;
		y = p_cur.y / size;
		x = (x < 0) ? 0 : ((x > 7) ? 7 : x);
		y = (y < 0) ? 0 : ((y > 7) ? 7 : y);

		
		if (start==0&&my_auth.whomai != status.whose_move && clock_listen.getElapsedTime().asSeconds() >1) {
			string answer = new_cmd(my_auth.ip, my_auth.port, "0000000|get_ready|" + my_auth.Login + "|" + my_auth.Password + "|" + my_auth.name_server + "|" + std::to_string(my_auth.whomai));
			std::vector<string> ans;
			ans = split(answer, "-");
			if (ans[0] == "1") {
				string ans = listen_cmd(my_auth.ip_my, my_auth.port_my, 0.2f);

				std::vector<string> answ;
				answ = split(ans, "=");
				if (answ[1] == my_auth.room_password) {
					if (answ[2] == "1") {
						status.whose_move = my_auth.whomai;
						shag = my_auth.whomai;
						std::vector<string> rows, cells;
						rows = split(answ[3], ".");
						for (int i = 0; i < rows.size(); i++) {
							cells = split(rows[i], ",");
							for (int j = 0; j < cells.size(); j++) {
								int ss = atoi(cells[j].c_str());
								//std::cout << ss << " ";
								board[i][j] = ss;
							}
							//std::cout << "\n";
						}

					}
					else if (answ[2] == "2") {
						std::vector<string> rows, cells;
						rows = split(answ[3], ".");
						for (int i = 0; i < rows.size(); i++) {
							cells = split(rows[i], ",");
							for (int j = 0; j < cells.size(); j++) {
								int ss = atoi(cells[j].c_str());
								//std::cout << ss << " ";
								board[i][j] = ss;
							}
							//std::cout << "\n";
						}
						my_auth.who_win = atoi(answ[4].c_str());
						end_game = 1;
					}
				}
			}
			clock_listen.restart();
		}


		while (window.pollEvent(e)&& end_game==0) {

			if (e.type == Event::Closed) {
				end_game = 1;
				window.close();

			}

			window.clear();

			

			if (my_auth.whomai == status.whose_move) {
				if (e.type == Event::MouseButtonPressed) {
					if (e.key.code == Mouse::Left) {
						Click = 1;

						if (board[y][x] != 0 && transformation == 0) {
							dx = p_cur.x - x * 100;
							dy = p_cur.y - y * 100;

							if (board[y][x] == figs.Pawn * status.whose_move) {
								status.fig = figs.Pawn;
								//CurrentFigureNum = status.figNum;
								status.figNum = figs.Pawn * status.whose_move;
								FigSave = status.figNum;
								status.p_old.x = x;
								status.p_old.y = y;
								status.p_new.x = x;
								status.p_new.y = y;
								MoveImages = (status.whose_move == WHITE) ? W_Pawn : B_Pawn;
								board[y][x] = 0;
								move = 1;
							}
							if (board[y][x] == figs.Rook * status.whose_move) {

								status.fig = figs.Rook;
								//CurrentFigureNum = status.figNum;
								status.figNum = figs.Rook * status.whose_move;
								FigSave = status.figNum;
								status.p_old.x = x;
								status.p_old.y = y;
								status.p_new.x = x;
								status.p_new.y = y;
								MoveImages = (status.whose_move == WHITE) ? W_Rook : B_Rook;
								board[y][x] = 0;
								move = 1;
							}
							if (board[y][x] == figs.King * status.whose_move) {
								status.fig = figs.King;
								//CurrentFigureNum = status.figNum;
								status.figNum = figs.King * status.whose_move;
								FigSave = status.figNum;
								status.p_old.x = x;
								status.p_old.y = y;
								status.p_new.x = x;
								status.p_new.y = y;
								MoveImages = (status.whose_move == WHITE) ? W_King : B_King;
								board[y][x] = 0;
								move = 1;
							}
							if (board[y][x] == figs.Knight * status.whose_move) {
								status.fig = figs.Knight;
								//CurrentFigureNum = status.figNum;
								status.figNum = figs.Knight * status.whose_move;
								FigSave = status.figNum;
								status.p_old.x = x;
								status.p_old.y = y;
								status.p_new.x = x;
								status.p_new.y = y;
								MoveImages = (status.whose_move == WHITE) ? W_Knight : B_Knight;
								board[y][x] = 0;
								move = 1;
							}
							if (board[y][x] == figs.Bishop * status.whose_move) {
								status.fig = figs.Bishop;
								//CurrentFigureNum = status.figNum;
								status.figNum = figs.Bishop * status.whose_move;
								FigSave = status.figNum;
								status.p_old.x = x;
								status.p_old.y = y;
								status.p_new.x = x;
								status.p_new.y = y;
								MoveImages = (status.whose_move == WHITE) ? W_Bishop : B_Bishop;
								board[y][x] = 0;
								move = 1;
							}
							if (board[y][x] == figs.Queen * status.whose_move) {
								status.fig = figs.Queen;
								//CurrentFigureNum = status.figNum;
								status.figNum = figs.Queen * status.whose_move;
								FigSave = status.figNum;
								status.p_old.x = x;
								status.p_old.y = y;
								status.p_new.x = x;
								status.p_new.y = y;
								MoveImages = (status.whose_move == WHITE) ? W_Queen : B_Queen;
								board[y][x] = 0;
								move = 1;
							}
						}
					}
				}
				if (e.type == Event::MouseButtonReleased) {
					if (e.key.code == Mouse::Left) {
						Click = 0;

						if (move == 1 && transformation == 0) {
							status.p_new.x = x;
							status.p_new.y = y;
							if (status.p_new.x != status.p_old.x || status.p_new.y != status.p_old.y) {
								Chess_move(status, board);
								//good = KingCheck(figs.King, status.whose_move, status.p_old, status.p_new, board);
								//std::cout << good << std::endl;

								//Проверка можно ли сделать ход чтоб не подставить короля под шах
								if (status.ok == 1) {
									int saveF_old = 0;
									int saveF_new = 0;
									saveF_old = status.figNum;
									saveF_new = board[status.p_new.y][status.p_new.x];
									board[status.p_old.y][status.p_old.x] = 0;
									board[status.p_new.y][status.p_new.x] = saveF_old;

									POS p_king = find_pos_king(status.whose_move, board);
									int attack = (status.whose_move == WHITE) ? BLACK : WHITE;
									shah = KingCheck(attack, p_king, board);

									board[status.p_old.y][status.p_old.x] = saveF_old;
									board[status.p_new.y][status.p_new.x] = saveF_new;
									//std::cout << "KingCheck:" << shah << std::endl;
									if (shah != 0){
										status.ok = 0;
										//end_game = 1;
									}

								}

								//Если мы дошли пешкой до конца доски
								if (status.ok == 1) {
									if (y == 0 && status.figNum == -666 || y == 7 && status.figNum == 666) {
										transformation = 1;
										t_transform.x = status.p_new.x;
										t_transform.y = status.p_new.y;
										status.ok = 2;
										board[status.p_new.y][status.p_new.x] = 0;
									}
								}
								//Если была рокировка
								if (status.ok == 1) {
									if (status.fig == figs.King &&
										abs(status.p_old.x - status.p_new.x) > 1) {
										board[status.p_old.y][status.p_old.x] = 0;
										board[status.p_new.y][status.p_new.x] = status.figNum;
										int left_or_right = (status.p_new.x > status.p_old.x) ? 7 : 0;
										board[status.p_old.y][left_or_right] = 0;
										board[status.p_old.y][(left_or_right == 7) ? 5 : 3] = figs.Rook * status.whose_move;
										//shag = (shag == -1) ? 1 : -1;
									}
								}

								if (status.ok == 1) {
									board[status.p_old.y][status.p_old.x] = 0;
									int who = 0;
									if (status.attak == 1) {
										who = board[status.p_attak.y][status.p_attak.x];
										board[status.p_attak.y][status.p_attak.x] = 0;
									}
									board[status.p_new.y][status.p_new.x] = status.figNum;
									shag = (shag == -1) ? 1 : -1;
								}
								else if (status.ok == 0) {
									board[status.p_old.y][status.p_old.x] = FigSave;
								}
							}
							else {
								board[status.p_old.y][status.p_old.x] = FigSave;
							}
						}
						else if (transformation == 1) {
							int x1, y1, good = 0;
							x1 = (p_cur.x - status.p_new.x * size);
							y1 = (p_cur.y - status.p_new.y * size);
							/*
							std::cout << "______________" << std::endl;
							std::cout << "Cursor:[" << p_cur.x << "|" << p_cur.y << "]" << std::endl;
							std::cout << "xy:[" << x1 << "|" << y1 << "]" << std::endl;
							std::cout << "xy/2:[" << x/2 << "|" << y1/2 << "]" << std::endl;
							std::cout << "--------------" << std::endl;
							*/
							if (0 < x1 && x1 < 50 && 0 < y1 && y1 < 50) {
								//std::cout << 2 << std::endl;
								status.figNum = figs.Rook * status.whose_move;
								board[t_transform.y][t_transform.x] = status.figNum;
								good = 1;
							}
							else if (size > x1 && x1 > 50 && 0 < y1 && y1 < 50) {
								//std::cout << 5 << std::endl;
								status.figNum = figs.Queen * status.whose_move;
								board[t_transform.y][t_transform.x] = status.figNum;
								good = 1;
							}
							else if (0 < x1 && x1 < 50 && size>y1 && y1 > 50) {
								//std::cout << 4 << std::endl;
								status.figNum = figs.Bishop * status.whose_move;
								board[t_transform.y][t_transform.x] = status.figNum;
								good = 1;
							}
							else if (size > x1 && x1 > 50 && size > y1 && y1 > 50) {
								//std::cout << 3 << std::endl;
								status.figNum = figs.Knight * status.whose_move;
								board[t_transform.y][t_transform.x] = status.figNum;
								good = 1;
							}
							if (good == 1) {
								transformation = 0;
								board[status.p_old.y][status.p_old.x] = 0;
								board[status.p_new.y][status.p_new.x] = status.figNum;
								status.ok = 1;
								shag = (shag == -1) ? 1 : -1;
							}
						}
						//Проверка можно ли сделать ход противнику при шахе чтобы выйти из под него
						if (status.ok == 1) {
							int attack = (status.whose_move == WHITE) ? BLACK : WHITE;
							POS p_king = find_pos_king(attack, board);
							shah = KingCheck(status.whose_move, p_king, board);
							std::cout << "shah:" << shah << std::endl;
							if (shah != 0) {
								POS p_king = find_pos_king(attack, board);
								mat = check_mat(attack, p_king, board);
								std::cout << "mat:" << mat << std::endl;
								if (mat != 0) {
									std::cout << "end_game:" << std::endl;
									end_game = 1;
									my_auth.who_win = status.whose_move;
									std::cout << "win:" <<(my_auth.who_win==WHITE)?"WHITE\n":"BLACK\n";
								}
							}
						}
						move = 0;
					}
					if (status.whose_move != shag) {
						board_str = ".";
						for (int i = 0; i < LENGTH; i++) {
							for (int j = 0; j < LENGTH; j++)
								board_str += std::to_string(board[i][j]) + ",";
							board_str[board_str.length() - 1] = '.';
						}
						clock_shag.restart();
						first_send = 1;
					}
				}

				
				if (status.whose_move != shag && (first_send==1||clock.getElapsedTime().asSeconds() > 1)) {
					string answer = new_cmd(my_auth.ip, my_auth.port, "0000000|set_ready|" + my_auth.Login + "|" + my_auth.Password+"|"+my_auth.name_server+"|"+std::to_string(my_auth.whomai));

					if (my_auth.who_win == status.whose_move) {
						answer = new_cmd(my_auth.ip_user2, my_auth.port_user2, "=" + my_auth.room_password + "=2=" + board_str + "=" + std::to_string(my_auth.who_win) + "=");
					}
					else {
						answer = new_cmd(my_auth.ip_user2, my_auth.port_user2, "=" + my_auth.room_password + "=1=" + board_str + "=");
					}
					std::vector<string> cou;
					//std::cout << "answer:" << answer << "\n";
					cou = split(answer, "-");
					//std::cout << "ans1:" << cou[0] << "\n";
					if (cou[0] == '1') {
						status.whose_move = shag;
						clock_listen.restart();
					}
					clock_shag.restart();
					first_send = 0;
				}
			}
		}



		window.clear();
		window.draw(Board);
		if (transformation == 1) {
			if (status.figNum == -666) {
				W_Pawn_Transf.setPosition(t_transform.x * size + x_start, t_transform.y * size + y_start);
				window.draw(W_Pawn_Transf);
			}
			else if (status.figNum == 666) {
				B_Pawn_Transf.setPosition(t_transform.x * size + x_start, t_transform.y * size + y_start);
				window.draw(B_Pawn_Transf);
			}
		}
		if (move == 1) {
			MoveImages.setPosition(p_cur.x - dx + 50, p_cur.y - dy + 50);
			window.draw(MoveImages);
		}
		for (int i = 0; i < LENGTH; i++) {
			for (int j = 0; j < LENGTH; j++) {
				if (board[i][j] != 0) {
					if (board[i][j] == figs.Pawn * BLACK) {
						B_Pawn.setPosition(j * size + x_start, i * size + y_start);
						window.draw(B_Pawn);
					}
					if (board[i][j] == figs.Pawn * WHITE) {
						W_Pawn.setPosition(j * size + x_start, i * size + y_start);
						window.draw(W_Pawn);
					}
					if (board[i][j] == figs.Rook * BLACK) {
						B_Rook.setPosition(j * size + x_start, i * size + y_start);
						window.draw(B_Rook);

					}
					if (board[i][j] == figs.Rook * WHITE) {
						W_Rook.setPosition(j * size + x_start, i * size + y_start);
						window.draw(W_Rook);

					}
					if (board[i][j] == figs.Knight * BLACK) {
						B_Knight.setPosition(j * size + x_start, i * size + y_start);
						window.draw(B_Knight);
					}
					if (board[i][j] == figs.Knight * WHITE) {
						W_Knight.setPosition(j * size + x_start, i * size + y_start);
						window.draw(W_Knight);
					}
					if (board[i][j] == figs.Bishop * BLACK) {
						B_Bishop.setPosition(j * size + x_start, i * size + y_start);
						window.draw(B_Bishop);
					}
					if (board[i][j] == figs.Bishop * WHITE) {
						W_Bishop.setPosition(j * size + x_start, i * size + y_start);
						window.draw(W_Bishop);
					}
					if (board[i][j] == figs.Queen * WHITE) {
						W_Queen.setPosition(j * size + x_start, i * size + y_start);
						window.draw(W_Queen);
					}
					if (board[i][j] == figs.Queen * BLACK) {
						B_Queen.setPosition(j * size + x_start, i * size + y_start);
						window.draw(B_Queen);
					}
					if (board[i][j] == figs.King * BLACK) {
						B_King.setPosition(j * size + x_start, i * size + y_start);
						window.draw(B_King);
					}
					if (board[i][j] == figs.King * WHITE) {
						W_King.setPosition(j * size + x_start, i * size + y_start);
						window.draw(W_King);
					}
				}
			}
		}
		

		TextBox_name_user1.setString(user1 + name_user1);
		TextBox_name_user2.setString(user2 + name_user2);
		TextBox_s_exp_user1.setString(s_exp + s_exp_user1);
		TextBox_s_exp_user2.setString(s_exp + s_exp_user2);
		TextBox_s_about.setString(s_about);
		window.draw(TextBox_name_user1);
		window.draw(TextBox_name_user2);
		window.draw(TextBox_s_exp_user1);
		window.draw(TextBox_s_exp_user2);
		window.draw(TextBox_s_about);
		window.draw(menu_ready);
		
		window.display();
		start = 0;
	};

	return my_auth;

}


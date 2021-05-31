#pragma once
#include "include.h"

using namespace sf;
using std::string;
using std::to_string;

//#include <thread>
//#include <mutex>

struct POS;
struct FIG;
struct STATUS;
struct Net;

//-----------


//Поиск фигуры
POS Get_Pos(int Board[8][8], int Figure, int Colour);
//Функция ходьбы фигурами
void Chess_move(struct STATUS& status, int board[8][8]);
//Поиск координат короля
POS find_pos_king(int whose_move, int board[8][8]);
//Функция проверки находится ли король под шахом
int KingCheck(int whose_move, POS p_king, int Board[8][8]);
//Функция проверки невозможности выхода из под шаха
int check_mat(int whose_move, POS p_king, int brd[8][8]);
//Функция инициализации начальных параметров
void inicialise();
struct Auth Game(RenderWindow& window, struct Auth ath);
struct Auth Game_single(RenderWindow& window, struct Auth ath);

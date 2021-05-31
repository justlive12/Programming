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


//����� ������
POS Get_Pos(int Board[8][8], int Figure, int Colour);
//������� ������ ��������
void Chess_move(struct STATUS& status, int board[8][8]);
//����� ��������� ������
POS find_pos_king(int whose_move, int board[8][8]);
//������� �������� ��������� �� ������ ��� �����
int KingCheck(int whose_move, POS p_king, int Board[8][8]);
//������� �������� ������������� ������ �� ��� ����
int check_mat(int whose_move, POS p_king, int brd[8][8]);
//������� ������������� ��������� ����������
void inicialise();
struct Auth Game(RenderWindow& window, struct Auth ath);
struct Auth Game_single(RenderWindow& window, struct Auth ath);

#pragma once
#include<stdlib.h>
#include<stdio.h>

#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Network.hpp>
#include<iostream>
#include<string>

#include <random>

#include"Menu.h"
#include"Chess.h"
#include<cmath>
#include<vector>

using namespace sf;
using std::string;
using std::to_string;



struct flags {
	bool conn = false;
	bool menu = false;
	bool exit = false;
};

//Структура для адреса подключения по сети
struct Auth {
	//my
	std::string ip_my;
	std::string port_my;
	int whomai=-2;//Кто я сервер или клиент server or client
	//server
	std::string ip;
	std::string port;
	std::string Login;
	std::string Password;
	std::string name_server;//назание комнаты
	//user2
	std::string Login_user2;
	std::string ip_user2;
	std::string port_user2;
	std::string room_password;

	int who_win=-3;//Кто выиграл

	flags f;//Флаги разрешения запуска частей меню
};

string get_str_in_char(char data[1024]);
string new_cmd(string s_ip, string s_p, string data);
string listen_cmd(string s_ip, string s_p, float hm);
int check_authorisation(string s_ip, string s_p, string data);
std::vector<string> split(const string& str, const string& delim);
string repl(string data, string sub);
void win_end(RenderWindow& window1, string Statistic);
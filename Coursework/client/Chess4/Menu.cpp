#include"Menu.h"

using namespace sf;
using std::string;
using std::to_string;

struct Auth Menu_Connect(RenderWindow& window, struct Auth ath) {
	sf::Image WindowIcon;
	if (!WindowIcon.loadFromFile("files/icon.png"))
		std::cout << "cant load texture from file " << std::endl;
	else
		window.setIcon(128, 128, WindowIcon.getPixelsPtr());
	sf::Font font;
	sf::Font& refFont = font;
	if (!font.loadFromFile("files/font.otf")) {
		std::cout << "cant load font" << std::endl;
	}
	Texture t_Background, under_bg;
	t_Background.loadFromFile("files/menu_connect/bg.png");
	Sprite s_bg(t_Background),
		s_under_bg(t_Background);
	//============================================================
	Texture t_b_left, t_b_right, t_w_left, t_w_right, t_textbox, t_reg, t_vhod;
	t_b_left.loadFromFile("files/menu_connect/b_left.png");
	t_b_right.loadFromFile("files/menu_connect/b_right.png");
	t_w_left.loadFromFile("files/menu_connect/w_left.png");
	t_w_right.loadFromFile("files/menu_connect/w_right.png");
	t_textbox.loadFromFile("files/menu_connect/textbox.png");
	t_reg.loadFromFile("files/menu_connect/reg.png");
	t_vhod.loadFromFile("files/menu_connect/vhod.png");
	Texture t_B_enter, t_B_registration, t_B_login, t_B_password, t_B_enter_click, t_B_registration_click;
	t_B_enter.loadFromFile("files/menu_connect/Next_enter.png");
	t_B_enter_click.loadFromFile("files/menu_connect/Next_enter_click.png");
	t_B_registration.loadFromFile("files/menu_connect/Reg_enter.png");
	t_B_registration_click.loadFromFile("files/menu_connect/Reg_enter_click.png");
	t_B_login.loadFromFile("files/menu_connect/mail.png");
	t_B_password.loadFromFile("files/menu_connect/password.png");
	Sprite s_b_left(t_b_left),
		s_b_right(t_b_right),
		s_w_left(t_w_left),
		s_w_right(t_w_right),
		s_textbox1(t_textbox),
		s_textbox2(t_textbox),
		s_textbox3(t_textbox),
		s_textbox4(t_textbox),
		s_textbox5(t_textbox),
		s_textbox6(t_textbox),
		s_reg(t_reg),
		s_vhod(t_vhod),
		s_B_enter_reg,
		s_B_enter(t_B_enter),
		s_B_registration(t_B_registration),
		s_B_login(t_B_login),
		s_B_password(t_B_password);
	Sprite B_left, B_right;
	//------------------------------------------------------------
	s_bg.setPosition(0, 0);
	s_under_bg.setPosition(0, 144);

	int current_button_loginOrReg = 0;
	B_left = s_b_right;
	B_right = s_b_left;
	B_left.setPosition(2.f, 2.f);
	B_right.setPosition(212.f, 2.f);

	s_textbox1.setPosition(23.f, 60.f);
	s_textbox2.setPosition(23.f, 100.f);
	s_textbox3.setPosition(23.f, 140.f);
	s_textbox4.setPosition(23.f, 180.f);
	s_textbox5.setPosition(23.f, 220.f);
	s_textbox6.setPosition(23.f, 260.f);

	s_B_enter_reg.setPosition(23.f, 320.f);

	s_reg.setPosition(70.f, 25.f);
	s_vhod.setPosition(295.f, 25.f);


	//------------------------------------------------------------
	//TextBox
	std::srand((sf::Mouse::getPosition(window).x + sf::Mouse::getPosition(window).y));
	
	//Рандом от 5555 до 8000
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> uni(5555, 8000);
	auto random_integer = uni(rng);
	std::string login = "", password = "", s_ip = "localhost", s_p = "5555", s_my_ip = "localhost", s_my_p = std::to_string(random_integer);
	sf::Text TextBox_login(login, font, 36);
	sf::Text TextBox_password(password, font, 36);
	sf::Text TextBox_ip(s_ip, font, 36);
	sf::Text TextBox_port(s_p, font, 36);
	sf::Text TextBox_my_ip(s_my_ip, font, 36);
	sf::Text TextBox_my_p(s_my_p, font, 36);
	TextBox_login.setFillColor(sf::Color::Blue);
	TextBox_password.setFillColor(sf::Color::Blue);
	TextBox_ip.setFillColor(sf::Color::Blue);
	TextBox_port.setFillColor(sf::Color::Blue);
	TextBox_my_ip.setFillColor(sf::Color::Blue);
	TextBox_my_p.setFillColor(sf::Color::Blue);
	TextBox_login.setStyle(sf::Text::Bold | sf::Text::Underlined);
	TextBox_password.setStyle(sf::Text::Bold | sf::Text::Underlined);
	TextBox_ip.setStyle(sf::Text::Bold | sf::Text::Underlined);
	TextBox_port.setStyle(sf::Text::Bold | sf::Text::Underlined);
	TextBox_my_ip.setStyle(sf::Text::Bold | sf::Text::Underlined);
	TextBox_my_p.setStyle(sf::Text::Bold | sf::Text::Underlined);
	//-----------
	sf::Clock blink_text_clock;
	static sf::Time text_effect_time;
	static bool show_cursor = true;
	//-----------
	TextBox_login.setPosition(33, 58);
	TextBox_password.setPosition(33, 98);
	TextBox_ip.setPosition(33, 138);
	TextBox_port.setPosition(33, 178);
	TextBox_my_ip.setPosition(33, 218);
	TextBox_my_p.setPosition(33, 258);
	//-----------
	//------------------------------------------------------------

	int TailleWindow[4] = { static_cast<int>(window.getSize().x),
							static_cast<int>(window.getSize().y),
							sf::Mouse::getPosition(window).x,
							sf::Mouse::getPosition(window).y
	};

	int what_do = 0;
	int login_pass_ip_port = 0;

	int reg_ok = 0;
	int login_ok = 0;
	int end = 0;
	sf::Event event;

	while (window.isOpen() && end == 0) {

		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				ath.f.conn = true;
				ath.f.menu = true;
				ath.f.exit = true;
				end = 1;
				break;
			case sf::Event::TextEntered:
				if (std::isprint(event.text.unicode)) {
					if (login_pass_ip_port == 0)
						login += event.text.unicode;
					else if (login_pass_ip_port == 1)
						password += event.text.unicode;
					else if (login_pass_ip_port == 2)
						s_ip += event.text.unicode;
					else if (login_pass_ip_port == 3)
						s_p += event.text.unicode;
					else if (login_pass_ip_port == 4)
						s_my_ip += event.text.unicode;
					else if (login_pass_ip_port == 5)
						s_my_p += event.text.unicode;
					login = repl(login, "\t");
					login = repl(login, "\n");

					password = repl(password, "\t");
					password = repl(password, "\n");

					s_ip = repl(s_ip, "\t");
					s_ip = repl(s_ip, "\n");

					s_p = repl(s_p, "\t");
					s_p = repl(s_p, "\n");

					s_my_ip = repl(s_my_ip, "\t");
					s_my_ip = repl(s_my_ip, "\n");

					s_my_p = repl(s_my_p, "\t");
					s_my_p = repl(s_my_p, "\n");
				}
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape) {
					end = 1;
					ath.f.conn = true;
					ath.f.menu = true;
					ath.f.exit = true;
					break;
				}
				if (event.key.code == sf::Keyboard::BackSpace) {
					if (login_pass_ip_port == 0) {
						if (!login.empty())
							login.pop_back();
					}
					else if (login_pass_ip_port == 1) {
						if (!password.empty())
							password.pop_back();
					}
					else if (login_pass_ip_port == 2) {
						if (!s_ip.empty())
							s_ip.pop_back();
					}
					else if (login_pass_ip_port == 3) {
						if (!s_p.empty())
							s_p.pop_back();
					}
					else if (login_pass_ip_port == 4) {
						if (!s_my_ip.empty())
							s_my_ip.pop_back();
					}
					else if (login_pass_ip_port == 5) {
						if (!s_my_p.empty())
							s_my_p.pop_back();
					}
					login = repl(login, "\t");
					login = repl(login, "\n");

					password = repl(password, "\t");
					password = repl(password, "\n");

					s_ip = repl(s_ip, "\t");
					s_ip = repl(s_ip, "\n");

					s_p = repl(s_p, "\t");
					s_p = repl(s_p, "\n");

					s_my_ip = repl(s_my_ip, "\t");
					s_my_ip = repl(s_my_ip, "\n");

					s_my_p = repl(s_my_p, "\t");
					s_my_p = repl(s_my_p, "\n");
				}
				if (event.key.code == sf::Keyboard::Return) {
					/*
					if (login_pass_ip_port == 0)
						login += '\n';
					else
						password += '\n';
					*/
				}
				if (event.key.code == sf::Keyboard::Tab) {
					if (login_pass_ip_port == 5)
						login_pass_ip_port = 0;
					else if (login_pass_ip_port == 4)
						login_pass_ip_port = 5;
					else if (login_pass_ip_port == 3)
						login_pass_ip_port = 4;
					else if (login_pass_ip_port == 2)
						login_pass_ip_port = 3;
					else if (login_pass_ip_port == 1)
						login_pass_ip_port = 2;
					else if (login_pass_ip_port == 0)
						login_pass_ip_port = 1;
					login = repl(login, "\t");
					login = repl(login, "\n");

					password = repl(password, "\t");
					password = repl(password, "\n");

					s_ip = repl(s_ip, "\t");
					s_ip = repl(s_ip, "\n");

					s_p = repl(s_p, "\t");
					s_p = repl(s_p, "\n");

					s_my_ip = repl(s_my_ip, "\t");
					s_my_ip = repl(s_my_ip, "\n");

					s_my_p = repl(s_my_p, "\t");
					s_my_p = repl(s_my_p, "\n");

				}
				break;
			case Event::MouseButtonPressed://MouseButtonPressed//MouseButtonReleased
				/*
				if (event.key.code == Mouse::Left) {
					std::cout << "x=" << sf::Mouse::getPosition(window).x << std::endl;
					std::cout << "y=" << sf::Mouse::getPosition(window).y << std::endl;
					TailleWindow[2] = sf::Mouse::getPosition(window).x;
					TailleWindow[3] = sf::Mouse::getPosition(window).y;
				}
				*/
				//isMenu = false;
				break;
			}
			/*
			if (event.type == Event::Closed) {
				//Обработка события при нажатии на закрыть окно
				end = 1;
			}
			*/
		}



		if (what_do == 0) {


			B_left.setTexture(t_b_left);
			B_right.setTexture(t_w_right);

			s_B_enter_reg.setTexture(t_B_enter);


		}
		else {
			B_left.setTexture(t_w_left);
			B_right.setTexture(t_b_right);

			s_B_enter_reg.setTexture(t_B_registration);
		}

		int menuNum = 0;
		if (IntRect(2.f, 2.f, 211.f, 49.f).contains(Mouse::getPosition(window))) { menuNum = 1; }
		if (IntRect(216.f, 2.f, 210.f, 49.f).contains(Mouse::getPosition(window))) { menuNum = 2; }

		if (IntRect(30.f, 63.f, 366.f, 35.f).contains(Mouse::getPosition(window))) { menuNum = 3; }
		if (IntRect(30.f, 105.f, 366.f, 35.f).contains(Mouse::getPosition(window))) { menuNum = 4; }
		if (IntRect(30.f, 143.f, 366.f, 35.f).contains(Mouse::getPosition(window))) { menuNum = 5; }
		if (IntRect(30.f, 184.f, 366.f, 35.f).contains(Mouse::getPosition(window))) { menuNum = 6; }
		if (IntRect(30.f, 224.f, 366.f, 35.f).contains(Mouse::getPosition(window))) { menuNum = 7; }
		if (IntRect(30.f, 264.f, 366.f, 35.f).contains(Mouse::getPosition(window))) { menuNum = 8; }

		if (IntRect(26.f, 319.f, 372.f, 40.f).contains(Mouse::getPosition(window))) { menuNum = 9; }

		if (Mouse::isButtonPressed(Mouse::Left)) {
			if (menuNum == 1) { what_do = 1; }
			if (menuNum == 2) { what_do = 0; }
			if (menuNum == 3) { login_pass_ip_port = 0; }
			if (menuNum == 4) { login_pass_ip_port = 1; }
			if (menuNum == 5) { login_pass_ip_port = 2; }
			if (menuNum == 6) { login_pass_ip_port = 3; }
			if (menuNum == 7) { login_pass_ip_port = 4; }
			if (menuNum == 8) { login_pass_ip_port = 5; }
			if (menuNum == 9) {
				if (what_do == 0) {
					s_B_enter_reg.setTexture(t_B_enter_click);
					//login
					int answer = 0;
					sf::Clock clock, pause;
					float ftime = clock.getElapsedTime().asSeconds(); 
					clock.restart();
					while (answer == 0 && clock.getElapsedTime().asSeconds() < 6) {
						if (pause.getElapsedTime().asSeconds() >= 1) {
							answer = check_authorisation(s_ip, s_p, "0000000|login|" + login + "|" + password);
							pause.restart();
						}
					}
					if (answer == 1) {
						ath.Login = login;
						ath.Password = password;
						ath.ip = s_ip;
						ath.port = s_p;
						ath.ip_my = s_my_ip;
						ath.port_my = s_my_p;
					}
					login_ok = answer;
				}
				else {
					s_B_enter_reg.setTexture(t_B_registration_click);
					//register
					int answer = 0;
					sf::Clock clock, pause;
					float ftime = clock.getElapsedTime().asSeconds(); 
					clock.restart();

					while (answer == 0 && clock.getElapsedTime().asSeconds() < 6) {
						if (pause.getElapsedTime().asSeconds() >= 1) {
							answer = check_authorisation(s_ip, s_p, "0000000|reg|" + login + "|" + password);
							pause.restart();
						}
					}
					reg_ok = answer;


				}

			}
		}

		
		text_effect_time += blink_text_clock.restart();
		if (text_effect_time >= sf::seconds(0.5f)) {
			show_cursor = !show_cursor;
			text_effect_time = sf::Time::Zero;
		}

		if (reg_ok == 1) {
			TextBox_login.setFillColor(sf::Color::Green);
			TextBox_password.setFillColor(sf::Color::Green);
			TextBox_ip.setFillColor(sf::Color::Green);
			TextBox_port.setFillColor(sf::Color::Green);
			TextBox_login.setString((show_cursor ? "Ok>|" : "Ok>[") + login + (show_cursor ? "|" : "]"));
			TextBox_password.setString((show_cursor ? "Ok>|" : "Ok>[") + password + (show_cursor ? "|" : "]"));
			TextBox_ip.setString((show_cursor ? "Ok>|" : "Ok>[") + s_ip + (show_cursor ? "|" : "]"));
			TextBox_port.setString((show_cursor ? "Ok>|" : "Ok>[") + s_p + (show_cursor ? "|" : "]"));
			TextBox_my_ip.setString((show_cursor ? ">" : ">") + s_my_ip);
			TextBox_my_p.setString((show_cursor ? ">" : ">") + s_my_p);
		}
		else if (reg_ok == 0) {
			TextBox_login.setFillColor(sf::Color::Blue);
			TextBox_password.setFillColor(sf::Color::Blue);
			TextBox_ip.setFillColor(sf::Color::Blue);
			TextBox_port.setFillColor(sf::Color::Blue);
			if (login_pass_ip_port == 0) {
				TextBox_login.setString((show_cursor ? "Login>" : "Login<") + login);
			}
			else if (login_pass_ip_port == 1) {
				TextBox_password.setString((show_cursor ? "Pass>" : "Pass<") + password);
			}
			else if (login_pass_ip_port == 2) {
				TextBox_ip.setString((show_cursor ? "IP>" : "IP<") + s_ip);
			}
			else if (login_pass_ip_port == 3) {
				TextBox_port.setString((show_cursor ? "Port>" : "Port<") + s_p);
			}
			else if (login_pass_ip_port == 4) {
				TextBox_my_ip.setString((show_cursor ? "MyIP>" : "MyIP<") + s_my_ip);
			}
			else if (login_pass_ip_port == 5) {
				TextBox_my_p.setString((show_cursor ? "MyPort>" : "MyPort<") + s_my_p);
			}
		}

		
		window.draw(s_bg);
		window.draw(s_under_bg);

		window.draw(B_left);
		window.draw(B_right);
		window.draw(s_textbox1);
		window.draw(s_textbox2);
		window.draw(s_textbox3);
		window.draw(s_textbox4);
		window.draw(s_textbox5);
		window.draw(s_textbox6);
		window.draw(s_B_enter_reg);
		window.draw(s_reg);
		window.draw(s_vhod);
		window.draw(TextBox_login);
		window.draw(TextBox_password);
		window.draw(TextBox_ip);
		window.draw(TextBox_port);
		window.draw(TextBox_my_ip);
		window.draw(TextBox_my_p);
		window.display();
		if (login_ok==1) {
			end = 1;
			ath.f.conn = true;
			ath.f.menu = false;
			ath.f.exit = false;
			window.close();
		}
	}
	window.close();
	return ath;
}

struct Auth Menu(RenderWindow& window, struct Auth ath) {
	sf::Image WindowIcon;
	if (!WindowIcon.loadFromFile("files/icon.png"))
		std::cout << "cant load texture from file " << std::endl;
	window.setIcon(128, 128, WindowIcon.getPixelsPtr());
	window.setMouseCursorVisible(true);
	sf::Font font;
	sf::Font& refFont = font;
	if (!font.loadFromFile("files/font.otf")) {
		std::cout << "cant load font" << std::endl;
	}
	//============================================================

	sf::Texture Texture1, Texture2, Texture3, Texture4, Texture5, menuBackground;
	Texture1.loadFromFile("files/b_single.png");
	Texture2.loadFromFile("files/b_server.png");
	Texture3.loadFromFile("files/b_client.png");
	Texture4.loadFromFile("files/b_statistic.png");
	menuBackground.loadFromFile("files/menu1.jpg");
	Sprite menu1(Texture1),
		menu2(Texture2),
		menu3(Texture3),
		menu4(Texture4),
		menu5(Texture5),
		menuBg(menuBackground);
	menu1.setPosition(100, 80);
	menu2.setPosition(115, 125);
	menu3.setPosition(115, 170);
	menu4.setPosition(100, 215);
	menuBg.setPosition(0, 0);

	//Параметры окна
	int TailleWindow[4] = { static_cast<int>(window.getSize().x),
							static_cast<int>(window.getSize().y),
							sf::Mouse::getPosition(window).x,
							sf::Mouse::getPosition(window).y
	};

	//------------------------------------------------------------
	//TextBox
	std::string Name, Name1 = "Name:", points, points1 = "points:", wins, wins1 = "wins:";
	sf::Text TextBox_Name(Name, font, 36);
	sf::Text TextBox_points(points, font, 36);
	sf::Text TextBox_wins(wins, font, 36);
	TextBox_Name.setFillColor(sf::Color::White);
	TextBox_points.setFillColor(sf::Color::White);
	TextBox_wins.setFillColor(sf::Color::White);
	TextBox_Name.setStyle(sf::Text::Bold | sf::Text::Underlined);
	TextBox_points.setStyle(sf::Text::Bold | sf::Text::Underlined);
	TextBox_wins.setStyle(sf::Text::Bold | sf::Text::Underlined);
	//-----------
	//position
	TextBox_Name.setPosition(80, 270);
	TextBox_points.setPosition(80, 310);
	TextBox_wins.setPosition(80, 345);
	//-----------
	
	int client_or_server = 0;

	float current_pos_b2_event[4] = { 126,135,86,33 },
		current_pos_b3_event[4] = { 130,180,85,33 };
	float pos_server_button_event[2][4] = { 125,135,89,33,
									50,135,89,33 };

	float pos_client_button_event[2][4] = { 130,180,87,33,
									53,180,87,33 };

	float pos_server_button_current[2] = { 115,125 };
	float pos_server_button[2][2] = { 115,125,
									40,125 };
	float pos_server_textbox[2][2] = { 150,132,
										150,177 };
	float pos_client_button_current[2] = { 115,170 };
	float pos_client_button[2][2] = { 115,170,
									40,170 };

	
	std::string Name_server = "", Name_server_cur = "";
	sf::Text TextBox_Name_server(Name_server_cur, font, 30);
	TextBox_Name_server.setFillColor(sf::Color::White);
	TextBox_Name_server.setStyle(sf::Text::Bold | sf::Text::Underlined);
	
	sf::Clock blink_text_clock;
	static sf::Time text_effect_time;
	static bool show_cursor = true;
	string anim = "";
	//------------------------------------------------------------
	
	int check_my_data = 1;
	int waiting_ready = 0;
	sf::Clock clock_ready;
	int left_release = 0;

	int isMenu = 0;
	int menuNum = 0;

	while (isMenu == 0)
	{
		window.draw(menuBg);

		
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {

			case sf::Event::Closed:
				isMenu = 1;
				ath.f.conn = true;
				ath.f.menu = true;
				ath.f.exit = true;
				break;
			case sf::Event::TextEntered:
				if (std::isprint(event.text.unicode))
					Name_server_cur += event.text.unicode;
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape) {
					isMenu = 1;
					ath.f.conn = true;
					ath.f.menu = true;
					ath.f.exit = true;
					break;
				}
				if (event.key.code == sf::Keyboard::BackSpace) {
					if (!Name_server_cur.empty())
						Name_server_cur.pop_back();
				}
			case Event::MouseButtonPressed:
				if (event.key.code == Mouse::Left) {
					left_release = 0;
				}

				break;
			case Event::MouseButtonReleased:
				break;
			}
		}



		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);
		menu4.setColor(Color::White);


		menu2.setPosition(pos_server_button_current[0], pos_server_button_current[1]);
		menu3.setPosition(pos_client_button_current[0], pos_client_button_current[1]);

		menuNum = 0;

		if (IntRect(114, 92, 112, 33).contains(Mouse::getPosition(window))) {
			menuNum = 1;
		}
		if (IntRect(114, 225, 113, 33).contains(Mouse::getPosition(window))) {
			menuNum = 4;
		}
		if (IntRect(84, 283, 175, 90).contains(Mouse::getPosition(window))) {
			menuNum = 5;
		}

		if (IntRect(current_pos_b2_event[0], current_pos_b2_event[1],
			current_pos_b2_event[2], current_pos_b2_event[3]).contains(Mouse::getPosition(window))) {
			menuNum = 2;
		}
		if (IntRect(current_pos_b3_event[0], current_pos_b3_event[1],
			current_pos_b3_event[2], current_pos_b3_event[3]).contains(Mouse::getPosition(window))) {
			menuNum = 3;
		}

		if (event.type == Event::MouseButtonPressed && event.key.code == Mouse::Left && left_release == 0) {
			if (menuNum == 1) {
				isMenu = 1;
				ath.f.conn = true;
				ath.f.menu = true;
				ath.f.exit = false;
				Name_server = Name_server_cur;
				ath.name_server = Name_server;
				string answer = new_cmd(ath.ip, ath.port, "0000000|create_room|" + ath.Login + "|" + ath.Password + "|Single|" + ath.Login + "=" + ath.ip_my + "=" + ath.port_my);
				answer = new_cmd(ath.ip, ath.port, "0000000|find_room|" + ath.Login + "|" + ath.Password + "||" + ath.Login + "=" + ath.ip_my + "=" + ath.port_my);
				ath.name_server = "Single";
				ath.Login_user2 = ath.Login;
				ath.ip_user2 = ath.ip;
				ath.port_user2 = ath.port;
				ath.whomai = -1;
			}
			if (menuNum == 2) {
				//server
				if (client_or_server != 1 && client_or_server != 11) {

					client_or_server = 1;
					Name_server_cur = "";
					anim = "";
				}
				else if (client_or_server == 11) {
					Name_server = Name_server_cur;
					ath.name_server = Name_server;
					string answer = new_cmd(ath.ip, ath.port, "0000000|create_room|" + ath.Login + "|" + ath.Password + "|" + ath.name_server + "|" + ath.Login + "=" + ath.ip_my + "=" + ath.port_my);
					
					string sub = "";
					int q = 0;
					for (int i = 0; i < answer.length(); i++) {
						if (answer[i] != '-') {
							sub += answer[i];
						}
						else if (answer[i] == '-') {
							q++;
							if (q == 2)
								break;
						}
					}
					answer = sub;
					//-----
					if (answer == "1") {
						Name_server_cur = "(waiting)";
						
						anim = "ok";
						waiting_ready = 1;
						clock_ready.restart();
					}
					else if (answer == "0") {
						anim = "no";
					}
				}
			}
			if (menuNum == 3) {
				
				if (client_or_server != 2) {

					client_or_server = 2;
					Name_server_cur = "";
					anim = "";
				}
				else if (client_or_server == 2) {
					Name_server = Name_server_cur;
					ath.name_server = Name_server;
					string answer = new_cmd(ath.ip, ath.port, "0000000|find_room|" + ath.Login + "|" + ath.Password + "|" + ath.name_server + "|" + ath.Login + "=" + ath.ip_my + "=" + ath.port_my);
					
					string sub = "";
					int q = 0;
					for (int i = 0; i < answer.length(); i++) {
						if (answer[i] != '-') {
							sub += answer[i];
						}
						else if (answer[i] == '-') {
							q++;
							if (q == 2)
								break;
						}
					}
					answer = sub;
					//-----
					if (answer[0] == '1') {
						Name_server_cur = "(waiting)";
						
						anim = "ok";
						waiting_ready = 2;
						clock_ready.restart();
					}
					else if (answer == "0") {
						anim = "no";
					}


				}
			}
			if (menuNum == 4) {
				client_or_server = 0;
				
				sf::RenderWindow window1(sf::VideoMode(350, 400), "Chess: Statistic");
				sf::Image WindowIcon;
				if (!WindowIcon.loadFromFile("files/icon.png"))
					std::cout << "cant load texture from file " << std::endl;
				window1.setIcon(128, 128, WindowIcon.getPixelsPtr());
				window1.setMouseCursorVisible(true);
				//-----------
				sf::Font font;
				sf::Font& refFont = font;
				if (!font.loadFromFile("files/normal.otf")) {
					std::cout << "cant load font" << std::endl;
				}

				std::string Statistic = "ssss";
				sf::Text TextBox_Statistic(Statistic, font, 20);
				TextBox_Statistic.setFillColor(sf::Color::Black);
				TextBox_Statistic.setStyle(sf::Text::Bold | sf::Text::Underlined);
				TextBox_Statistic.setPosition(25, 25);

				check_my_data = 1;
				while (window1.isOpen()) {
					window1.clear(Color(150, 166, 166));
					sf::Event event;
					while (window1.pollEvent(event)) {
						if (event.type == sf::Event::Closed)
							window1.close();
						if (event.type == sf::Event::KeyPressed)
							if (event.key.code == sf::Keyboard::Escape)
								window1.close();
					}
					//------------------------------------------------------------
					if (check_my_data == 1) {
						sf::Clock clock, pause;
						float ftime = clock.getElapsedTime().asSeconds(); 
						clock.restart();
						string answer = "";
						while (answer == "" && clock.getElapsedTime().asSeconds() < 6) {
							if (pause.getElapsedTime().asSeconds() >= 1) {
								answer = new_cmd(ath.ip, ath.port, "0000000|statistic_all|" + ath.Login + "|" + ath.Password);
								pause.restart();
							}
						}
						if (answer != "") {
							string sub = "";
							int q = 0;
							for (int i = 0; i < answer.length(); i++) {
								if (answer[i] != '-') {
									sub += answer[i];
								}
								else if (answer[i] == '-') {
									q++;
									if (q == 2)
										break;
								}
							}
							Statistic = sub;
						}
						check_my_data = 0;
						int q = 0;
						string rep = "[]()";
						for (int i = 0; i < rep.length(); i++)
							for (int j = 0; j < Statistic.length(); j++) {
								if (Statistic[j] == rep[i])
									Statistic.erase(j, 1);
								if (Statistic[j] == ',' && q < 2) {
									q = q + 1;
									Statistic[j] = '|';
								}
								else if (Statistic[j] == ',' && q == 2) {
									q = 0;
									Statistic[j] = '\n';
								}
							}
						Statistic = "name | points | wins\n" + Statistic;
						//std::cout << Statistic << std::endl;
					}
					//------------------------------------------------------------


					TextBox_Statistic.setString(Statistic);

					window1.draw(TextBox_Statistic);
					window1.display();
					window1.clear();


				}

			}
			if (menuNum == 5) {
				client_or_server = 0;
				check_my_data = 1;
				//------------------------------------------------------------
				if (check_my_data == 1) {
					sf::Clock clock, pause;
					float ftime = clock.getElapsedTime().asSeconds(); 
					clock.restart();
					string answer = "";
					while (answer == "" && clock.getElapsedTime().asSeconds() < 6) {
						if (pause.getElapsedTime().asSeconds() >= 1) {
							answer = new_cmd(ath.ip, ath.port, "0000000|statistic|" + ath.Login + "|" + ath.Password);
							pause.restart();
						}
					}
					if (answer != "") {
						string sub = "";
						int matrix[2] = { 0,0 };
						int q = 0;
						for (int i = 0; i < answer.length(); i++) {
							if (answer[i] != '-') {
								sub += answer[i];
							}
							else if (answer[i] == '-' && sub != "") {
								matrix[q] = atoi(sub.c_str());
								sub = "";
								q++;
								if (q == 2)
									break;
							}
						}
						Name = ath.Login;
						points = std::to_string(matrix[0]);
						wins = std::to_string(matrix[1]);
					}
					check_my_data = 0;
				}
				TextBox_Name.setString(Name1 + Name);
				TextBox_points.setString(points1 + points);
				TextBox_wins.setString(wins1 + wins);
			}
			left_release = 1;
		}

		//------------------------------------------------------------
		
		if (client_or_server == 0) {
			pos_server_button_current[0] = pos_server_button[0][0];
			pos_server_button_current[1] = pos_server_button[0][1];
			pos_client_button_current[0] = pos_client_button[0][0];
			pos_client_button_current[1] = pos_client_button[0][1];

			current_pos_b2_event[0] = pos_server_button_event[0][0];
			current_pos_b2_event[1] = pos_server_button_event[0][1];
			current_pos_b2_event[2] = pos_server_button_event[0][2];
			current_pos_b2_event[3] = pos_server_button_event[0][3];
			current_pos_b3_event[0] = pos_client_button_event[0][0];
			current_pos_b3_event[1] = pos_client_button_event[0][1];
			current_pos_b3_event[2] = pos_client_button_event[0][2];
			current_pos_b3_event[3] = pos_client_button_event[0][3];


		}
		else if (client_or_server == 1) {
			//server
			//Устновка позиций кнопок
			pos_server_button_current[0] = pos_server_button[1][0];
			pos_server_button_current[1] = pos_server_button[1][1];
			pos_client_button_current[0] = pos_client_button[0][0];
			pos_client_button_current[1] = pos_client_button[0][1];
			//Установка границ обработчика событий кнопок
			current_pos_b2_event[0] = pos_server_button_event[1][0];
			current_pos_b2_event[1] = pos_server_button_event[1][1];
			current_pos_b2_event[2] = pos_server_button_event[1][2];
			current_pos_b2_event[3] = pos_server_button_event[1][3];
			current_pos_b3_event[0] = pos_client_button_event[0][0];
			current_pos_b3_event[1] = pos_client_button_event[0][1];
			current_pos_b3_event[2] = pos_client_button_event[0][2];
			current_pos_b3_event[3] = pos_client_button_event[0][3];

			//Установка позиции textbox
			TextBox_Name_server.setPosition(pos_server_textbox[0][0], pos_server_textbox[0][1]);
			client_or_server = 11;
		}
		else if (client_or_server == 2) {
			//client
			//Устновка позиций кнопок
			pos_server_button_current[0] = pos_server_button[0][0];
			pos_server_button_current[1] = pos_server_button[0][1];
			pos_client_button_current[0] = pos_client_button[1][0];
			pos_client_button_current[1] = pos_client_button[1][1];
			//Установка границ обработчика событий кнопок
			current_pos_b2_event[0] = pos_server_button_event[0][0];
			current_pos_b2_event[1] = pos_server_button_event[0][1];
			current_pos_b2_event[2] = pos_server_button_event[0][2];
			current_pos_b2_event[3] = pos_server_button_event[0][3];
			current_pos_b3_event[0] = pos_client_button_event[1][0];
			current_pos_b3_event[1] = pos_client_button_event[1][1];
			current_pos_b3_event[2] = pos_client_button_event[1][2];
			current_pos_b3_event[3] = pos_client_button_event[1][3];

			//Установка позиции textbox
			TextBox_Name_server.setPosition(pos_server_textbox[1][0], pos_server_textbox[1][1]);


		}
		if (client_or_server != 0) {
			text_effect_time += blink_text_clock.restart();
			if (text_effect_time >= sf::seconds(0.5f)) {
				show_cursor = !show_cursor;
				text_effect_time = sf::Time::Zero;
			}
			TextBox_Name_server.setString((show_cursor ? anim + ">" : anim + "<") + Name_server_cur);
			window.draw(TextBox_Name_server);
		}

		//------------------------------------------------------------

		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);
		window.draw(menu4);
		window.draw(TextBox_Name);
		window.draw(TextBox_points);
		window.draw(TextBox_wins);
		window.display();
		window.clear();


		
		if (waiting_ready > 0) {
			if (clock_ready.getElapsedTime().asSeconds() >= 1) {
				string answer = "";
				answer = (string)new_cmd(ath.ip, ath.port, "0000000|check_freedoom|" + ath.Login + "|" + ath.Password + "|" + ath.name_server);
				std::vector<string> ss = split(answer,"-");
				if (ss[0] == '0') {
					answer = "";
					if (waiting_ready == 1) {
						answer = new_cmd(ath.ip, ath.port, "0000000|get_user|" + ath.Login + "|" + ath.Password + "|" + ath.name_server + "|2");
						ath.whomai = -1;
					}
					if (waiting_ready == 2) {
						answer = new_cmd(ath.ip, ath.port, "0000000|get_user|" + ath.Login + "|" + ath.Password + "|" + ath.name_server + "|1");
						ath.whomai = 1;
					}
					std::vector<string> ans;

					ans= split(answer, "-");
					//for (auto i = ans.begin(); i != ans.end(); ++i)
					//	std::cout << '[' << *i << ']';
					//std::cout << "\n";

					ans = split(ans[0], "=");
					ath.Login_user2 = ans[0];
					ath.ip_user2 = ans[1];
					ath.port_user2 = ans[2];
					//std::cout << "Login_user2=" << ans[0] << "\n";
					//std::cout << "ip_user2=" << ans[1] << "\n";
					//std::cout << "port_user2=" << ans[2] << "\n";
					waiting_ready = 0;
					//-----
					Name_server = "(starting)";
					anim = "ok";


					isMenu = 1;
					ath.f.conn = true;
					ath.f.menu = true;
					ath.f.exit = false;
					window.close();

				}
				clock_ready.restart();
				//
			}
		}



	}
	return ath;
}
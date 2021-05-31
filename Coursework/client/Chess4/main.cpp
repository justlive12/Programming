#include "include.h"

using namespace sf;
using std::string;
using std::to_string;

string get_str_in_char(char data[1024]) {
	string ans;
	for (int i = 0; i < 1024; i++)
		ans.push_back(data[i]);
	return ans;
}

string new_cmd(string s_ip, string s_p, string data) {
	int accept = 0;

	std::vector<sf::TcpSocket*> clients;
	sf::TcpSocket socket;

	sf::TcpListener listener;
	listener.setBlocking(false);


	sf::SocketSelector selector;

	const std::string address = s_ip;
	const int port = atoi(s_p.c_str());

	if (socket.connect(address, port) == sf::Socket::Done) {
		std::cout << "Connected to the server" << std::endl;
	}
	selector.add(socket);

	sf::Packet packet;
	packet << data;
	socket.send(packet);
	packet.clear();

	char data1[2048];
	sf::Packet packet2;


	sf::Clock clock, pause;
	float ftime = clock.getElapsedTime().asSeconds(); 
	clock.restart();


	std::size_t received;
	socket.receive(data1, sizeof(data1), received);
	string ans = get_str_in_char(data1);




	return ans;
}
int check_authorisation(string s_ip, string s_p, string data) {
	int accept = 0;

	std::vector<sf::TcpSocket*> clients;
	sf::TcpSocket socket;

	sf::TcpListener listener;
	listener.setBlocking(false);


	sf::SocketSelector selector;

	const std::string address = s_ip;
	const int port = atoi(s_p.c_str());

	if (socket.connect(address, port) == sf::Socket::Done) {
		std::cout << "Connected to the server" << std::endl;
	}
	selector.add(socket);

	sf::Packet packet;
	packet << data;
	socket.send(packet);
	packet.clear();

	char data1[2048];
	sf::Packet packet2;


	sf::Clock clock, pause;
	float ftime = clock.getElapsedTime().asSeconds(); 
	clock.restart();


	std::size_t received;
	socket.receive(data1, sizeof(data1), received);
	//std::cout << "data1:" << data1 << "\n";
	string ans = get_str_in_char(data1);
	//std::cout << "Message:" << ans << "\n";

	accept = string(data1)[0] - '0';
	//std::cout << "accept:" << accept << "\n";



	if (accept == 1)
		return 1;

	return 0;
}

std::vector<string> split(const string& str, const string& delim){
	std::vector<string> tokens;
	size_t prev = 0, pos = 0;
	do{
		pos = str.find(delim, prev);
		if (pos == string::npos) pos = str.length();
		string token = str.substr(prev, pos - prev);
		if (!token.empty()) tokens.push_back(token);
		prev = pos + delim.length();
	} while (pos < str.length() && prev < str.length());
	return tokens;
}

string repl(string data, string sub) {
	int i = 0;
	while (data[i] != NULL) {
		if (data[i] == sub) {
			data.erase(i, 1);
			if ((i - 1) >= 0) i--;
		}
		else i++;
	}
	return data;
}

string listen_cmd(string s_ip, string s_p, float hm) {
	sf::TcpListener listener;


	const std::string Address = s_ip;
	const int Port = atoi(s_p.c_str());
	listener.listen(Port);
	sf::TcpSocket client;
	listener.accept(client);


	char data[2048];
	std::size_t received;

	sf::Clock clock_listen;
	clock_listen.restart();
	string ans = "0";
	if (client.receive(data, sizeof(data), received) != sf::Socket::Done) {
		
		return ans;
	}
	else {
		data[received] = '\0';
		ans = std::string(data, data + received);

		const char out[] = "-1-";
		client.send(out, sizeof(out));
	}
	client.disconnect();
	listener.close();


	return ans;
}

void win_end(RenderWindow& window1,string Statistic) {

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

	sf::Text TextBox_Statistic(Statistic, font, 36);
	TextBox_Statistic.setFillColor(sf::Color::Black);
	TextBox_Statistic.setStyle(sf::Text::Bold | sf::Text::Underlined);
	TextBox_Statistic.setPosition(50, 50);

	
	while (window1.isOpen()) {
		window1.clear(Color(200, 200, 200));
		sf::Event event;
		while (window1.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window1.close();
			if (event.type == sf::Event::KeyPressed)
				if (event.key.code == sf::Keyboard::Escape)
					window1.close();
		}
		TextBox_Statistic.setString(Statistic);
		window1.draw(TextBox_Statistic);
		window1.display();
		window1.clear();
	}
}

int main() {
	setlocale(LC_ALL, "");

	struct Auth ath;
	ath.f.conn = false;
	ath.f.menu = false;
	ath.f.exit = false;
	std::string Statistic;
	while (ath.f.exit == false) {
		if (ath.f.conn == false) {
			RenderWindow window_connect(VideoMode(425, 363), "Chess: Connect");
			window_connect.setFramerateLimit(30);
			Auth at;
			at = Menu_Connect(window_connect, ath);
			ath = at;
		}
		else if (ath.f.menu == false && ath.f.exit == false) {
			RenderWindow window_menu(VideoMode(350, 480), "Chess: Menu");
			window_menu.setFramerateLimit(30);
			Auth at;
			at = Menu(window_menu, ath);
			ath = at;
		}
		else if (ath.f.exit == false) {
			RenderWindow window_game(VideoMode(1250, 900), "Chess: Game");
			window_game.setFramerateLimit(30);
			Auth at;
			if (ath.name_server == "Single")
				at = Game_single(window_game, ath);
			else
				at = Game(window_game, ath);
			ath = at;
			ath.f.menu = false;
		}

		if ((ath.who_win == -1 || ath.who_win == 1)) {
			if (ath.who_win == ath.whomai) {
				string answer = new_cmd(ath.ip, ath.port, "0000000|set_win|" + ath.Login + "|" + ath.Password + "|" + ath.Login);
				//Парсинг 
				std::vector<string> ans = split(answer, "-");
				//Отображение окна статистики игроков
				sf::RenderWindow window1(sf::VideoMode(260, 130), "Chess: end game");
				Statistic = "Win";
				win_end(window1, Statistic);
			}
			else {
				sf::RenderWindow window1(sf::VideoMode(260, 130), "Chess: end game");
				Statistic = "End Game";
				win_end(window1, Statistic);
			}
			ath.who_win = -3;
		}
		
	}

	return 0;
}
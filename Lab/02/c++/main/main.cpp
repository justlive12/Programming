#include "Webhooks.h";
#include <map>

typedef std::map<std::string, std::string> new_Map;

json session_list; 
new_Map session_list_map;
bool help_pressed = false;

json button_help = { { {"title", "Помощь"}, {"payload", json::object()}, {"hide", true} } };
json button_speak = { {"title", "Говори"}, {"payload", json::object()}, {"hide", true} };
json button_silent = { {"title", "Молчать"}, {"payload", json::object()}, {"hide", true} };
json buttons_to_help = {
				{{"title", "Молчать"}, {"payload", json::object()}, {"hide", true}},
				{{"title", "Говори"}, {"payload", json::object()}, {"hide", true}},
				{{"title", "Помощь"}, {"payload", json::object()}, {"hide", true}},
				{{"title", "Добавить в корзину"}, {"payload", json::object()}, {"hide", true}},
				{{"title", "Удалить из корзины"}, {"payload", json::object()}, {"hide", true}},
				{{"title", "Что в корзине"}, {"payload", json::object()}, {"hide", true}},
				{{"title", "Сумма"}, {"payload", json::object()}, {"hide", true}},
				{{"title", "Покупка завершена"}, {"payload", json::object()}, {"hide", true}},
				{{"title", "Выход"}, {"payload", json::object()}, {"hide", true}}
};

void webhooks_resp(std::string user_id, json cart) {
	json j_cart = json::array(); 

	for (std::string item : cart) { 
		std::string sep = u8R"( )";
		std::string temp; 
		size_t sep_size = sep.length();
		json jcart_temp = json::array();
		while (true) {
			temp = item.substr(0, item.find(sep)); 
			if (temp.size() != 0) {
				jcart_temp.push_back(temp); 
			}
			if (temp.size() == item.size()) { 
				break;
			}
			else {
				item = item.substr(temp.size() + sep_size);
			}
		}

		j_cart.push_back({ {"item",jcart_temp[0]}, {"price",jcart_temp[1]} });
	}

	json response = {
		{"user_id", user_id},
		{"check", j_cart}
	};

	for (std::string link : cache) { 
		findAndRepl(link, "https://", "http://"); 

		const int http_protocol_size = 7;

		int index = link.find('/', http_protocol_size);

		if (index == std::string::npos)
		{
			link.push_back('/');
		}

		Client cli(link.substr(0, index).c_str());
		cli.Post(link.substr(index, std::string::npos).c_str(), response.dump(), "application/json; charset=UTF-8");
	}
}


json gen_response(const std::string& text,
	const std::string& tts,
	const json buttons,
	const std::string session_id,
	bool end_session = false
)
{
	json response = {
		{"response", {
			{"buttons", buttons},
			{"end_session", end_session}
		}},
		{"version", "1.0"}
	};

	if (text != "")
	{
		response["response"]["text"] = text;
	}

	if (!session_id.empty() && end_session == false) {
		if (session_list[session_id]["speak"])
		{
			if (tts != "")
			{
				response["response"]["tts"] = tts;
			}
			if (!session_list[session_id]["help"]) {
				response["response"]["buttons"].push_back(button_silent);
			}
		}
		else if (!session_list[session_id]["speak"] && !session_list[session_id]["help"])
		{
			response["response"]["buttons"].push_back(button_speak);
		}
	}

	return response;
}

void request_processing(const Request& req, Response& res) {
	json j = json::parse(req.body); 
	json answer; 

	std::string session_id = j["session"]["session_id"];

	if (j["session"]["new"]) {
		std::string text = u8R"(Здравствуйте! Я помогу вам с покупками.)";
		

		session_list_map.emplace(session_id, "1");
		session_list[session_id] = json::object();
		session_list[session_id]["speak"] = true;
		session_list[session_id]["help"] = false;
		session_list[session_id]["sum"] = "0";
		session_list[session_id]["cart"] = json::array();

		answer = gen_response(text, text, button_help, session_id);
		res.set_content(answer.dump(), "text/json; charset=UTF-8");
	}
	else {
		bool breaking = true;
		for (auto session : session_list_map)
		{
			if (session.first == session_id)
			{
				breaking = false;
			}
		}
		if (breaking) {
			std::string text = u8R"(Ошибка, данные не корректны. Попробуйте еще раз.)";
			answer = gen_response(text, text, button_help, session_id, true);
			res.set_content(answer.dump(), "text/json; charset=UTF-8");
		}
		if (j["request"]["nlu"]["tokens"][0] == u8"молчать") {
			if (!session_list[session_id]["help"]) {
				session_list[session_id]["speak"] = false;
				std::string text = u8R"(Озвучка сообщений отключена)";
				answer = gen_response(text, text, button_help, session_id);
				res.set_content(answer.dump(), "text/json; charset=UTF-8");
			}
			else {
				std::string text = u8R"(Вызовите эту команду чтобы отключить озвучку сообщений. О чем еще рассказать?)";
				answer = gen_response(text, text, buttons_to_help, session_id);
				res.set_content(answer.dump(), "text/json; charset=UTF-8");
			}
		}
		else if (j["request"]["nlu"]["tokens"][0] == u8"помощь") {
			if (!session_list[session_id]["help"]) {
				session_list[session_id]["help"] = true;
				std::string text = u8R"(Корзина. Поможет организовать покупки.
					Помощь. Расскажет как этим пользоваться.
					Говорить/Молчать. Управляют озвучиванием сообщений.
					О чём рассказать подробнее?)";
				answer = gen_response(text, text, buttons_to_help, session_id);
				res.set_content(answer.dump(), "text/json; charset=UTF-8");
			}
			else {
				std::string text = u8R"(Помощь расскажет как пользоваться данным навыком. О чем еще рассказать?)";
				answer = gen_response(text, text, buttons_to_help, session_id);
				res.set_content(answer.dump(), "text/json; charset=UTF-8");
			}
		}
		else if (j["request"]["nlu"]["tokens"][0] == u8"говори") {
			if (!session_list[session_id]["help"]) {
				session_list[session_id]["speak"] = true;
				std::string text = u8R"(Озвучка сообщений включена)";
				answer = gen_response(text, text, button_help, session_id);
				res.set_content(answer.dump(), "text/json; charset=UTF-8");
			}
			else {
				std::string text = u8R"(Вызовите эту команду чтобы включить озвучку сообщений. О чем еще рассказать?)";
				answer = gen_response(text, text, buttons_to_help, session_id);
				res.set_content(answer.dump(), "text/json; charset=UTF-8");
			}
		}
		else if (j["request"]["nlu"]["tokens"][0] == u8"покупка") {
			if (!session_list[session_id]["help"]) {
				std::string text = u8R"(Заходите ещё)";
				webhooks_resp(j["session"]["user"]["user_id"], session_list[session_id]["cart"]);
				
				json arr = json::object(); 
				
				for (auto session_old = session_list_map.begin(); session_old != session_list_map.end();)
				{
					if (session_old->first == session_id)
					{
						session_old = session_list_map.erase(session_old);
					}
					else if (session_id != session_old->first) {
						arr.push_back(session_list);
					}
					else {
						++session_old;
					}
				}
				session_list = arr;
				answer = gen_response(text, text, button_help, session_id, true);
				res.set_content(answer.dump(), "text/json; charset=UTF-8");
			}
			else {
				std::string text = u8R"(Эта команда завершает покупку. О чем еще рассказать?)";
				answer = gen_response(text, text, buttons_to_help, session_id);
				res.set_content(answer.dump(), "text/json; charset=UTF-8");
			}
		}
		else if (j["request"]["nlu"]["tokens"][0] == u8"что") {
			if (!session_list[session_id]["help"]) {
				std::string text;
				for (auto item_old : session_list[session_id]["cart"]) {
					text += item_old;
					text += "\n";
				}
				if (text.empty()) {
					text = u8R"(Корзина пуста, Вы ничего не добавили)";
				}
				answer = gen_response(text, text, button_help, session_id);
				res.set_content(answer.dump(), "text/json; charset=UTF-8");
			}
			else {
				std::string text = u8R"(Вызовите эту команду чтобы узнать содержимое Вашей корзины. О чем еще рассказать?)";
				answer = gen_response(text, text, buttons_to_help, session_id);
				res.set_content(answer.dump(), "text/json; charset=UTF-8");
			}
		}
		else if (j["request"]["nlu"]["tokens"][0] == u8"добавить") {
			if (!session_list[session_id]["help"]) {
				std::string good_name = j["request"]["nlu"]["tokens"][3];
				std::string good_price = j["request"]["nlu"]["tokens"][4];
				std::string good_val = j["request"]["nlu"]["tokens"][5];
				std::string good = good_name + " " + good_price + " " + good_val;

				session_list[session_id]["cart"].push_back(good);

				std::string s = session_list[session_id]["sum"];
				int a = std::stoi(s);
				int i = std::stoi(good_price);
				session_list[session_id]["sum"] = std::to_string(a + i);

				std::string text = u8R"(Ок)";
				answer = gen_response(text, text, button_help, session_id);
				res.set_content(answer.dump(), "text/json; charset=UTF-8");
			}
			else {
				std::string text = u8R"(Вызовите эту команду чтобы добавить товар в корзину (шаблон: Добавить в корзину "товар" "цена"). О чем еще рассказать?)";
				answer = gen_response(text, text, buttons_to_help, session_id);
				res.set_content(answer.dump(), "text/json; charset=UTF-8");
			}
		}
		else if (j["request"]["nlu"]["tokens"][0] == u8"удалить") {
		if (!session_list[session_id]["help"]) {
			std::string item_name = j["request"]["nlu"]["tokens"][3];
			std::string item_price = j["request"]["nlu"]["tokens"][4];
			std::string item_val = j["request"]["nlu"]["tokens"][5];
			std::string item = item_name + " " + item_price + " " + item_val;
			bool exists = false;


			json arr = json::array(); 
			for (auto item_old : session_list[session_id]["cart"]) {
				if (item != item_old) {
					arr.push_back(item_old);
				}
				else {
					exists = true; 
				}
			}
			session_list[session_id]["cart"] = arr;

			std::string s = session_list[session_id]["sum"];
			int a = std::stoi(s);
			int i = std::stoi(item_price);
			session_list[session_id]["sum"] = std::to_string(a - i);
			std::string text;
			if (exists) {
				text = u8R"(Удалил)";
			}
			else
			{
				text = u8R"(Такого продукта нет)";
			}

			answer = gen_response(text, text, button_help, session_id);
			res.set_content(answer.dump(), "text/json; charset=UTF-8");
		}
			else {
				std::string text = u8R"(Вызовите эту команду чтобы удалить товар из корзины (шаблон: Удалить из корзины "товар" "цена"). О чем еще рассказать?)";
				answer = gen_response(text, text, buttons_to_help, session_id);
				res.set_content(answer.dump(), "text/json; charset=UTF-8");
			}
		}
		else if (j["request"]["nlu"]["tokens"][0] == u8"очистить") {
			if (!session_list[session_id]["help"]) {
				session_list[session_id]["cart"] = json::array();
				std::string text = u8R"(Корзина очищена)";
				session_list[session_id]["sum"] = "0";
				answer = gen_response(text, text, button_help, session_id);
				res.set_content(answer.dump(), "text/json; charset=UTF-8");
			}
			else {
				std::string text = u8R"(Вызовите эту команду для очистки корзину. О чем еще рассказать?)";
				answer = gen_response(text, text, buttons_to_help, session_id);
				res.set_content(answer.dump(), "text/json; charset=UTF-8");
			}
		}
		else if (j["request"]["nlu"]["tokens"][0] == u8"сумма") {
			if (!session_list[session_id]["help"]) {
				std::string s = session_list[session_id]["sum"];
				std::string text = u8R"(Сумма Вашей покупки )" + s + u8R"( рублей)";
				answer = gen_response(text, text, button_help, session_id);
				res.set_content(answer.dump(), "text/json; charset=UTF-8");
			}
			else {
				std::string text = u8R"(Вызови эту команду чтобы узнать сумму Вашей покупки. О чем еще рассказать?)";
				answer = gen_response(text, text, buttons_to_help, session_id);
				res.set_content(answer.dump(), "text/json; charset=UTF-8");
			}
		}
		else if (j["request"]["nlu"]["tokens"][0] == u8"выход") {
			session_list[session_id]["help"] = false;
			std::string text = u8R"(Обращайтесь еще)";
			answer = gen_response(text, text, button_help, session_id);
			res.set_content(answer.dump(), "text/json; charset=UTF-8");
		}
		else {
			std::string text = u8R"(Не могу понять команду, попробуйте еще)";
			answer = gen_response(text, text, button_help, session_id);
			res.set_content(answer.dump(), "text/json; charset=UTF-8");
		}
	}
}

void gen_response_webhooks(const Request& req, Response& res) {

	std::string template_file_name = "template.html";
	std::ifstream template_file(template_file_name);
	std::string template_str;

	if (template_file.is_open())
	{
		getline(template_file, template_str, '\0');
		template_file.close();
	}
	else
	{
		std::cout << "Error open file template.html";
	}

	if (cache.empty()) {
		findAndRepl(template_str, "{webhooks_list}", "");
	}
	else {
		std::string template_file_name = "template_block.html";
		std::ifstream template_file_block(template_file_name);
		std::string template_block;
		std::string temp;

		for (int i = 0; i < cache.size(); i++) {
			if (template_file_block.is_open())
			{
				getline(template_file_block, template_block, '\0');
				temp = template_block;
			}
			else {
				std::cout << "Error open file template_block.html";
				break;
			}
			findAndRepl(temp, "{Webhook URL}", cache[i]);

			findAndRepl(template_str, "{webhooks_list}", temp);
		}
		template_file_block.close();
		findAndRepl(template_str, "{webhooks_list}", "");
	}
	res.set_content(template_str, "text/html");

}

void gen_response_webhooks_post(const Request& req, Response& res) {
	if (req.has_param("del")) {
		auto val = req.get_param_value("del");
		update_conf("del", val);
	}
	else if (req.has_param("set")) {
		auto val = req.get_param_value("set");
		update_conf("set", val);
	}
	else {
		std::cout << "Post request error";
	}
	gen_response_webhooks(req, res);
}

int main() {
	Server svr;
	check_conf();

	svr.Post("/", request_processing);
	svr.Get("/webhooks", gen_response_webhooks);
	svr.Post("/webhooks", gen_response_webhooks_post);
	std::cout << "Start server... OK\n";
	svr.listen("localhost", 1234);
}




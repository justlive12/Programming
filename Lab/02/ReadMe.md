<p align="center">МИНИСТЕРСТВО НАУКИ  И ВЫСШЕГО ОБРАЗОВАНИЯ РОССИЙСКОЙ ФЕДЕРАЦИИ<br>
Федеральное государственное автономное образовательное учреждение высшего образования<br>
"КРЫМСКИЙ ФЕДЕРАЛЬНЫЙ УНИВЕРСИТЕТ им. В. И. ВЕРНАДСКОГО"<br>
ФИЗИКО-ТЕХНИЧЕСКИЙ ИНСТИТУТ<br>
Кафедра компьютерной инженерии и моделирования</p>
<br>
<h3 align="center">Отчёт по лабораторной работе № 2<br> по дисциплине "Программирование"</h3>
<br><br>
<p>студента 1 курса группы ПИ-б-о-201(1)<br>
Ильясов Эмир Шухратович<br>
направления подготовки 09.03.04 "Программная инженерия"</p>
<br><br>
<table>
<tr><td>Научный руководитель<br> старший преподаватель кафедры<br> компьютерной инженерии и моделирования</td>
<td>(оценка)</td>
<td>Чабанов В.В.</td>
</tr>
</table>
<br><br>
<p align="center">Симферополь, 2020</p>
<hr>

# Лабораторная работа №2 Алиса
**Цель работы:** 
1.  Получить представления о структуре post-запроса;
2.  Изучить webhooks как метод взаимодействия web-приложений;

**Постановка задачи:**
1.  Разработать и зарегистрировать навык для Алисы на сервисе Яндекс.Диалоги;
2.  В качестве backend-a для навыка реализовать приложение на языке С++ выполняющее следующие функции:
    1.  Составление продуктовой корзины:
        -   Добавление продукта в корзину;
        -   Удаление продукта из корзины;
        -   Очистка корзины;
        -   Вывод списка товаров в корзине;
        -   Подсчёт стоимости товаров в корзине.
    2.  Вывод справочной информации по навыку;
    3.  Регистрацию webhook-ов сторонних сервисов;
    4.  Отправку данных на сторонние сервисы.
3.  В качестве стороннего сервиса реализовать приложение на языке Python выполняющее следующие функции:
    1.  Ожидание данных о покупке;
    2.  Сохранение поступивших данных в excel-документ.

## Выполнение работы

### 1. Настройка
В самом начале переходим на сервис Яндекс.Диалоги. На главной странице нажмимаем кнопку Консоль или Создать навык, после чего попадаем на dashboard со всеми созданными навыками. Затем нажимаем кнопку "Создать диалог", а далее "Навык в Алисе", после чего попадем на страницу настройки навыка; Далее заполняем поля формы (рисунок 1) в соответствии с документацией и опубликовываем настройки диалога.

![](./images/01.png)
<p align="center">
Рис. 1. Страница настроек навыка
</p>

### 2. Корзина
Корзина использует сессионные данные для хранения выбранных пользователем названий и цен товаров. У корзины есть такие команды (рисунок 2), как:
	1) "Добавить в корзину" добавляет в корзину название и его цену;
	2) "Удалить из корзины" -  убирает из корзины указанный товар;
	3) "Очистить корзину" удоляет все товары из корзины;  
	4) "Что в корзине" - выводит все товары в формате: Название и цена;
	5) "Сумма" - сообщает суммарную стоимость всех товаров пользователю;
	6) "Покупка завершина" - завершает сессию.

![](./images/02.png)
<p align="center">
Рис. 2. Демонстрация работ команд корзины
</p>

### 3. Помощь
Если пользователь нажал кнопку "помощь", то режим навыка переключается в режим помощи, а затем перечисляются всевозможные навыки и их краткое описание. Для того чтобы отобразить детальную справку по команде, необходимо ввести необходимую команду или нажать на соответствующую ей кнопку (рисунок 3).

![](./images/03.png)
<p align="center">
Рис. 3. Демонстрация функционала функции "Помощь"
</p>

### 4. Управление списком WebHook-служб
При подключении к "/webhooks" на сервере, программа автоматически изменяет локальный файл "template.html" и редактирует соответствующие поля с блоками URL-адресов, подставляя в каждый из них информацию из файла "template_block.html", а затем возвращает браузеру html-документ (рис. 4). При добавлении или удалении соответствующего WebHook-а, браузер посылает POST-запрос на тот же URN серверу. Затем серверное приложение обрабатывает запрос и совершает необходимое действие.

![](./images/04.png)
<p align="center">
Рис. 4. Страница управления webhook-ами
</p>

### 5. Заполнение Excel-файла
Для работы с Excel-документом клиентское приложение использует модуль Openpyxl для Python. Клиент получает с помощью модуля Flask json-строку с сервера. Затем происходит запись данных в буфер, также записывается дата отправки запроса. Буфер очищается, когда количество записей достигнет десяти, а затем записывается в Excel документ.
Ссылка на Excel документ: [python/data.xlsx](./python/data.xlsx)
### 6. Клиентское приложение
Для создания клиентского приложения использовался язык Python, весь исходный код хранится в одном файле. Использовались библиотеки Openpyxl и Flask. Приложение ждет запроса сервера и получает от него данные корзины пользователя и записывает в файл data.xlsx. Исходный код приложения:
```py
from flask import Flask
from flask.globals import request
import openpyxl
import os.path
import datetime

app = Flask(__name__)

pwd = os.path.abspath(os.path.dirname(__file__))

buffer_len = 0
buffer = []


def save_excel():
    global buffer

    writing_to_file  = os.path.join(pwd, 'data.xlsx')

    book = None

    if not os.path.exists(writing_to_file ):
        book = openpyxl.Workbook()
        # headers
        book.active['A1'] = 'N'
        book.active['B1'] = 'User ID'
        book.active['C1'] = 'Datetime'
        book.active['D1'] = 'Item'
        book.active['E1'] = 'Prise'
        book.save(writing_to_file )
    else:
        book = openpyxl.open(writing_to_file )
    sheet = book.active

    max_row = len(sheet['A'])
    nowtime = datetime.datetime.utcnow()

    row = max_row + 1
    for dataset in buffer:
        id = dataset['user_id']
        check = dataset['check']

        for item in check:
            sheet[row][0].value = row - 1
            sheet[row][1].value = id
            sheet[row][2].value = nowtime
            sheet[row][3].value = item['item']
            sheet[row][4].value = item['price']
            row += 1

    book.save(writing_to_file )
    book.close()


@app.route('/', methods=['POST', 'GET'])
def index():
    global buffer

    if request.method == 'POST':

        buffer += [request.json]
        print('req.body:', buffer)
        if (len(buffer) > buffer_len):
            save_excel()
            buffer = []

        return 'OK'

    elif request.method == 'GET':
        return 'Это GET запрос'


if __name__ == '__main__':
    app.run()
```
### 7. Серверное приложение
Для запуска сервера, был использован язык C++. Если приходит запрос на "/webhooks", сервер формирует и отправляет html-страницу со список webhook-ов, если же запрос приходит на "/", сервер формирует и отправляет json-файл с ответными данными на Яндекс.Диалоги. Исходный код приложения:

**main.cpp**
```c++
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
						std::cout << "aaa" << std::endl;
						arr.push_back(session_list);
					}
					else
					{
						++session_old;
					}
				}
				session_list = arr;
				json aaa = session_list_map;
				std::cout << aaa << std::endl;
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
```
**Webhooks.h**
```c++
#pragma once

#include <iostream>
#include <string>
#include <cpp_httplib/httplib.h>
#include <nlohmann/json.hpp>
#include <vector>

using namespace httplib;
using json = nlohmann::json;
std::vector<std::string> cache;
std::vector<std::string> webhooks;


void findAndRepl(std::string& data, std::string toSearch, std::string replStr) {
	size_t pos = data.find(toSearch);
	while (pos != std::string::npos) {
		data.replace(pos, toSearch.size(), replStr);
		pos = data.find(toSearch, pos + replStr.size());
	}
}

void update_conf(std::string param, std::string val) {
	std::string webhooks_file_name = "webhooks.json";
	std::ifstream webhooks_file(webhooks_file_name);
	json j;

	if (webhooks_file.is_open())
	{
		webhooks_file >> j;
		webhooks_file.close();

		if (param == "del") {
			cache.erase(std::remove(cache.begin(), cache.end(), val), cache.end());
		}
		else if (param == "set") {
			cache.push_back(val);
		}
		json j2;
		j2["webhooks"] = cache;
		std::ofstream conf_file(webhooks_file_name);
		conf_file << j2;
		conf_file.close();
	}
	else
	{
		std::cout << "Error open file";
	}
}

void check_conf() {
	std::string webhooks_file_name = "webhooks.json";
	std::ifstream webhooks_file(webhooks_file_name);
	std::cout << "Попытка открыть файл...\n";
	if (webhooks_file.is_open())
	{
		int i = 0;
		std::cout << "Открыл!\n";
		json j = json::parse(webhooks_file);

		for (int i = 0; i < j["webhooks"].size(); i++) {
			cache.push_back(j["webhooks"][i]);
		}
	}
	else
	{
		std::cout << "Не получилось, создаю новый...\n";
		std::ofstream webhooks_file(webhooks_file_name);
		std::string config = R"(
			{
			"webhooks":[]
			})";
		webhooks_file << config;
		webhooks_file.close();
		cache.clear();
	}
}

## Вывод

Все поставленные задачи выполнены, а цель работы достигнута - разработано распределённое клиент-серверное приложение, использующее возможности Yandex.Dialogs для обработки запросов пользователя. Благодаря этому реализовано приложение, выполняющее составление списка продуктов и подсчет суммарной стоимости чека.

В разработке С++-сервера использованы две сторонние библиотеки: `json` и `cpp-httplib`. Python-клиент использует библиотеку `flask` обработки post-запросов.
```
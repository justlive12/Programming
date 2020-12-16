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
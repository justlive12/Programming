from tkinter import *
import json
import requests

def reload_data(event=None):
	try:
		response = requests.get('http://localhost:3000/raw').content.decode("utf8")
        
		inf = json.loads(response)
		desccription.config(text=str(inf["description"]))
		temp.config(text=str(inf["temp"]) + "°C")
	except requests.exceptions.ConnectionError:
		print('Error')
    
    
    
root = Tk()
root.title("Погода")
root.bind("<Button-3>", reload_data)

yellow = "#ffb84d"
white = "#ffffff"
wid = 180
heigh = 60

header =    Frame(root, bg=yellow, width=wid, height=heigh)
content = Frame(root, bg=white,  width=wid, height=heigh)
footer = Frame(root, bg=yellow, width=wid, height=heigh)

header.pack(side=TOP, fill=X)
content.pack(expand=True, fill=BOTH)
footer.pack(side=BOTTOM, fill=X)

city_name = Label(header, font=("Calibri Bold", 14), text="Симферополь", bg=yellow)
desccription = Label(header, font=("Calibri", 12), bg=yellow)
temp = Label(content, font=("Calibri", 52), bg=white)

city_name.pack(pady=0)
desccription.pack(pady=0)
temp.pack(expand=True)

reload_data()
root.mainloop()
from flask import Flask, render_template, request

app = Flask(__name__)

@app.route("/")
def EasyModepage():
    score_arr = []
    with open("res_easy", "r", encoding='utf-8') as f:
        for elem in f:
            score_arr.append(elem.strip())
    dic = {}
    for i, elem in enumerate(score_arr):
        dic[f"n{i + 1}n"] = elem.split(",")[0].split(":")[1].strip()
        dic[f"n{i + 1}"] = float(elem.split('!')[1])
        
    return render_template("easymode.html", dic=dic)

@app.route("/HardMode")
def HardModepage():
    score_arr = []
    with open("res_hard", "r", encoding='utf-8') as f:
        for elem in f:
            score_arr.append(elem.strip())
    dic = {}
    for i, elem in enumerate(score_arr):
        dic[f"n{i + 1}n"] = elem.split(",")[0].split(":")[1].strip()
        dic[f"n{i + 1}"] = float(elem.split('!')[1])
        
    return render_template("hardmode.html", dic=dic)



app.run()
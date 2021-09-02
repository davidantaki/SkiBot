# Flask app backend

from flask import Flask, render_template
import waxing_control

waxing_control.setup()

app = Flask(__name__)

@app.route("/")
def index():
    return render_template('index.html')

@app.route("/<moveDir>")
def move(moveDir):
    if moveDir == "moveleft":
        waxing_control.moveLeft()
    if moveDir == "moveright":
        waxing_control.moveRight()
    return render_template('index.html')

if __name__ == '__main__':
    app.run(debug=False, port=5000, host='0.0.0.0')
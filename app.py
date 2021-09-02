# Flask app backend

from flask import Flask, render_template, send_from_directory
import waxing_control

waxing_control.setup()

app = Flask(__name__, static_url_path='', static_folder='frontend/build')

@app.route("/")
def index():
    return send_from_directory(app.static_folder, 'index.html')

@app.route("/<moveDir>")
def move(moveDir):
    if moveDir == "moveleft":
        waxing_control.moveLeft()
    if moveDir == "moveright":
        waxing_control.moveRight()
    if moveDir == "movestop":
        waxing_control.moveStop()

    return send_from_directory(app.static_folder, 'index.html')

if __name__ == '__main__':
    app.run(debug=False, port=5000, host='0.0.0.0')
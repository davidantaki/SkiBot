# Flask app backend

from flask import Flask, send_from_directory, request
import waxing_control

waxing_control.setup()

app = Flask(__name__, static_url_path='', static_folder='frontend/build')

@app.route("/")
def index():
    return send_from_directory(app.static_folder, 'index.html')

@app.route("/move", methods=['POST'])
def move():
    if request.method == 'POST':
        print(request.json)
        if request.json['moveDir'] == "moveLeft":
            waxing_control.moveLeft()
        if request.json['moveDir'] == "moveRight":
            waxing_control.moveRight()
        if request.json['moveDir'] == "moveStop":
            waxing_control.moveStop()
        return 'Success'
    else:
        return 'Fail'

if __name__ == '__main__':
    app.run(debug=True, port=5000, host='0.0.0.0')
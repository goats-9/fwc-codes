import flask

led_wrist = 0
led_chop = 0

app = flask.Flask(__name__)
@app.route('/gesture', methods=['GET', 'PUT'])
def status_handler():
    global led_wrist
    global led_chop
    str_chop = "ON"
    str_wrist = "ON"
    if led_chop == 0:
        str_chop = "OFF"
    if led_wrist == 0:
        str_wrist = "OFF"
    if flask.request.method == 'GET':
        return "LED Status:\n\tChop LED: " + str_chop + "\n\tWrist LED: " + str_wrist
    elif flask.request.method == 'PUT':
        temp = flask.request.json['temp']
        return {}

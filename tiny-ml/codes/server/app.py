import flask

payload = {}

app = flask.Flask(__name__)
@app.route('/gesture', methods=['GET', 'POST'])
def status_handler():
    global payload
    if flask.request.method == 'GET':
        return payload
    elif flask.request.method == 'POST':
        payload = flask.request.json
        return {}

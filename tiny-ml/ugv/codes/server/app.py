import flask

payload = {}
k = 0
pid = 0
num_samples = 20
get_payload = {}

app = flask.Flask(__name__)
@app.route('/ugv', methods=['GET', 'POST'])
def status_handler():
    global payload
    global acc_thr
    global k
    global get_payload
    global pid
    global num_samples
    if flask.request.method == 'GET':
        if k >= num_samples:
            get_payload = payload.copy()
            payload.clear()
            pid += 1
            print("pid =", pid)
            get_payload['id'] = pid
            k = 0
        return get_payload
    elif flask.request.method == 'POST':
        if k >= num_samples:
            return {}
        body = flask.request.json
        for ele in body['payload']:
            r, p, y = ele['values']['roll'], ele['values']['pitch'], ele['values']['yaw']
            payload['r'+str(k)], payload['p'+str(k)], payload['y'+str(k)] = r, p, y
            k += 1
            if k >= num_samples:
                break
        return {}

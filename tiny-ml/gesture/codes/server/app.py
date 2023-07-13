import flask

payload = {}
acc_thr = 30.0
k = 0
pid = 0
num_samples = 40
get_payload = {}

app = flask.Flask(__name__)
@app.route('/gesture', methods=['GET', 'POST'])
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
            vx, vy, vz = list(ele['values'].values())
            name = ele['name']
            if bool(payload) == False:
                if name == 'accelerometer':
                    if abs(vx) + abs(vy) + abs(vz) >= acc_thr:
                        print(vx, vy, vz, k)
                        payload['ax0'], payload['ay0'], payload['az0'] = vx, vy, vz
            else:
                if name == 'accelerometer' or name == 'gyroscope':
                    print(vx, vy, vz, k)
                    payload[name[0]+'x'+str(k)], payload[name[0]+'y'+str(k)], payload[name[0]+'z'+str(k)] = vx, vy, vz
                if name == 'gyroscope':
                    k += 1
            if k >= num_samples:
                break
        return {}

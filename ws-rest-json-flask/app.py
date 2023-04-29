
# Based on example at:
# 

from flask import Flask, request, jsonify

app = Flask(__name__)

ddaa = [ ]

@app.route('/ddaa', methods=["GET"])
def get_ddaa():
    return jsonify(ddaa)

@app.route('/ddaa', methods=["POST"])
def add_ddaa():
    if request.is_json:
        da = request.get_json()
        ddaa.append(da)
        return da, 201
    return {"error": "Request must be JSON"}, 415

@app.route('/ddaa', methods=["PUT"])
def update_da():
    if request.is_json:
        da = request.get_json()
        for dai in ddaa:
            if dai["name"] == da["name"]:
               key = da["key"]
               val = da["val"]
               dai["array"][key] = val
        return da, 201
    return {"error": "Request must be JSON"}, 415

@app.route('/ddaa/<name>/<key>', methods=["GET"])
def get_da(name, key):
    found = 0
    for dai in ddaa:
        if dai["name"] == str(name):
           found = 1
    if found == 0:
       return {"error": "name or key not found"}, 415
    return dai, 201

@app.route('/ddaa/<name>/<key>/<value>', methods=["PUT"])
def set_da(name, key, value):
    found = 0
    for dai in ddaa:
        if dai["name"] == str(name):
           dai["array"][str(key)] = str(value)
           found = 1
    if found == 0:
       return {"error": "name or key not found"}, 415
    return dai, 201


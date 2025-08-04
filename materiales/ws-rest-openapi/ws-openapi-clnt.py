

import requests

def add_item(key, value):
    http_url = "http://127.0.0.1:8000/items/" + str(key)
    http_headers = { 'Content-type': 'application/json', 'accept': 'application/json' }
    r = requests.put(url=http_url, json=value, headers=http_headers)
    return r.text

key   = 10
value = { "name": "name", "weight":0.0 }
r = add_item(key,value)
print(r)


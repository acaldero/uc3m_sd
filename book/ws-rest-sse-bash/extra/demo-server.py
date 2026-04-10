from flask import Flask, Response
import time

app = Flask(__name__)

@app.route("/")
def sse():
    def gen():
        while 1:
            yield f"data: {{'time': '{time.ctime()}'}}\n\n"
            time.sleep(1)
    return Response(gen(), mimetype="text/event-stream")

app.run()


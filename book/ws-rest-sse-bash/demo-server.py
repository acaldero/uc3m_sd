from   flask import Flask, Response
import time

app = Flask(__name__)

cors_headers = {
    "Access-Control-Allow-Origin": "*",
    "Cache-Control": "no-cache",
    "X-Accel-Buffering": "no"
}

@app.route("/")
def sse():
    def gen():
        while 1:
            yield f"data: {{'time': '{time.ctime()}'}}\n\n"
            time.sleep(1)
    return Response(gen(), mimetype="text/event-stream", headers=cors_headers)

app.run(host="0.0.0.0", port=5000, threaded=True)


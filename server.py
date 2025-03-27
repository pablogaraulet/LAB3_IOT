from flask import Flask, request

app = Flask(__name__)

@app.route("/")
def receive_data():
    temp = request.args.get("temp")
    hum = request.args.get("hum")

    print(f"Temperature: {temp} °C")
    print(f"Humidity: {hum} %")

    return f"We received -> Temperature: {temp} °C, Humidity: {hum} %"

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000)


from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/data', methods=['POST'])
def receive_data():
    # Ambil data JSON dari request
    data = request.get_json()
    # Ambil nilai temperature dan humidity dari data JSON
    temperature = data.get('temperature')
    humidity = data.get('humidity')
    
    # Buat response JSON
    response = {
        'status': 'success',
        'received': {
            'temperature': temperature,
            'humidity': humidity
        }
    }
    
    # Return response sebagai JSON
    return jsonify(response)

if __name__ == '__main__':
    # Jalankan Flask server pada host 0.0.0.0 dan port 5000
    app.run(host='0.0.0.0', port=5000)
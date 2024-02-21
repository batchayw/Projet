from flask import Flask, request, jsonify
import mysql.connector
import os
import time
import json
import paho.mqtt.client as mqtt

app = Flask(__name__)

# Mysql configuration
db_config = {
    'host': os.environ.get('DB_HOST', 'mysql'),
    'user': os.environ.get('DB_USER', 'app_user'),
    'password': os.environ.get('DB_PASSWORD', 'app_password'),
    'database': os.environ.get('DB_DATABASE', 'init'),
}

# Wait for MySQL to be ready before proceeding
def wait_for_mysql():
    max_retries = 30
    retries = 0
    while retries < max_retries:
        try:
            # Attempt to connect to MySQL
            mysql.connector.connect(**db_config)
            print("Connected to MySQL!")
            return
        except mysql.connector.Error as err:
            retries += 1
            print(f"Error connecting to MySQL: {err}")
            time.sleep(1)

    # If we reach here, we couldn't connect to MySQL
    raise Exception("Unable to connect to MySQL. Exiting.")

# MQTT configuration
mqtt_broker_host = os.environ.get('MQTT_BROKER_HOST', 'jorammq')
mqtt_broker_port = int(os.environ.get('MQTT_BROKER_PORT', 1883))
mqtt_topic = 'LIG'

# port
port = int(os.environ.get('APP_PORT', 5000))

def on_publish(client, userdata, mid):
    print(f"Message Published (mid={mid})")

mqtt_client = mqtt.Client()
mqtt_client.on_publish = on_publish

# Wait for MySQL to be ready before proceeding
wait_for_mysql()

# Mysql connection
conn = mysql.connector.connect(**db_config)
cursor = conn.cursor()

@app.route('/get_info', methods=['POST'])
def get_info():
    data = request.json
    tel_number = data['tel_number']
    
    # Query (ask) the database
    query = "SELECT * FROM contacts WHERE tel_number = %s"
    cursor.execute(query, (tel_number,))
    result = cursor.fetchone()
    
    if result:
        # Convert result to dictionary for JSON response
        result_dict = {
            'name': result[1],
            'address': result[2],
            'email': result[3],
            'profession': result[4],
        }
        result_json_str = json.dumps(result_dict)
        
        # Publish the JSON result to MQTT topic with QoS=1
        try:
            mqtt_client.connect(mqtt_broker_host, mqtt_broker_port)
            mqtt_client.publish(mqtt_topic, result_json_str, qos=1)
        except Exception as e:
            print(f"Error publishing to MQTT: {e}")

        return jsonify(result_dict)
    else:
        return jsonify({'error': 'contact not exist'})

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)

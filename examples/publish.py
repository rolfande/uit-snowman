# Script to publish message to the mqtt broker
# Usage: python publish.py <topic> <message>
# Example: python publish.py "test" "Hello World"

import paho.mqtt.client as mqtt
import sys

# Define Variables
MQTT_HOST = "<broker_ip>"
MQTT_PORT = 1883
MQTT_KEEPALIVE_INTERVAL = 45
MQTT_TOPIC = sys.argv[1]
MQTT_MSG = sys.argv[2]

# Define on_publish event function
def on_publish(client, userdata, mid):
    print("Message Published...")
    pass

# Initiate MQTT Client
mqttc = mqtt.Client()

# Register publish callback function
mqttc.on_publish = on_publish

# Define MQTT username and password
MQTT_USERNAME = "<username>"
MQTT_PASSWORD = "<password>"

# Set username and password
mqttc.username_pw_set(MQTT_USERNAME, MQTT_PASSWORD)

# Connect with MQTT Broker
mqttc.connect(MQTT_HOST, MQTT_PORT, MQTT_KEEPALIVE_INTERVAL)

# Publish message to MQTT Topic
mqttc.publish(MQTT_TOPIC,MQTT_MSG)

# Disconnect from MQTT_Broker
mqttc.disconnect()
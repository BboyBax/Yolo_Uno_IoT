print("Hello Core IOT")
import paho.mqtt.client as mqttclient
import time
import json

BROKER_ADDRESS = "app.coreiot.io"
PORT = 1883
ACCESS_TOKEN = "hts221105"
ACCESS_USERNAME = "hts221105"

def subscribed(client, userdata, mid, granted_qos):
    print("Subscribed...")


def recv_message(client, userdata, message):
    print("Received: ", message.payload.decode("utf-8"))
    temp_data = {'value': True}
    try:
        jsonobj = json.loads(message.payload)
        if jsonobj['method'] == "setValue":
            temp_data['value'] = jsonobj['params']
            client.publish('v1/devices/me/attributes', json.dumps(temp_data), 1)
    except:
        pass


def connected(client, usedata, flags, rc):
    if rc == 0:
        print("Connected successfully!!")
        client.subscribe("v1/devices/me/rpc/request/+")
    else:
        print("Connection is failed")


client = mqttclient.Client("DEVICE_2")
client.username_pw_set(ACCESS_USERNAME, ACCESS_TOKEN)

client.on_connect = connected
client.connect(BROKER_ADDRESS, 1883)
client.loop_start()

client.on_subscribe = subscribed
client.on_message = recv_message

temp = 32
humi = 66
light_intesity = 100
counter = 0

#H6
long = 106.80633605864662
lat = 10.880018410410052

while True:
    collect_data = {'temperature': temp, 'humidity': humi,
                    'light':light_intesity,
                    'long': long, 'lat': lat}
    temp += 5
    humi += 5
    light_intesity += 5
    client.publish('v1/devices/me/telemetry', json.dumps(collect_data), 1)
    time.sleep(5)
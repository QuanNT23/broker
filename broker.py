import paho.mqtt.client as mqtt

BROKER_ADDRESS = "192.168.1.130"
PORT = 1883

def on_connect(client, userdata, flags, rc):
    print(f"Connected with result code {rc}")
    # Gửi thông điệp sau khi kết nối thành công
    publish_message("home/test", "Hello from the publisher!")

def on_message(client, userdata, message):
    print(f"Message received on {message.topic}: {message.payload.decode()}")

def publish_message(topic, message):
    # Gửi thông điệp đến broker
    client.publish(topic, message)
    print(f"Message published to {topic}: {message}")

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect(BROKER_ADDRESS, PORT)
client.subscribe("home/#")  # Subscribe to all topics under "home/"
print("hihi")
client.loop_forever()

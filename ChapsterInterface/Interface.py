# A python file used to send messages to "Chapster" the chapstick robot, with simple keyboard control
import keyboard
import paho.mqtt.client as mqttClient
import time

Topic = "CHAPSTER"

LastMessage = ''

def main_function():
    message = ''
    if keyboard.is_pressed('up') :
        message = b"\x0B\x01\x32" # Go forwards
    elif keyboard.is_pressed('down') :
        message = b"\x0B\x00\x32" # Go backwards
    elif keyboard.is_pressed('left') :
        message = b"\x0C\x00" # turn CCW
    elif keyboard.is_pressed('right') :
        message = b"\x0C\x01" # turn CW
    elif keyboard.is_pressed('q') :
        message = b"\x10\x01" # elevator up
    elif keyboard.is_pressed('a') :
        message = b"\x10\x00" # elevator down
    elif keyboard.is_pressed('w') :
        message = b"\x0F\x00" # close claw
    elif keyboard.is_pressed('e') :
        message = b"\x0F\x01" # open claw
    elif keyboard.is_pressed('z') :
        message = b"\xA0" # Retrieve command
    elif keyboard.is_pressed('x') :
        message = b"\xA1" # Place command
    else :
        message = b"\x0B\x00\x00" # Stop drivetrain
    
    global LastMessage
    if (LastMessage == message):
        return

    LastMessage = message
    client.publish(Topic, message)
    print("Sent message: (in hex): ", message.hex())

def on_connect(client, userdata, flags, rc):
 
    if rc == 0:
 
        print("Connected to broker")
 
        global connected                #Use global variable
        connected = True                #Signal connection 
 
    else:
 
        print("Connection failed")

connected = False

brokerAddress = "127.0.0.1" # Replace this with broker address
port = 1883

client = mqttClient.Client("PythonChapsterInterface")
client.on_connect = on_connect
client.connect(brokerAddress, port=port)

client.loop_start()

while connected != True:
    time.sleep(0.1)

try:
    while True:
        main_function()

except KeyboardInterrupt:
    client.disconnect()
    client.loop_stop()
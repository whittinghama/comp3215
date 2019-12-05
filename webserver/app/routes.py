import time
import serial
from flask import render_template, request, jsonify
from app import app

#https://blog.miguelgrinberg.com/post/the-flask-mega-tutorial-part-i-hello-world
#https://blog.miguelgrinberg.com/post/the-flask-mega-tutorial-part-ii-templates
#http://www.varesano.net/blog/fabio/serial%20rs232%20connections%20python
#https://pyserial.readthedocs.io/en/latest/pyserial.html

@app.route('/')
@app.route('/index')
def index():
    ser = serial.Serial(
        port= 'COM9',
	baudrate=9600,
	#parity=serial.PARITY_ODD,
        #stopbits=serial.STOPBITS_TWO,
	#bytesize=serial.SEVENBITS
	)
    ser2 = serial.Serial(
        port= 'COM10',
	baudrate=9600,
	#parity=serial.PARITY_ODD,
        #stopbits=serial.STOPBITS_TWO,
	#bytesize=serial.SEVENBITS
	)
    ser.close()
    ser2.close()
    ser.open()
    ser2.open()
    ser.isOpen()
    ser2.isOpen()
    ser.write('66')
    data = ser2.read(2)
    if data == '66':
        ser2.write('20100')
    startup_data = ser.read(5)
    states = str(startup_data[1:5])
    print(startup_data[0])
    print(startup_data[1:5])
    startup = {'host' : startup_data[0], 'startup_state' : startup_data[1:5]}
    
    ser.close()
    ser2.close()
    return render_template('index.html', startup=startup, states=states)
    

@app.route('/buttonpress',methods=['POST'])
def buttonpress():
    button_id=request.args.get('button_id')
    button_state=request.args.get('button_state')
    packet = str(button_id) + str(button_state)
    print(button_id)
    print(button_state)
    ser = serial.Serial(
        port= 'COM9',
	baudrate=9600,
	#parity=serial.PARITY_ODD,
        #stopbits=serial.STOPBITS_TWO,
	#bytesize=serial.SEVENBITS
	)
    ser2 = serial.Serial(
        port= 'COM10',
	baudrate=9600,
	#parity=serial.PARITY_ODD,
        #stopbits=serial.STOPBITS_TWO,
	#bytesize=serial.SEVENBITS
	)
    ser.close()
    ser2.close()
    ser.open()
    ser2.open()
    ser.isOpen()
    ser2.isOpen()
    ser.write(packet)
    out = ''
    #time.sleep(1)
    #while ser.inWaiting() > 0:
    out += ser2.read(2)
    if out != '':
    	print(out)
    ser2.write('1111')
    onlineoffline = ser.read(4)
    print(onlineoffline)
    ser.close()
    ser2.close()
    return jsonify({'reply':'success', 'id' : out[0], 'state' : out[1], 'onlineoffline' : onlineoffline})


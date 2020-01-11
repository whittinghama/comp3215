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
    ser = serial.Serial(port= 'COM8', baudrate=115200)
    #ser.close()
    #ser.open()
    ser.write('CONCHECK' + '\n') #connection check 
    #print('CONCHECK DONE')
    time.sleep(.1)
    ser.write('CONREPLY' + '\n') #connection reply
    #print('CONREPLY DONE')
    time.sleep(.1)
    while(ser.in_waiting != 0):
        line = ser.readline()
        if 'STATE' in line: #look for correct response line and throw away the others
            response = line.split(',')
            host_no = response[1]
            states = response[2]
            #print(host_no)
            #print(states)
            #ser.close()
            startup = {'host' : host_no, 'startup_state' : states}
            return render_template('index.html', startup=startup)

@app.route('/buttonpress',methods=['POST'])
def buttonpress():
    button_id=request.args.get('button_id')
    button_state=request.args.get('button_state')
    #print(button_id)
    #print(button_state)
    if button_state == '1':
        packet = 'LEDON ' + str(button_id) + '\n';
        #print(packet)
    elif button_state == '0':
        packet = 'LEDOFF ' + str(button_id) + '\n';
        #print(packet)
    ser = serial.Serial(port= 'COM8', baudrate=115200)
    ser.close()
    ser.open()
    flag = 1
    ser.write('CONCHECK' + '\n') #connection check 
    time.sleep(.1)
    ser.write('CONREPLY' + '\n') #connection reply
    time.sleep(.1)
    while(ser.in_waiting != 0):
        line = ser.readline()
        #print(line)
        if 'STATE' in line: #look for correct response line and throw away the others
            response = line.split(',')
            states = response[2]
            host = response[1]
            if states[int(button_id) - 1] == '0':
                flag = 0
                print 'OFFLINE NOT ATTEMPTING..'
                #print('dont do it')
            break
    while flag == 1:
        ser.write(packet)
        print 'ATTEMPTING...'
        time.sleep(.1)
        while(ser.in_waiting != 0):
            line = ser.readline()
            #print(line)
            if 'AK' in line:
                flag = 0
                print 'SUCCESS'
                break
        #print(flag)
    ser.close()
    return jsonify({'reply':'success', 'id' : button_id, 'state' : button_state, 'onlineoffline' : states, 'host' : host})




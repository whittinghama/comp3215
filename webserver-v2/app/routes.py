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
        port= 'COM8',
	baudrate=115200,
	#parity=serial.PARITY_ODD,
        #stopbits=serial.STOPBITS_TWO,
	#bytesize=serial.SEVENBITS
	)
    #ser.close()
    #ser.open()
    #ser.isOpen()
    ser.write('CONCHECK' + '\n') #connection check 
    print('CONCHECK DONE')
    time.sleep(.1)
    ser.write('CONREPLY' + '\n') #connection reply
    print('CONREPLY DONE')
    time.sleep(.1)
    while(ser.in_waiting != 0):
        line = ser.readline()
        if 'STATE' in line: #look for correct response line and throw away the others
            response = line.split(',')
            host_no = response[1]
            states = response[2]
            print(host_no)
            print(states)
            #ser.close()
            startup = {'host' : host_no, 'startup_state' : states}
            return render_template('index.html', startup=startup)
                
                    
                
            #print(states[0])
            #print(states[1])
            
    #data = ser2.read(2)
    #if data == '66':
    #    ser2.write('20110')
    #startup_data = ser.read(5)
    #states = str(startup_data[1:5])
    #print(startup_data[0])
    #print(startup_data[1:5])
   #startup = {'host' : startup_data[0], 'startup_state' : startup_data[1:5]}
    
    #ser.close()
    
#, startup=startup, states=states
    

@app.route('/buttonpress',methods=['POST'])
def buttonpress():
    button_id=request.args.get('button_id')
    button_state=request.args.get('button_state')
    #print(button_id)
    #print(button_state)
    if button_state == "1":
        packet = 'LEDON ' + str(button_id) + "\n";
        print(packet)
    elif button_state == "0":
        packet = 'LEDOFF ' + str(button_id) + "\n";
        print(packet)
        
    ser = serial.Serial(
        port= 'COM8',
	baudrate=115200,
	#parity=serial.PARITY_ODD,
        #stopbits=serial.STOPBITS_TWO,
	#bytesize=serial.SEVENBITS
	)
    
    ser.close()
    ser.open()
    ser.isOpen()

    flag = 1
    ser.write('CONCHECK' + '\n') #connection check 
    time.sleep(.1)
    ser.write('CONREPLY' + '\n') #connection reply
    time.sleep(.1)
    while(ser.in_waiting != 0):
        line = ser.readline()
        print(line)
        if 'STATE' in line: #look for correct response line and throw away the others
            response = line.split(',')
            states = response[2]
            host = response[1]
            if states[int(button_id) - 1] == '0':
                flag = 0
                print('dont do it')
            break


    while flag == 1:
        ser.write(packet)
        time.sleep(.1)
        while(ser.in_waiting != 0):
            line = ser.readline()
            print(line)
            if 'AK' in line:
                flag = 0
                break
        ser.close()
        ser.open()
        print(flag)
        
    #time.sleep(1)
    #ser.write(packet)
    #out = ''
    #time.sleep(1)
    #while ser.inWaiting() > 0:
    #out += ser2.read(2)
    #if out != '':
    #	print(out)
    #ser2.write('1111')
    #onlineoffline = ser.readline()
    #print(onlineoffline)
    #onlineoffline2 = ser.readline()
    #print(onlineoffline2)
    ser.close()
    #ser2.close()
    return jsonify({'reply':'success', 'id' : button_id, 'state' : button_state, 'onlineoffline' : states, 'host' : host})


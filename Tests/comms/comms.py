import threading
from datetime import datetime
import time

def handle_comms():
    import serial
    import struct

    port = '/dev/ttyACM0'
    baudrate = 115200
    timeout = 30

    connected = True

    try:
        ser = serial.Serial(port, baudrate=baudrate, timeout = timeout, write_timeout= 1)
        connected = True
        ser.flushInput()
        ser.flushOutput()
    except serial.SerialException:
        print("Port not found or can not be configured")
        connected = False

    MAX_BUFFER = 255

    buffer_start = 0
    buffer_end = 0
    buffer_size = 0
    buffer = [0]*MAX_BUFFER

    INCOMING_BYTES = 14

    data_pointer = 0
    data = [0] * INCOMING_BYTES

    need_sync = True

    linear = [0.4, 0.0, 0.0]
    angular = [0, 0, 0.1]

    while connected:
        roomba_control_vector = linear + angular
        ser.write(b'\xff')
        for val in roomba_control_vector:
            ser.write(struct.pack('f', val))


        if ser.in_waiting and buffer_size < MAX_BUFFER:
            temp = ser.read()
            #print(temp)
            if not need_sync:
                for i in range(INCOMING_BYTES*4):
                    if temp == b'\xff': break
                    buffer[buffer_end] = temp
                    buffer_end = (buffer_end + 1) % MAX_BUFFER
                    buffer_size += 1
                    if i != 55:
                        temp = ser.read()

            if temp == b'\xff' or ser.in_waiting > 60:
                need_sync = False
                buffer_start = 0
                buffer_end = 0
                buffer_size = 0
                buffer = [0]*MAX_BUFFER
                data_pointer = 0
                data = [0] * INCOMING_BYTES
                if ser.in_waiting > 60:
                    ser.flushInput() # YEET we need latest info
                

        while buffer_size >= 4 and not need_sync:
            data_bytes = []
            for i in range(4):
                data_bytes.append(buffer[buffer_start])
                buffer_start = (buffer_start + 1) % MAX_BUFFER
                buffer_size -= 1
            #print(data_pointer, b''.join(data_bytes))
            data[data_pointer] = struct.unpack('f', b''.join(data_bytes))
            data_pointer += 1
            if data_pointer >= INCOMING_BYTES:
                data_pointer = 0
                need_sync = True
                print(data[:7])
                print(data[7:])


if __name__ == '__main__':
    handle_comms()
    

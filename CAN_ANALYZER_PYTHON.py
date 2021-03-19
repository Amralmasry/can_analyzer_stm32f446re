import time
import serial
import tkinter as tk
from pandas import DataFrame
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import threading
from matplotlib.animation import FuncAnimation
from itertools import count
import pandas as pd


read = [0,0,0,0]
main_read_1 = []   
main_read_2 = []   




#plt.style.use('seaborn')
axcolor = 'lightgoldenrodyellow'

x_vals = []
y_vals = []
 
index = count()

fig1, (ax1,ax2) = plt.subplots(nrows=2,ncols=1)
counter_1 = 0
counter_2 = 0
cc1 = 0
cc2 = 0


x1 = []
x2 = []

y1 = []
y2 = []
chan1_id = 0
chan2_id = 0
chan1_lable = str()
chan2_lable = str()
start = 0 
def animate(i):
    global read
    global main_read_1
    global main_read_2
    global cc1
    global cc2
    global chan1_id
    global chan2_id
    global chan1_lable
    global chan2_lable
    global start
    global counter_1 
    global counter_2 
    if start == 1 :
        if len(main_read_1) > cc1 :
            cc1 = len(main_read_1)
            
            ax1.cla()
             
            ax1.set_axisbelow(True)
            ax1.minorticks_on()
            ax1.grid(which='major', linestyle='-', linewidth='0.5', color='red')
            ax1.grid(which='minor', linestyle=':', linewidth='0.5', color='black')
            ax2.axvline(0.0,0,1, linestyle='dashed') 
            ax1.plot(x1, main_read_1, label= chan1_lable)
            ax1.legend()
            ax1.set_ylabel('time')
            if counter_1 < 500 :
                ax1.set_xlim([0,550])   
            else :
                ax1.set_xlim(max(0,counter_1 - 500),(counter_1 + 50))
            ax1.set_ylim([0,400])            
            
        if len(main_read_2) > cc2 :
            cc2 = len(main_read_2)
            ax2.cla()
            ax2.set_axisbelow(True)

            ax2.minorticks_on()
           
            ax2.grid(which='major', linestyle='-', linewidth='0.5', color='green')
            ax2.grid(which='minor', linestyle=':', linewidth='0.5', color='black')
            
            ax2.plot(x2, main_read_2, label= chan2_lable)
            ax2.legend()
            ax2.set_xlabel('time')
            if counter_2 < 250 :
                ax2.set_xlim([0,300])   
            else :
                ax2.set_xlim(max(0,counter_2 - 250),(counter_2 + 50))
            ax2.set_ylim([0,400])
 
def start_Stop () :
    global start
    if start == 0 :
        start = 1 
    else :
        start = 0 
       
    
 
def enter () :
    global chan1_id
    global chan2_id
    global chan1_lable
    global chan2_lable
    global start
    global enterButton
    global l1
    global l2
    global l3
    global l4
    global send_ID
    global send_DATA
    global ser
    chan1_id = int(chan_1_ID.get())
    chan2_id = int(chan_2_ID.get())
    chan1_lable = str(chan_1_lable.get())
    chan2_lable = str(chan_2_lable.get())
    chan_1_ID.destroy()
    chan_2_ID.destroy()
    chan_1_lable.destroy()
    chan_2_lable.destroy()
    enterButton.grid_remove ()
    l1.grid_remove ()
    l2.grid_remove ()
    l3.grid_remove ()
    l4.grid_remove ()
    
     
    send_ID = tk.Entry(Title1 , width = 30)
    send_ID.grid(row = 1 , column = 3)
    SEND_ID_LABEL = tk.Label(Title1, text = 'ID', font =('Verdana', 10)) 
    SEND_ID_LABEL.grid(row = 1 , column = 1)

    send_DATA = tk.Entry(Title1 , width = 30)
    send_DATA.grid(row = 3 , column = 3)
    send_DATA_LABEL = tk.Label(Title1, text = 'DATA', font =('Verdana', 10)) 
    send_DATA_LABEL.grid(row = 3 , column = 1)

    sendButton = tk.Button(Title1,text = "SEND" ,command = send_func , bg = 'green',width = 15)
    sendButton.grid(row = 4 , column = 3)
    
    sendButton = tk.Button(Title1,text = "SEND" ,command = send_func , bg = 'green',width = 15)
    sendButton.grid(row = 4 , column = 3)
    
    startstopButton = tk.Button(Title1,text = "start / stop" ,command = start_Stop , bg = 'red',width = 20)
    startstopButton.grid(row = 6 , column = 3)
    
    ser = serial.Serial('COM9',115200) 
 
    if ser.is_open:
        print("\n   Port Open Success")
    
    ser.write((chan1_id).to_bytes(2, byteorder='big'))
    ser.write((chan2_id).to_bytes(2, byteorder='big'))


    
    start =  1 ;

    
 
def send_func () :
    global send_ID
    global send_DATA
    global ser
    _id = int(send_ID.get())
    _data = int(send_DATA.get())
    print(_id)
    print(_data)
    ser.write((_id).to_bytes(2, byteorder='big'))
    ser.write((_data).to_bytes(2, byteorder='little'))


def function (i): 
    global counter_1 
    global counter_2 
   
    global read
    global main_read_1
    global main_read_2
    global can_1_data
    global can_2_data

    global chan1_id
    global chan2_id
    global start
    global ser
    global root
    while start == 0 :
        time.sleep(1)
    while 1 :
        while (ser.inWaiting()>0):
            for n in range(4):
                read[n]=int.from_bytes(ser.read(1), "big")
            can_id = (read[1] << 8 )| ((read[0]) & 0xff )
            can_id_data = (read[3] << 8 )| ((read[2]) & 0xff )   
            if   start == 1 :
                if ( can_id == chan1_id):
                    can_1_data = can_id_data
                    counter_1+=1 
                    x1.append(counter_1)
                    main_read_1.append(can_id_data)
                elif (can_id == chan2_id) :
                    can_2_data = can_id_data  
                    counter_2+=1 
                    x2.append(counter_2)
                    main_read_2.append(can_id_data)
         
       
    

root= tk.Tk()     
root.geometry("1000x500+200+100")

i=0
while i< 10:
	root.columnconfigure(i,minsize='10m')
	i+=1
i=0
while i<10:
	root.rowconfigure(i,minsize='10m')
	i+=1

fig1.set_size_inches(6,5)



#loginButton =tkinter.Button(root,text = "LOG IN" ,command = CheckID , bg = 'green',width = 15).grid(row = 4 , column = 4)
#l1 = tkinter.Label(root, text = 'ID', font =('Verdana', 10)) 
#l1.grid(row = 3 , column = 3)

Title = tk.Frame(root, width=400, height=400, bd=4, relief="ridge")
Title.grid(row=0, column=0)

Title1 = tk.Frame(root, width=400, height=400, relief="ridge")
Title1.grid(row=0, column=1)
i=0
while i< 10:
	Title1.columnconfigure(i,minsize='10m')
	i+=1
i=0
while i<10:
	Title1.rowconfigure(i,minsize='10m')
	i+=1
i=0
 
chan_1_ID = tk.Entry(Title1 , width = 30)
chan_1_ID.grid(row = 0 , column = 3)
l1 = tk.Label(Title1, text = 'ID 1', font =('Verdana', 10)) 
l1.grid(row = 0 , column = 1)

 
chan_1_lable = tk.Entry(Title1 , width = 30)
chan_1_lable.grid(row = 1 , column = 3)
l2 = tk.Label(Title1, text = 'label 1', font =('Verdana', 10)) 
l2.grid(row = 1 , column = 1)

chan_2_ID = tk.Entry(Title1 , width = 30)
chan_2_ID.grid(row = 4 , column = 3)
l3 = tk.Label(Title1, text = 'ID 2', font =('Verdana', 10)) 
l3.grid(row = 4 , column = 1)


chan_2_lable = tk.Entry(Title1 , width = 30)
chan_2_lable.grid(row = 5 , column = 3)
l4 = tk.Label(Title1, text = 'label 2', font =('Verdana', 10)) 
l4.grid(row = 5 , column = 1)

enterButton =tk.Button(Title1,text = "enter" ,command = enter , bg = 'green',width = 15)
enterButton.grid(row = 6 , column = 3)


bar1 = FigureCanvasTkAgg(fig1, Title)
bar1.get_tk_widget().grid(row = 0 , column = 0)
 
x = threading.Thread(target=function, args=(1,))
x.start() 

ani = FuncAnimation(fig1, animate, interval=50)

root.mainloop()
 

 

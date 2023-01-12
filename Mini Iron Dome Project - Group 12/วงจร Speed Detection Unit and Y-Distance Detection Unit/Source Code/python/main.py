#!/usr/bin/env python3
import time
import os
from practicum import find_mcu_boards, McuBoard, PeriBoard
from flask import Flask, render_template, redirect, url_for,send_from_directory
from multiprocessing import Process, Value, Manager

# Const
dist_cm = 19
delay_ms = 1
lower_limit_s = 3
upper_limit_cm_p_s = 20

err = 30
dist = dist_cm * 0.01
delay = delay_ms*0.001

devices = find_mcu_boards()
mcu = McuBoard(devices[0])
peri = PeriBoard(mcu)
app = Flask(__name__)
root_dir = os.getcwd()
manager = Manager() # multiprocess
m_speed = manager.Value('int',0)
m_height = manager.Value('float',1)

class Detector():
	def __init__(self):
		self.count = 0
		self.speed = 0
		self.height = 0
		self.detect_prev = [False,False]
		self.counter_on = False
		self.t = 0

	def beep(self,state):
		if(self.t%30 > 15):
			peri.set_beep(state)
		else:
			peri.set_beep(0)
	def update(self):
		# set detect
		detect = [peri.get_detect(0),peri.get_detect(1)]

		if(detect[1] and not self.detect_prev[1]):
			# positive edge
			self.counter_on = True
			self.count = 0
			self.height = 0

		if(detect[0] and not self.detect_prev[0]):
			# positive edge
			self.counter_on = False
			if(self.count != 0):
				self.speed = dist/(self.count*(delay+err*0.001))
				m_speed.value = self.speed
				m_height.value = self.height/self.count
				
			
	
		if(self.counter_on):
			h = get_height()
			#print(h)
			self.height +=h
			self.count+=1
			if(self.count*delay > lower_limit_s):
				# too slow
				self.counter_on = False
				self.count = 0

		if(self.speed*100 > upper_limit_cm_p_s): # too fast
			self.beep(1)
		else:
			self.beep(0)
		self.detect_prev[0] = detect[0]
		self.detect_prev[1] = detect[1]
		self.t+=1

def get_height():
	p = peri.get_echo()
	return p


d = Detector()
def detector_loop(d):
	while(True):
		d.update()
		time.sleep(delay) # 10 ms time


@app.route("/")
def index():
	return send_from_directory(root_dir, 'index.html')

@app.route("/speed")
def speed():
	return '{'+\
	"\"speed\": %.2f"% (m_speed.value*100)+\
	",\"height\": %.2f"% (m_height.value)+\
	'}'

if __name__ == "__main__":
	p = Process(target=detector_loop, args=(d,))
	p.start()  
	app.run(debug=False, port=8000, host="0.0.0.0")
	time.sleep(20)
	p.join()

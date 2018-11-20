#!/usr/bin/env python3
# -*- coding: utf-8 -*-


# modulos
'''
e@interspecifics.cc
'''

import pyxel
import argparse
import json
import math
from time import time, sleep
from oscpy.client import OSCClient

TWO_PI = 2*math.pi
old_paleton = [0, 1911635, 8267091, 34641, 
11227702, 6248271, 12764103, 16773608, 
0xFF0007, 0xFF8700, 0xFFFF00, 0x58E000, 
0x213FFF, 0x7117FF, 16742312, 16764074]
neu_paleton = [0x1C032B, 0x002F2F, 0x193434, 0xFFFAF6, 
0x007F7F, 0xD3D000, 0xD36000, 0x59068D, 
0x005D5D, 0x9B9900, 0x984600, 0x410568, 
0x003E3E, 0x676500, 0x672E00, 0x2B0345]

# like processing's map
def pMap(value, inMin, inMax, outMin, outMax):
	inSpan = inMax - inMin
	outSpan = outMax - outMin
	transVal = float(value - inMin) / float(inSpan)
	return outMin + (transVal * outSpan)



# App
class App:
	def __init__(self):
		pyxel.init(200, 200, fps=30, caption="[ i n t e r s p e c i f i c s ]:CE:Data Server", palette = old_paleton)
		# argparse
		self.ap = argparse.ArgumentParser()
		self.ap.add_argument("-t", "--transmission-file",    default="transmission.json",  help="json file with a sequence")
		self.args = vars(self.ap.parse_args())
		#params
		self.transmssn = json.load(open(self.args["transmission_file"], 'r'))
		self.seq_name = self.transmssn["name"]
		self.resol = self.transmssn["resolution"]
		self.sleepy_pause = self.transmssn["sleeptime"]
		self.sequence = self.transmssn["sequence"]
		#osc
		self.osc_addr = "192.168.1.87"
		self.osc_port = 8000
		self.osc = OSCClient(self.osc_addr, self.osc_port)
		#seq
		self.scene = ''
		self.data = ''
		self.feats = ''
		self.scene_name = ''
		self.scene_dur = ''
		self.t1 = 0
		self.nScene = 0
		self.load_scene(self.nScene)
		#stream
		self.i = 0
		self.j = 0
		self.k = 0
		self.feat = ''
		#pyxel
		pyxel.run(self.update, self.draw)



	def update(self):
		# increase step
		if (self.k < self.resol):			
			self.k = self.k + 1
		else:
			# increase frame
			if (self.i < len(self.data)):
				self.frame = self.data[self.i]
				self.i = self.i + 1
			else:
				# end scene
				self.i = 0
				self.osc.send_message(b'/CE/'+self.scene_name.encode()+b'/stop', [0])
				# increase scene
				self.nScene = self.nScene + 1
				if (self.nScene>=len(self.sequence)):
					self.nScene = 0
				# load new scene
				self.load_scene(self.nScene)
			# reset step
			self.k = 0
		# get frame size
		self.frameW = self.frame['gridWN']
		self.frameH = self.frame['gridHN']
		#print (self.i, len(self.frame['opticflow']))



	def draw(self):
		pyxel.cls(1)
		# draw the map
		for ai in range(len(self.frame['opticflow'])):
			ax = ai / (self.frameH+4) + 2
			ay = ai % (self.frameH+4) + 3
			if (len(self.frame['opticflow'][ai])>1):
				ang = self.frame['opticflow'][ai][2]/1000.0
				mag = self.frame['opticflow'][ai][3]/1000.0
				coloro = int(pMap(mag, 1, 32, 8, 12))
				#print(ax, ay, ai, self.frame['opticflow'][ai])
				pyxel.circ(ax, ay, 0.5, coloro)

		# then draw overlay
		for self.j in range(len(self.feats)):
			self.feat = self.feats[self.j]
			if (self.i>=self.feat["init_frame"] and self.i<=self.feat["end_frame"]):
				self.c_coord = [ int(( self.feat["coordinates"][0] + self.feat["radius"]*math.cos(self.k*TWO_PI/self.resol)) / self.frame['gridSize']), 
								 int(( self.feat["coordinates"][1] + self.feat["radius"]*math.sin(self.k*TWO_PI/self.resol)) / self.frame['gridSize']) ]
				# rectify cell index
				if (self.c_coord[0] > self.frameW): self.c_coord[0] = self.frameW
				if (self.c_coord[0] < 0): self.c_coord[0] = 0
				if (self.c_coord[1] > self.frameH): self.c_coord[1] = self.frameH
				if (self.c_coord[1] < 0): self.c_coord[1] = 0
				# calculate cell index
				self.c_cell  = self.c_coord[1] + (self.frameH+4)*self.c_coord[0]
				# get values for cell
				if (len(self.frame["opticflow"][self.c_cell]) > 1):
					self.c_angle = self.frame["opticflow"][self.c_cell][2]/1000.0  # the angle
					self.c_force= self.frame["opticflow"][self.c_cell][3]/1000.0  # the force
				else:
					self.c_angle = 0
					self.c_force= 0
				
				# draw around
				pyxel.circb(2+(self.feat["coordinates"][0]-self.feat["radius"])/10, 3+(self.feat["coordinates"][1])/10, 0.5, 6)
				pyxel.circb(2+(self.feat["coordinates"][0])/10, 3+(self.feat["coordinates"][1]-self.feat["radius"])/10, 0.5, 6)
				pyxel.circb(2+(self.feat["coordinates"][0]+self.feat["radius"])/10, 3+(self.feat["coordinates"][1])/10, 0.5, 6)
				pyxel.circb(2+(self.feat["coordinates"][0])/10, 3+(self.feat["coordinates"][1]+self.feat["radius"])/10, 0.5, 6)
				# draw center
				pyxel.circb(2+self.feat["coordinates"][0]/10, 3+self.feat["coordinates"][1]/10, 0.5, 7)
				pyxel.circb(2+self.feat["coordinates"][0]/10, 3+self.feat["coordinates"][1]/10, 3, 6)
				pyxel.text(2+self.feat["coordinates"][0]/10-5, 3+self.feat["coordinates"][1]/10+5, "[" + str(self.feat["index"]) + "]", 5)	
				# draw mobile
				pyxel.circ(2+self.c_coord[0], 3+self.c_coord[1], 0.5, (self.i%2)*7)
				# draw frames				
				pyxel.rectb(1, 1, pyxel.width-2, self.frameH+8, 6)
				pyxel.rectb(1, self.frameH+10, pyxel.width-2, pyxel.height-2, 6)
				pyxel.text(pyxel.width/2 + 0, pyxel.height/2 + 30 + self.j*10, "[" + str(self.feat["index"]) + "]: " + str(self.c_angle) , 7)	
				pyxel.text(pyxel.width/2 + 60, pyxel.height/2 + 30 + self.j*10, str(self.c_force), 7);
				# draw indicators
				mag = int(pMap(self.c_angle, -180, 180, -10, 10))
				pyxel.rect(pyxel.width/2 + 30, pyxel.height/2 + 36 + self.j*10, pyxel.width/2 + 30 + mag, pyxel.height/2 + 36 + self.j*10, 7)
				if (self.c_force==0): coloro = 7
				else: coloro = int(pMap(self.c_force, 1, 32, 8, 12))
				mag = int(pMap(self.c_force, 0, 32, 0, 20))
				pyxel.rect(pyxel.width/2 + 60, pyxel.height/2 + 36 + self.j*10, pyxel.width/2 + 60 + mag, pyxel.height/2 + 36 + self.j*10, coloro)

				# send it as OSC
				self.osc.send_message(b'/CE/'+self.scene_name.encode()+b'/F'+str(self.feat["index"]).encode(), [self.k, self.c_angle, self.c_force])

		#then draw texts
		pyxel.text(pyxel.width/2 -90, pyxel.height/2 + 30, "[scene]: " + self.scene_name, 7)	
		pyxel.text(pyxel.width/2 -90, pyxel.height/2 + 40, "[t]: " + str(self.i) + "." + str(self.k) + "/" + str(len(self.data)), 7)



	def load_scene(self, nSc):
		# load data
		self.scene = self.sequence[nSc] 
		self.data = json.load(open(self.scene["data_filename"], 'r'))
		self.feats = json.load(open(self.scene["feats_filename"], 'r'))
		self.scene_name = self.scene["name"]
		self.scene_dur = self.scene["duration"]
		self.t1 = int(time())
		self.i = 0
		self.j = 0
		self.k = 0
		self.frame = self.data[self.i]
		self.osc.send_message(b'/CE/'+self.scene_name.encode()+b'/start', [1])
		#print ("\n\n[loaded]: ", self.scene_name, "[t]:", self.t1, self.scene["data_filename"], self.scene["feats_filename"])
		#print ("\n[streamming]:")
		#print ("\n step \t\tF0.A \tF0.F \t\tF1.A \tF1.F \t\tF2.A \tF2.F \t\tF3.A \tF3.F \t\tF4.A \tF4.F")


App()


#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import  socket

class   QGateController:
    def __init__(self,address,port):
        self.address = address
        self.port    = port

        #create the socket instance
        self.sckt    = socket.socket()
        self.sckt.settimeout(2)         #set the socket timeout

        #connect the socket to the appropriate address/port
        self.sckt.connect((self.address,self.port))

    def acquire_head(self):

        #bytecode command to acquire circular buffer header
        hd = b'$RBH\r'
        #send the request to read the header
        self.sckt.send(hd)
        #receive the response from the controller
        head = self.sckt.recv(1024)
        return head

    def request_buffer(self):
        bf = b'$RDBC\t0\r'    #bytecode to request circular buffer
        self.sckt.send(bf)

    def acquire_buffer(self,frame_size,n_frames):
        #receives n_frames of the given frame_size
        buff = self.sckt.recv(frame_size*n_frames)
        return buff

    def close(self):
        self.sckt.close()

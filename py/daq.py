#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from acquire import QGateController
from decode import UDBF

class   DAQ:
    def __init__(self,address,port):
        self.ctrl = QGateController(address,port)
        self.udbf = UDBF()
        self.n_frames = 1000

    def start(self):
        #get the binary header from the controller
        bin_head  = self.ctrl.acquire_head()

        #decode the binary header
        self.udbf.decode_header(bin_head)

        #start the circular buffer
        self.ctrl.request_buffer()

        self.frame_size = sum(self.udbf.var_sizes)
        try:
            #loop forever while continually reading out the buffer and decoding the binary stream
            while True:
                bin_str = self.ctrl.acquire_buffer(self.frame_size, self.n_frames)
                self.udbf.decode_buffer(bin_str)

        #might want to add other except blocks to catch other errors
        except KeyboardInterrupt:
            pass
        except:
            raise
        finally:
            self.ctrl.close()


#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from acquire import QGateController
from decode import UDBF

class   DAQ:
    def __init__(self,address,port):
        self.ctrl = QGateController(address,port)

    def start(self):
        #get the binary header from the controller
        bin_head  = self.ctrl.acquire_head()

        #decode the binary header
        self.udbf = UDBF(bin_head)
        self.udbf.decode_header()

        #create buffer instance to decode the binary stream as it comes
        var_sizes = [4 for i in range(self.head.VarCount)]     #kind of sloppy but each variable should always be 4 bytes

        #start the circular buffer
        self.ctrl.request_buffer()

        try:
            #loop forever while continually reading out the buffer and decoding the binary stream
            while True:
                bin_str = self.ctrl.acquire_buffer()
                self.udbf.decode_buffer(bin_str)

        #might want to add other except blocks to catch other errors
        except KeyboardInterrupt:
            pass
        except:
            raise
        finally:
            self.ctrl.close()


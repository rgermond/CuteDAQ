#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import time

from acquire import QGateController
from decode import UDBF

class   DAQ:

    n_frames = 1000
    n_rows   = 40e3

    def __init__(self,address,port):
        self.ctrl = QGateController(address,port)
        self.udbf = UDBF()

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

                #generate a filename from the current time
                stamp = time.strftime('%Y%m%d_%H%M%S', time.localtime())
                filename = stamp + '.csv'

                for i in range(int(n_rows/n_frames)):
                    bin_str = self.ctrl.acquire_buffer(self.frame_size, n_frames)
                    self.udbf.decode_buffer(bin_str)
                    self.udbf.write_csv(filename, self.udbf.var_names[1:])      #write everything but the timestamp

        #might want to add other except blocks to catch other errors
        except KeyboardInterrupt:
            pass
        except:
            raise
        finally:
            self.ctrl.close()


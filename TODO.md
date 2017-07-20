#Things To Do

- [] Fix the recv_all() method in the client class so it actually receives all data in the buffer
     - This is necessary to read out the header when you don't know the length of it
     - Likewise change the DAQ::acquire_header() method in daq.hpp to reflect this change

- [] Change the constant N_FRAMES in daq.hpp to decide how much data should be used in each averaged FFT/ stored to file

- [] Extend functionality to support big and little endian processors
     - Currently only big endian data transfer is supported

- [] Include FFT/ PSD functionality and store this data
     - Necessary for the functionality required by CUTE

- [] Make it compatible with data types that AREN'T 4 bytes long

- [] Make it compatible with additional data in the header

- [] Implement some kind of sqlite db functionality?

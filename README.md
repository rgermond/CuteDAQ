# CuteDAQ
## Data Acquisition Controller for Gantner Q. Gate

The program is written in C++ and makes use of the Boost C++ library (specifically the Asio and the variant modules/headers). It was written for use with the vibration measurement system in the Cryogenic Underground TEst facility (CUTE), a particle astrophysics experiment based out of SNOLAB in Sudbury, ON, ran by SuperCDMS.

This code allows for data to be read out from Gantner Q.Gate DAQ over an ethernet port.
The code functions by opening a TCP socket with the controller.
The binary header is read out from the controller and decoded (necessary to decode the buffer).
The circular buffer begins filling and the data is stored to a CSV file.

Currently the DAQ only supports UDBF (Universal Data Bin Format) 1.07 and doesn't support additional data to be included in the stream (reference the Gantner QGate manual for more information).

## Building
To build controller using cmake simply:
```
cd build
cmake ..
make
```
## Testing
The extras folder provides a test server (called server) which provides the binary header and a sample of the binary buffer stream. To build the server simply run the bash script provided with:
```
./build.sh server
```
To test the DAQ run the server with:
```
./server <port-number>
```
And then start the DAQ with:
```
./daq localhost <port-numer>
```

## Future Plans
See the ToDo list (TODO.md) to see things currently being worked on, and the future plans (PLANS.md) for planned work.

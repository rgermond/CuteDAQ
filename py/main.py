from daq import DAQ

def main():
    #start the DAQ here
    daq = DAQ('192.168.1.28',10000)         #probably change this too so that the IP address can be set through GUI or config file
    daq.start()

if __name__ == '__main__':
    main()

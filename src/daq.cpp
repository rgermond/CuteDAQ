//DAQ for CUTE Rev 0.1
//Author: Richard Germond
//SuperCDMS, Queen's University

//standard C++ headers
#include <iostream>

//standard C headers
#include <signal.h>

//boost headers
#include <boost/asio.hpp>
using boost::asio::ip::tcp;

//my headers
#include "daq.hpp"

//function that handles the signal interrupt
void sig_handler(int sig)
{
    interrupt = true;
}

int main(int argc, const char *argv[])
{
    try
    {
        //ensure that the usage is correct
        if (argc != 3) 
        {
            std::cerr << "Usage: daq <hostname> <port> <additional flags>" << std::endl;
        }
        
        //set up the function to handle the SIGINT signal
        signal(SIGINT, sig_handler);

        //create an io_service and query object to pass to the daq object
        //so that a socket can be created and the acquisition performed
        boost::asio::io_service io_service;
        tcp::resolver::query query(argv[1],argv[2]);

        //create the DAQ object and run the acquisition
        DAQ daq(io_service, query, true);
        daq.start_daq();

        io_service.run();

    }

    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

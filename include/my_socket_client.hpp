#ifndef MY_SOCKET_CLIENT
#define MY_SOCKET_CLIENT

//C++ Headers
#include <iostream>
#include <vector>

//Boost Headers
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

enum {max_size = 1024};

class socket_client
{
    public:

        //constructor
        socket_client (boost::asio::io_service& io_service, const tcp::resolver::query query) : socket_(io_service), resolver_(io_service) 
    {
        tcp::resolver::iterator ep_it = resolver_.resolve(query);
        boost::asio::connect(socket_, ep_it);
    }

        //destructor
        ~socket_client ()
        {
            socket_.shutdown(tcp::socket::shutdown_both); //shutdown the send and receive functionality of a socket
            socket_.close();                              //finally close the socket
            //std::cout << "closed client" << std::endl;
        }
        
        //write function
        void send_msg (std::vector<char> & data)
        {
            boost::asio::write(socket_, boost::asio::buffer(data, data.size()));
        }

        //read function
        void recv_msg (std::vector<char> & data, int n) 
        {
            boost::asio::read(socket_, boost::asio::buffer(data), boost::asio::transfer_exactly(n));
        }

        //read-all function
        void recv_all (std::vector<char> & data,int max_size) 
        {
            //boost::asio::read(socket_, boost::asio::buffer(data), boost::asio::transfer_all());
            socket_.read_some(boost::asio::buffer(data, max_size));
        }

    private:
        tcp::resolver resolver_;
        tcp::socket socket_;
};


#endif //MY_SOCKET_CLIENT

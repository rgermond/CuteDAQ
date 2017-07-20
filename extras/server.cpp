//C++ Headers
#include <iostream>
#include <vector>
#include <fstream>

//C Headers
#include <stdlib.h>

//Boost Headers
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

enum {max_size = 1024};

class server
{
    public:
        server(boost::asio::io_service& io, const tcp::endpoint& endpoint) : acceptor_(io), socket_(io)
    {

        acceptor_.open(endpoint.protocol());             //open the acceptor
        acceptor_.bind(endpoint);                        //bind to the provided endpoint
        acceptor_.listen();                              //wait for a connection
        acceptor_.accept(socket_);                        //accept connection into the socket
    }

        ~server()
        {
            socket_.shutdown(tcp::socket::shutdown_both); //shutdown the send and receive functionality of a socket
            socket_.close();                              //finally close the socket
            std::cout << "closed server" << std::endl;
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
        void recv_all (std::vector<char> & data) 
        {
            boost::asio::read(socket_, boost::asio::buffer(data), boost::asio::transfer_exactly(socket_.available()));
        }

    private:
        tcp::acceptor acceptor_;
        tcp::socket socket_;
};


int main(int argc, const char *argv[])
{
    try
    {
    boost::asio::io_service io;
    tcp::endpoint endpoint(tcp::v4(), std::atoi(argv[1]));
    server s(io, endpoint); 

    //recv header request
    std::vector<char> req(max_size);
    s.recv_msg(req, 5);

    //print header request to stdout
    for (int i=0; i<req.size(); i++)
    {
        std::cout << req[i];
    }
    std::cout << std::endl;

    //acquire header from file
    std::streampos size;
    std::ifstream file("header.dat", std::ios::binary); 
    std::vector<char> header((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
    file.close(); 
    std::cout << "opened and closed the header file" << std::endl;
    std::cout << "length of header: " << header.size() << std::endl;

    //send header
    s.send_msg(header);

    //recv buffer request
    std::vector<char> bf_req(max_size);
    s.recv_msg(bf_req, 8);
    
    //print buffer request to stdout
    for (int i=0; i<bf_req.size(); i++)
    {
        std::cout << bf_req[i];
    }
    std::cout << std::endl;
    
    //acquire buffer from file
    std::ifstream file2("buffer.dat", std::ios::binary); 
    std::vector<char> buffer(360000);
    file2.read(&buffer[0], buffer.size());
    file2.close(); 
    std::cout << "opened and closed the buffer file" << std::endl;
    std::cout << "length of buffer: " << buffer.size() << std::endl;

    //send the buffer
    s.send_msg(buffer);
    
    io.run(); 

    }
    catch(std::exception & e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}

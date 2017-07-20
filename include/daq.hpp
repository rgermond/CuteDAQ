#ifndef MY_DAQ_H
#define MY_DAQ_H

//standard C++ headers
#include <iostream>
#include <vector>

//standard C headers
#include <signal.h>

//boost headers
#include <boost/asio.hpp>
using boost::asio::ip::tcp;

//headers from git
//https://github.com/aminroosta/sqlite_modern_cpp
//#include <sqlite_modern_cpp.h>

//headers from stack overflow
//https://stackoverflow.com/questions/997946/how-to-get-current-time-and-date-in-c
//user: Joe
#include "datetime_str_util.h"

//https://stackoverflow.com/questions/25201131/writing-csv-files-from-c
#include "csvfile.h" 

//my headers
#include "decode.hpp"
#include "my_socket_client.hpp"

//decide how many frames should be used in each db table
const int N_FRAMES = 10000;

//volatile boolean to determine if SIGINT (keyboard interrupt) is received by main program
volatile bool interrupt = false;

//class that inherits from the UDBF, "persistence" and "socket" classes
//implements all of the features that are required to  run the DAQ for CUTE
class DAQ : public UDBF, public socket_client
{
    public:

        DAQ(boost::asio::io_service & io, tcp::resolver::query query, bool persist=false) : socket_client(io, query), save_on(persist)
        {
        }

        void start_daq()
        {
            //public function that allows the daq to be started

            set_tbl_name();                                 //changes the name of the table to be saved to (if required)
            acquire_header();                               //requests, acquires and decodes the binary header (needed to decode buffer) 
            start_buffer();                                 //starts data to begin filling up the circular buffer
            
            int c = 0;
            while (c < 1) //!interrupt
            {
                acquire_frames();                           //constantly reads out N_FRAMES from the circular buffer
                c++;

                //if the flag has been passed to save the data
                if (save_on)
                {
                    save_csv();                          //save data to the db
                }
            }
        }

    private:

        //attributes
        bool save_on;
        std::string tbl_name;

        void acquire_header()
        {
            //header request byte array
            std::vector<char> hd_req = {'$','R','B','H','\r'};

            //request the header
            send_msg(hd_req);
            
            //store the header response
            std::vector<char> header(max_size);
            recv_msg(header, 256); //NOT GOOD SINCE WON'T KNOW IT'S 256 CHARACTERS LONG

            //decode the header
            decode_header(header);
        }
        
        void start_buffer()
        {
            //byte array to begin writing to the circular buffer
            std::vector<char> buf_req = {'$','R','B','D','C','\t','0','\r'};

            //start the circular buffer
            send_msg(buf_req);
        }

        void acquire_frames()
        {
        //acquires the number of frames (defined at top of file)
        //decodes them and stores them

            std::vector<char> frame(frame_size);

            for (int i=0; i < N_FRAMES; i++)
            {
            
            //acquire the frame
            recv_msg(frame, frame_size);

            //decode the buffer
            decode_frame(frame);

            }
            
        } 
        void save_csv()
        {
        //acquires the number of frames (defined at top of file)
        //decodes them and stores them

            csvfile csv(tbl_name+".csv");

            //write the header
            for (int n=0; n<=var_count; n++)
            {
                csv << name[n];
            }
            csv << endrow;

            //write the data to the file
            for (int i=0; i < N_FRAMES; i++)
            {
                for (int j=0; j<=var_count; j++) 
                {
                    csv << data[name[j]].front();                      //put each element in a sqlrow to be put into the db 
                    data[name[j]].pop();                               //remove the item from the queue
                }
                csv << endrow;
            
            }
            
        }

        //helper functions for the db functionality
        void set_tbl_name()
        {
            tbl_name = "vib_"+getCurrentDateTime(1); 
        }

        std::string create_tbl_query()
        {
            std::string tbl_query = "create table if not exists "; 
            tbl_query += tbl_name;
            tbl_query += " ";
            tbl_query += bind_names();
            tbl_query += ";";

            return tbl_query;
        }

        std::string insert_tbl_query()
        {
            std::string tbl_query = "insert into "; 
            tbl_query += tbl_name;
            tbl_query += " ";
            tbl_query += bind_names();
            tbl_query += " values ";
            tbl_query += bind_args();
            tbl_query += ";";

            return tbl_query;
        }

        std::string bind_names()
        {
            std::string bind = "(";
            for (int i=0; i <= var_count; i++)
            {
                bind += name[i]; 

                if (i != var_count)
                {
                bind += ",";
                }
            }
            bind += ")";

            return bind;
        }
        
        std::string bind_args()
        {
            std::string bind = "(";
            for (int i=0; i <= var_count; i++)
            {
                bind += "?"; 

                if (i != var_count)
                {
                bind += ",";
                }
            }
            bind += ")";

            return bind;
        }
};

#endif //MY_DAQ_H

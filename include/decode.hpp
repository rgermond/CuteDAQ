#ifndef UDBF_DECODE_H
#define UDBF_DECODE_H

//C++ headers
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>

//C headers
#include <string.h>
#include <math.h>

//Boost headers 
#include <boost/variant.hpp>

//my headers


/*class used to decode the binary stream from a GANTNER Q.GATE
 *only supports big endian, v.107, with no additional data 
 */

//function for slicing char array
std::string easy_slice(std::vector<char> buff, int start, int len);

//define structures to hold the data in using Boosts variant type
typedef boost::variant<double, float> measurement;
typedef std::map<std::string, std::queue<measurement > > collection;

class UDBF
{
    public:
        UDBF()
        {
            name.push_back("Counter");
        }
       
        //processing methods
        void decode_header(std::vector<char> header);
        void decode_frame(std::vector<char> buffer);
        
        collection data;
        std::vector<std::string> name;

    protected:
        int is_big_endian;
        int var_count;
        int frame_size;
        double sample_rate;

    private:
        //attributes
        int version, ven_len, with_check_sum, mod_add_data_len, dact_time_data_type;
        double start_time_2_dayf, dact_time_2_secf, start_time;
        std::vector<int> namelen, data_dir, data_typ,fieldlen,unitlen,add_data_len;
        std::vector<std::string> unit;

        //helper methods
        int byte_2_int(std::vector<char> buff, int start, int size);
        double byte_2_dbl(std::string str);
        float byte_2_flt(std::string str);

};

void UDBF::decode_header(std::vector<char> header)
{
    
    //get all of the fields before the variable information
    is_big_endian              = (int) header[0];                          
    version                     = byte_2_int(header, 1,2);                          
    ven_len                     = byte_2_int(header, 3,2);                          
    with_check_sum              = byte_2_int(header, 5+ven_len,1);                          
    mod_add_data_len            = byte_2_int(header, 6+ven_len,2);                          
    start_time_2_dayf        = byte_2_dbl(easy_slice(header, 8+ven_len,8));
    dact_time_data_type         = byte_2_int(header, 16+ven_len,2);                          
    dact_time_2_secf         = byte_2_dbl(easy_slice(header, 18+ven_len,8));
    start_time               = byte_2_dbl(easy_slice(header, 26+ven_len,8));
    sample_rate              = byte_2_dbl(easy_slice(header, 34+ven_len,8));
    var_count                   = byte_2_int(header, 42+ven_len, 2);                          

    int var_start = 44+ven_len;
    for (int i=0; i<var_count; i++)
    {
        
        //get the length of the name
        int nl = byte_2_int(header, var_start, 2);                          
        namelen.push_back(nl);
       
        //append the fields associated with variable
        name.push_back(easy_slice(header, var_start+2, nl));
        data_dir.push_back(byte_2_int(header, var_start+2+nl, 2));
        data_typ.push_back(byte_2_int(header, var_start+4+nl, 2));
        fieldlen.push_back(byte_2_int(header, var_start+6+nl, 2));
        unitlen.push_back(byte_2_int(header, var_start+8+nl, 2));
        
        //get the length of the unit
        int ul = byte_2_int(header, var_start+10+nl, 2);                          
        unitlen.push_back(ul);
        
        //append the final fields
        unit.push_back(easy_slice(header, var_start+12+nl, ul));
        add_data_len.push_back(byte_2_int(header, var_start+12+nl+ul, 2));

        //update the index for the loop
        var_start += nl + ul + 14;
    }

    frame_size = 8 + 4*var_count; //calculate the frame_size for the buffer in bytes, including the timestamp
}

void UDBF::decode_frame(std::vector<char> buffer)
{
   //assumes that there is an 8 byte double at the start 
   //of each frame, this gets inserted into the data stream
   //with the key "Counter " 
   //treats the rest of the values as floats

   int sz;
   int start = 0;
   for (int i=0; i<=var_count; i++)
   {
       if (i==0)                                            //the first 8 bytes in the frame is the timestamp, should be a double
       {
           sz = 8;
           double val = byte_2_dbl(easy_slice(buffer, start, sz));
           data[name[i]].push(val);
       }
       else                                                 //currently this only supports data which is 4 bytes long (ie. float)
       {
           sz = 4;
           float val = byte_2_flt(easy_slice(buffer, start, sz));
           data[name[i]].push(val);
       }

       start += sz;
       
   }
}

int UDBF::byte_2_int(std::vector<char> buff, int start, int size)
{
    int val = 0;
    if (is_big_endian)
    {
       for (int i=0; i<size; i++) 
       {
          val += ((int) buff[start+i])*pow(2,8*(size-i-1)); 
       }
    }
    return val;
}

//helper functions for converting from bytes to the required data type
double UDBF::byte_2_dbl(std::string str)
{
    std::reverse(str.begin(), str.end()); //I dont completely know why it needs to be flipped here...
    const char * buff = str.c_str();
    double val;
    memcpy(&val, buff, sizeof(val));
    return val;
}

float UDBF::byte_2_flt(std::string str)
{
    std::reverse(str.begin(), str.end()); //I dont completely know why it needs to be flipped here...
    const char * buff = str.c_str();
    float val;
    memcpy(&val, buff, sizeof(val));
    return val;
}

std::string easy_slice(std::vector<char> buff, int start, int len)
{
    std::string s;
    for (int i = 0; i < len; i++) 
    {
       s.push_back(buff[start+i]);
    }
    return s;
}

#endif //UDBF_DECODE_H

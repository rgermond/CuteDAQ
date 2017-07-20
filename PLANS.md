# Requirements for CUTE DAQ

- [x] should end gracefully upon shutdown signal
- [x] acquire data from QGate and decode binary stream
- [x] store requested length of data to csv file
- [] process data as desired 
- [] store requested length of data to database
- [] some kind of scope functionality to view data as it comes in

# Technologies for the DAQ 

* main DAQ written in C++ 
* store data in sqlite db
    * C/C++ has stdlib compatibility with sqlite 

#Technologies for scope functionality

The scope should run in any browser, and require a very minimal (few MB) folder to support this (ie. all required libraries be stored in the same folder)

* scope functionality some kind of javascript/php?
    * probably javascript as it runs on the client machine (ie. in browser)
    * could use the built in HTML canvas feature (compatible with js)
    * sql.js offers functionality for accessing sqlite db
        https://github.com/kripken/sql.js
    * can load data from sqlite file on disk based on:
        https://github.com/kripken/sql.js/wiki/Load-a-database-from-the-server
        https://www.w3schools.com/xml/xml_http.asp
        https://stackoverflow.com/questions/36749154/loading-sqlite-database-in-javascript-with-sql-js


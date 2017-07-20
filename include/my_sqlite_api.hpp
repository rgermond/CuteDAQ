#ifndef MY_SQLITE_H
#define MY_SQLITE_H

#include <iostream>
#include <vector>
#include <sqlite3.h>
#include <boost/variant.hpp>

typedef boost::variant<int, double, float, const char *> sqlcol;
typedef std::vector<sqlcol> sqlrow;
typedef std::vector<sqlrow> sqlrows;

class sqlite_bind_visitor : public boost::static_visitor<>
{
    public:
        sqlite_bind_visitor(){}
        
        void operator()(int & n, sqlite3_stmt *stmt, int col) const
        {
//        std::cout << n << std::endl;
            if (sqlite3_bind_int(stmt, col, n) != SQLITE_OK) 
            {
                //std::cerr << "bind_visitor int error" << std::endl; 
            }
        }

        void operator()(const char* & str, sqlite3_stmt *stmt, int col) const
        {
//       std::cout << str << std::endl;

            if (sqlite3_bind_text(stmt, col, str, strlen(str), SQLITE_STATIC) != SQLITE_OK) 
            {
                //std::cerr << "bind_visitor text error" << std::endl; 
            }
        }
        
        void operator()(double & f, sqlite3_stmt *stmt, int col) const
        {
//      std::cout << f << std::endl;

            if (sqlite3_bind_double(stmt, col, f) != SQLITE_OK) 
            {
                //std::cerr << "bind_visitor double error" << std::endl; 
            }
        }

        void operator()(float & f, sqlite3_stmt *stmt, int col) const
        {
//      std::cout << f << std::endl;
            double d = static_cast<double>(f);
            if (sqlite3_bind_double(stmt, col, d) != SQLITE_OK) 
            {
                //std::cerr << "bind_visitor float error" << std::endl; 
            }
        }
};

class SQLiteDB
{
    public:
        SQLiteDB(const char* filename);
        ~SQLiteDB();
        sqlrows query(const char* sql);
        void prepare(const char* sql);
        void insert(sqlrow vec);

    private:
        sqlite3 *db;
        sqlite3_stmt *stmt;
};

SQLiteDB::SQLiteDB(const char* filename) 
{
    sqlite3_open(filename, &db);
}

SQLiteDB::~SQLiteDB()
{
    sqlite3_close(db);
}

void SQLiteDB::prepare(const char* sql)
{
    //prepare the statement (mostly for insert statements)
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK)     
    {
        std::cerr << "SQLiteDB::prepare something went wrong" << std::endl; 
    }
}

void SQLiteDB::insert(sqlrow vec)
{
    //loop over all the columns
    //and bind the values to the previously prepared statement
    for (int i = 0; i < vec.size(); i++) 
    {
        //auto visitor = std::bind(sqlite_bind_visitor(), std::placeholders::_1, stmt, i+1);
        boost::apply_visitor(std::bind(sqlite_bind_visitor(), std::placeholders::_1, stmt, i+1), vec[i]);
    }

    //step the statement (actually apply it)
    if ( sqlite3_step(stmt) != SQLITE_DONE)
    {
        //std::cerr << "step failed" << std::endl;
    }
    
    //reset the statement so it can be used again
    if (sqlite3_reset(stmt) != SQLITE_OK)
    {
        std::cerr << "reset failed" << std::endl;
    }

}

sqlrows SQLiteDB::query(const char* sql)
{
    //sqlite3_stmt *stmt;
    sqlrows results;
     
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK)
    {
        int cols = sqlite3_column_count(stmt);
        int result;

        while (true) 
        {
            result = sqlite3_step(stmt);

            if (result==SQLITE_ROW) 
            {
                sqlrow values;

                for (int col = 0; col < cols; col++) 
                {
                    int col_type = sqlite3_column_type(stmt, col);

                    if (col_type == SQLITE_INTEGER) 
                    {
                        values.push_back(sqlite3_column_int(stmt, col));
                    }
                   
                    else if (col_type == SQLITE_FLOAT) 
                    {
                        values.push_back(sqlite3_column_double(stmt, col));
                    }
                    
                    else if (col_type == SQLITE_TEXT || SQLITE3_TEXT) 
                    {
                        values.push_back(reinterpret_cast<const char *>(sqlite3_column_text(stmt, col)));
                    }
                }
                results.push_back(values);

            }
            else
            {
                break;
            }
        }
        sqlite3_finalize(stmt);
    }
    return results;
}

#endif  //MY_SQLITE_H

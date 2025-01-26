#ifndef _MYEXCEPTION_HPP_
#define _MYEXCEPTION_HPP_

#include <iostream>

using namespace std;
//Hermela Gebretsion

class MyException {

    public:
    MyException(const std::string& msg);
    const char* what() const;

    private:
    std::string msg;
};


#endif

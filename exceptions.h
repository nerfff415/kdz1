#ifndef HW__EXCEPTIONS_H_
#define HW__EXCEPTIONS_H_
#include <exception>
#include <string>

class unsortedException : public std::exception {
    std::string m_error;
public:
    unsortedException(std::string msg):m_error(msg) {

    }
    const char* what() const noexcept
    {
        return m_error.c_str();
    }
};


#endif //HW__EXCEPTIONS_H_

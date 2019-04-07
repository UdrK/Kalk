#ifndef CUSTOMEXCEPTION_H
#define CUSTOMEXCEPTION_H
#include <exception>
#include <QString>

class CustomException : public std::exception{
private:
    QString reason;
public:
    CustomException(QString);
    CustomException();
    ~CustomException() throw() {}
    QString getReason()const;
};

#endif // CUSTOMEXCEPTION_H

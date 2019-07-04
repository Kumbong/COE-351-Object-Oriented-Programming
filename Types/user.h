#ifndef USER_H
#define USER_H
#include <QString>

class User
{
public:
    User();
//private:
    QString username;
    QString firstName;
    QString lastName;
    QString address;
    QString email;
    QString password;
    QString question;
    QString answer;
    int accountType;
};

#endif // USER_H

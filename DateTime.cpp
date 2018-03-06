#include <iostream>

std::string getDate()
{
    time_t t = time(0);
    struct tm * now = localtime(&t);
    return std::to_string(now->tm_mday) + "/" +
           std::to_string(now->tm_mon + 1) + "/" +
           std::to_string(now->tm_year + 1900);
}

std::string getTime()
{
    time_t t = time(0);
    struct tm * now = localtime(&t);
    return std::to_string(now->tm_hour) + ":" +
           std::to_string(now->tm_min) + ":" +
           std::to_string(now->tm_sec);
}
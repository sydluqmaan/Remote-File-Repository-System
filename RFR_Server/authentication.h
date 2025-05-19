#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H
#include <string>


class authentication {
public:
    std::string generateToken(std::string username);
    bool verifyToken();

private:
    const std::string JWT_SECRET = "my_super_secret_key";
};



#endif //AUTHENTICATION_H

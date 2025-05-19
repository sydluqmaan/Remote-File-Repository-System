#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H
#include "networking.h"
#include <string>

class Authentication {
    public:
        Authentication(Networking networkingIn);
        bool checkLocalToken();
        bool authenticate();

        Networking networking;
};

#endif

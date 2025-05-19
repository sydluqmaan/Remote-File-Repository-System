#include "authentication.h"
#include <jwt-cpp/jwt.h>
#include <string>
#include <chrono>

std::string authentication::generateToken(std::string username) {

    std::string token = jwt::create()
    .set_issuer("server")
    .set_type("JWS")
    .set_subject(username)
    .set_issued_at(std::chrono::system_clock::now())
    .set_expires_at(std::chrono::system_clock::now() + std::chrono::days(30))
    .sign(jwt::algorithm::hs256{JWT_SECRET});

    return token;
}
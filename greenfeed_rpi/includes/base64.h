#ifndef GREENFEED_RPI_BASE64_H
#define GREENFEED_RPI_BASE64_H

#include <string>

std::string base64_encode(unsigned char const* , unsigned int len);
std::string base64_decode(std::string const& s);

#endif //GREENFEED_RPI_BASE64_H

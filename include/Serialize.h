#ifndef SERIALIZE_H
#define SERIALIZE_H

#include "Bin_Ser.h"
#include "XML_Ser.h"

#include <fstream>
#include <sstream>

namespace Ser {
    bool USE_BASE64 = 1;

    void enable_base64() { USE_BASE64 = 1; }
    void disable_base64() { USE_BASE64 = 0; }

    inline void output(std::stringstream &buf, const std::string &path) {
        std::ofstream os;
        os.open(path);
        if (USE_BASE64)
            os << b64::encode(buf.str());
        else
            os << buf.str();
        os.flush();
    }

    template <typename Type>
    void serialize(const Type &obj, const std::string path) {
        std::stringstream buf;
        Bin_Ser::Serializer(obj, buf);

        output(buf, path);
    }

    template <typename Type>
    void serialize(const Type &obj, const std::string path, size_t len) {
        std::stringstream buf;
        Bin_Ser::Serializer(obj, buf, len);

        output(buf, path);
    }
}  // namespace Ser

namespace Des {
    bool USE_BASE64 = 1;

    void enable_base64() { USE_BASE64 = 1; }
    void disable_base64() { USE_BASE64 = 0; }

    inline void input(std::stringstream &buf, const std::string &path) {
        std::stringstream raw;
        std::ifstream is;
        is.open(path);
        if (USE_BASE64) {
            raw << is.rdbuf();
            buf << b64::decode(raw.str());
        } else
            buf << is.rdbuf();
    }

    template <typename Type>
    void deserialize(Type &obj, const std::string path) {
        std::stringstream buf;
        input(buf, path);
        Bin_Des::Deserializer(obj, buf);
    }

    template <typename Type>
    void deserialize(Type &obj, const std::string path, size_t len) {
        std::stringstream buf;
        input(buf, path);
        Bin_Des::Deserializer(obj, buf, len);
    }
}  // namespace Des

#endif
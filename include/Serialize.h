#ifndef SERIALIZE_H
#define SERIALIZE_H

#include "Bin_Ser.h"
#include "XML_Ser.h"
#include "tinyxml2.h"

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

    template <typename Type>
    void serialize_xml(const Type &obj, const std::string name, const std::string path) {
        xml_ser X_Ser(path.c_str());
        X_Ser.Serializer(obj, name, X_Ser.root);
    }

    template <typename Type>
    void serialize_xml(const Type &obj, const std::string name, const std::string path, size_t len) {
        xml_ser X_Ser(path.c_str());
        X_Ser.Serializer(obj, name, X_Ser.root, len);
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

    template <typename Type>
    void deserialize_xml(Type &obj, const std::string name, const std::string path) {
        xml_des X_Des(path.c_str());
        X_Des.Deserializer(obj, name, (X_Des.root)->FirstChildElement());
    }

    template <typename Type>
    void deserialize_xml(Type &obj, const std::string name, const std::string path, size_t len) {
        xml_des X_Des(path.c_str());
        X_Des.Deserializer(obj, name, (X_Des.root)->FirstChildElement(), len);
    }

}  // namespace Des

class UserType_Ser_Bin {
  public:
    UserType_Ser_Bin(const std::string path) : path(path) {}
    ~UserType_Ser_Bin() { Ser::output(buf, path); }

    template <typename Type>
    void serialize(Type &obj) {
        Bin_Ser::Serializer(obj, buf);
    }
    template <typename Type>
    void serialize(Type &obj, size_t len) {
        Bin_Ser::Serializer(obj, buf, len);
    }

  private:
    std::stringstream buf;
    std::string path;
};

class UserType_Des_Bin {
  public:
    UserType_Des_Bin(const std::string path) : path(path) { Des::input(buf, path); }
    ~UserType_Des_Bin() {}

    template <typename Type>
    void deserialize(Type &obj) {
        Bin_Des::Deserializer(obj, buf);
    }
    template <typename Type>
    void deserialize(Type &obj, size_t len) {
        Bin_Des::Deserializer(obj, buf, len);
    }

  private:
    std::stringstream buf;
    std::string path;
};

class UserType_Ser_Xml : public xml_ser {
  public:
    UserType_Ser_Xml(const char *filepath) : xml_ser(filepath){};
    ~UserType_Ser_Xml(){};

    template <typename Type>
    void serialize_xml(Type &obj, std::string NodeName) {
        Serializer(obj, NodeName, root);
    };
    template <typename Type>
    void serialize_xml(Type &obj, std::string NodeName, size_t len) {
        Serializer(obj, NodeName, root, len);
    };
};

class UserType_Des_Xml : public xml_des {
  private:
    tinyxml2::XMLElement *Child;

  public:
    UserType_Des_Xml(const char *filepath) : xml_des(filepath) { Child = root->FirstChildElement(); };
    ~UserType_Des_Xml(){};

    template <typename Type>
    void deserialize_xml(Type &obj, std::string NodeName) {
        if (Child) {
            Deserializer(obj, NodeName, Child);
            Child = Child->NextSiblingElement();
        }
    };
    template <typename Type>
    void deserialize_xml(Type &obj, std::string NodeName, size_t len) {
        if (Child) {
            Deserializer(obj, NodeName, Child, len);
            Child = Child->NextSiblingElement();
        }
    };
};

#endif
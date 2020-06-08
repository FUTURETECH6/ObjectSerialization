#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "Base64.h"
#include <fstream>
#include <memory>
#include <sstream>
#include <type_traits>

#include <list>
#include <map>
#include <set>
#include <utility>
#include <vector>

namespace ser {
    const std::string sep = " ";

    /* Arithmetic || string */
    template <typename Type>
    typename std::enable_if<std::is_arithmetic<Type>::value ||
                            std::is_same<Type, std::string>::value>::type
    Serializer(const Type &obj, std::ostream &buf) {
        buf << obj << sep;
    };

    /* pair */
    template <typename Type1, typename Type2>
    void Serializer(const std::pair<Type1, Type2> &obj, std::ostream &buf) {
        Serializer(obj.first, buf);
        Serializer<Type2>(obj.second, buf);
    };

    /* vector */
    template <typename Type>
    void Serializer(const std::vector<Type> &obj, std::ostream &buf) {
        buf << obj.size() << sep;
        for (auto &i : obj)
            Serializer<Type>(i, buf);
    }

    /* list */
    template <typename Type>
    void Serializer(const std::list<Type> &obj, std::ostream &buf) {
        buf << obj.size() << sep;
        for (auto &i : obj)
            Serializer<Type>(i, buf);
    }

    /* set */
    template <typename Type>
    void Serializer(const std::set<Type> &obj, std::ostream &buf) {
        buf << obj.size() << sep;
        for (auto &i : obj)
            Serializer<Type>(i, buf);
    }

    /* map */
    template <typename Type1, typename Type2>
    void Serializer(const std::map<Type1, Type2, std::less<Type1>,
                        std::allocator<std::pair<const Type1, Type2>>> &obj,
        std::ostream &buf) {
        buf << obj.size() << sep;
        for (auto &i : obj)
            Serializer<Type1, Type2>(i, buf);
    }

    /* unique_ptr */
    template <typename Type>
    void Serializer(const std::unique_ptr<Type> &obj, std::ostream &buf) {
        Serializer<Type>(*obj, buf);
    }
    template <typename Type>
    void Serializer(const std::unique_ptr<Type[]> &obj, std::ostream &buf, size_t len = 1) {
        buf << len << sep;
        for (auto i = 0; i < len; i++)
            Serializer<Type>(obj[i], buf);
    }

    /* shared_ptr */
    template <typename Type>
    void Serializer(const std::shared_ptr<Type> &obj, std::ostream &buf) {
        Serializer<Type>(*obj, buf);
    }
    template <typename Type>
    void Serializer(const std::shared_ptr<Type[]> &obj, std::ostream &buf, size_t len = 1) {
        buf << len << sep;
        for (auto i = 0; i < len; i++)
            Serializer<Type>(obj[i], buf);
    }

    /* ptr */
    template <typename Type>
    void Serializer(const Type *obj, std::ostream &buf, size_t len = 1) {
        buf << len << sep;
        for (auto i = 0; i < len; i++)
            Serializer<Type>(obj[i], buf);
    }

}  // namespace ser

namespace des {

    template <typename Type>
    typename std::enable_if<std::is_arithmetic<Type>::value ||
                            std::is_same<Type, std::string>::value>::type
    Deserializer(Type &obj, std::istream &buf) {
        buf >> obj;
    }

    /* pair */
    template <typename Type1, typename Type2>
    void Deserializer(std::pair<Type1, Type2> &obj, std::istream &buf) {
        Type1 tmp1;
        Type2 tmp2;
        Deserializer<Type1>(tmp1, buf);
        Deserializer<Type2>(tmp2, buf);
        obj = std::make_pair(tmp1, tmp2);
    };

    /* vector */
    template <typename Type>
    void Deserializer(std::vector<Type> &obj, std::istream &buf) {
        size_t len;
        buf >> len;
        obj.resize(len);
        for (auto &i : obj)
            Deserializer<Type>(i, buf);
    }

    /* list */
    template <typename Type>
    void Deserializer(std::list<Type> &obj, std::istream &buf) {
        size_t len;
        buf >> len;
        obj.resize(len);
        for (auto &i : obj)
            Deserializer<Type>(i, buf);
    }

    /* set */
    template <typename Type>
    void Deserializer(std::set<Type> &obj, std::istream &buf) {
        size_t len;
        buf >> len;
        for (auto i = 0; i < len; i++) {
            Type tmp;
            Deserializer<Type>(tmp, buf);
            obj.insert(tmp);
        }
    }

    /* map */
    template <typename Type1, typename Type2>
    void Deserializer(std::map<Type1, Type2> &obj, std::istream &buf) {
        size_t len;
        buf >> len;
        for (auto i = 0; i < len; i++) {
            Type1 tmp1;
            Type2 tmp2;
            Deserializer<Type1>(tmp1, buf);
            Deserializer<Type2>(tmp2, buf);
            obj.insert(std::make_pair(tmp1, tmp2));
        }
    }

    /* unique_ptr */
    template <typename Type>
    void Deserializer(std::unique_ptr<Type> &obj, std::istream &buf) {
        obj = std::unique_ptr<Type>(new Type);
        Deserializer<Type>(obj, buf);
    }
    template <typename Type>
    void Deserializer(std::unique_ptr<Type[]> &obj, std::istream &buf, size_t len = 1) {
        obj = std::unique_ptr<Type[]>(new Type[len]);
        for (auto i = 0; i < len; i++)
            Deserializer<Type>(obj[i], buf);
    }

    /* shared_ptr */
    template <typename Type>
    void Deserializer(std::shared_ptr<Type> &obj, std::istream &buf) {
        obj = std::shared_ptr<Type>(new Type);
        Deserializer<Type>(obj, buf);
    }
    template <typename Type>
    void Deserializer(std::shared_ptr<Type[]> &obj, std::istream &buf, size_t len = 1) {
        obj = std::unique_ptr<Type>(new Type[len]);
        for (auto i = 0; i < len; i++)
            Deserializer<Type>(obj[i], buf);
    }

    /* ptr */
    template <typename Type>
    void Deserializer(Type *obj, std::istream &buf, size_t len = 1) {
        obj = new Type[len];
        for (auto i = 0; i < len; i++)
            Deserializer<Type>(obj[i], buf);
    }
}  // namespace des

#endif

#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "Base64.h"
#include <fstream>
#include <memory>
#include <sstream>

#include <list>
#include <map>
#include <set>
#include <utility>
#include <vector>

namespace ser {
    template <typename T1, typename T2 = void, typename T3 = void>
    class Base_Ser {
      public:
        using obj_type   = T1;
        using value_type = T2;
        using pair_type1 = T2;
        using pair_type2 = T3;

        Base_Ser(obj_type &obj, std::ostream &os) : obj(obj), os(os) { buffer.clear(); };
        ~Base_Ser() { toBase64(); }
        virtual void serialize() = 0;
        void toBase64() {
            os << b64::encode(buffer.str());
            os.flush();
        }

      protected:
        const char *sep = " ";
        const obj_type &obj;
        std::ostream &os;
        std::stringstream buffer;
    };

    template <typename T1>
    class ser_ari : public Base_Ser<T1> {
      public:
        using base = Base_Ser<T1>;

        ser_ari(typename base::obj_type &obj, std::ostream &os) : base(obj, os) { serialize(); }
        void serialize() override { base::buffer << base::obj << std::endl; }
    };

    template <typename T2, typename T3>
    class ser_pair : public Base_Ser<std::pair<T2, T3>, T2, T3> {
      public:
        using base = Base_Ser<std::pair<T2, T3>, T2, T3>;

        ser_pair(typename base::obj_type &obj, std::ostream &os) : base(obj, os) { serialize(); }
        void serialize() override {
            base::buffer << base::obj.first << base::sep << base::obj.second << std::endl;
        }
    };

    template <typename T2>
    class sec_uptr : public Base_Ser<std::unique_ptr<T2>, T2> {
      public:
        using base = Base_Ser<std::unique_ptr<T2>, T2>;

        sec_uptr(typename base::obj_type &obj, std::ostream &os) : base(obj, os) { serialize(); }
        void serialize() override { base::buffer << base::obj << std::endl; }
    };

    template <typename T2>
    class ser_vec : public Base_Ser<std::vector<T2>, T2> {
      public:
        using base = Base_Ser<std::vector<T2>, T2>;

        ser_vec(typename base::obj_type &obj, std::ostream &os) : base(obj, os) { serialize(); }
        void serialize() override {
            base::buffer << base::obj.size() << base::sep;
            for (auto &elem : base::obj)
                base::buffer << elem << base::sep;
            base::buffer << std::endl;
        }
    };

    template <typename T2>
    class ser_list : public Base_Ser<std::list<T2>, T2> {
      public:
        using base = Base_Ser<std::list<T2>, T2>;

        ser_list(typename base::obj_type &obj, std::ostream &os) : base(obj, os) { serialize(); }
        void serialize() override {
            base::buffer << base::obj.size() << base::sep;
            for (auto &elem : base::obj)
                base::buffer << elem << base::sep;
            base::buffer << std::endl;
        }
    };

    template <typename T2>
    class ser_set : public Base_Ser<std::set<T2>, T2> {
      public:
        using base = Base_Ser<std::set<T2>, T2>;

        ser_set(typename base::obj_type &obj, std::ostream &os) : base(obj, os) { serialize(); }
        void serialize() override {
            base::buffer << base::obj.size() << base::sep;
            for (auto &elem : base::obj)
                base::buffer << elem << base::sep;
            base::buffer << std::endl;
        }
    };

    template <typename T2, typename T3>
    class ser_map : public Base_Ser<std::map<T2, T3>, T2, T3> {
      public:
        using base = Base_Ser<std::map<T2, T3>, T2, T3>;

        ser_map(typename base::obj_type &obj, std::ostream &os) : base(obj, os) { serialize(); }
        void serialize() override {
            base::buffer << base::obj.size() << base::sep;
            for (auto &elem : base::obj)
                base::buffer << elem.first << base::sep << elem.second << base::sep;
            base::buffer << std::endl;
        }
    };
} // namespace ser

/* -------------------------------------------------------------------------- */

namespace des {
    template <typename T1, typename T2 = void, typename T3 = void>
    class Base_Des {
      public:
        using obj_type   = T1;
        using value_type = T2;
        using pair_type1 = T2;
        using pair_type2 = T3;

        Base_Des(obj_type &obj, std::istream &is) : obj(obj), is(is) { fromBase64(); }
        virtual void deserialize() = 0;
        void fromBase64() {
            buffer.clear();
            std::stringstream raw;
            raw << is.rdbuf();
            buffer << b64::decode(raw.str());
        }

      protected:
        obj_type &obj;
        std::istream &is;
        std::stringstream buffer;
    };

    template <typename T1>
    class des_ari : public Base_Des<T1> {
      public:
        using base = Base_Des<T1>;

        des_ari(typename base::obj_type &obj, std::istream &is) : base(obj, is) { deserialize(); }
        void deserialize() override { base::buffer >> std::skipws >> base::obj; }
    };

    template <typename T2, typename T3>
    class des_pair : Base_Des<std::pair<T2, T3>, T2, T3> {
      public:
        using base = Base_Des<std::pair<T2, T3>, T2, T3>;

        des_pair(typename base::obj_type &obj, std::istream &is) : base(obj, is) { deserialize(); }
        void deserialize() override {
            typename base::pair_type1 first;
            typename base::pair_type2 second;
            base::buffer >> std::skipws >> first >> second;
            base::obj = std::make_pair(first, second);
        }
    };

    template <typename T2>
    class des_uptr : Base_Des<std::unique_ptr<T2>, T2> {
      public:
        using base = Base_Des<std::unique_ptr<T2>, T2>;

        des_uptr(typename base::obj_type &obj, std::istream &is) : base(obj, is) { deserialize(); }
        void deserialize() override {
            size_t size;
            base::buffer >> std::skipws >> size;
            base::obj.reset();
            base::obj = std::make_unique<typename base::value_type>(new typename base::value_type);
            base::buffer >> base::obj;
            // for (auto i = 0; i < size; i++)
            //     base::buffer >> base::obj[i];
        }
    };

    template <typename T2>
    class des_vec : Base_Des<std::vector<T2>, T2> {
      public:
        using base = Base_Des<std::vector<T2>, T2>;

        des_vec(typename base::obj_type &obj, std::istream &is) : base(obj, is) { deserialize(); }
        void deserialize() override {
            size_t size;
            typename base::value_type tmpVal;
            base::buffer >> std::skipws >> size;
            base::obj.clear();
            for (; size-- > 0;) {
                base::buffer >> tmpVal;
                base::obj.push_back(tmpVal);
            }
        }
    };

    template <typename T2>
    class des_list : Base_Des<std::list<T2>, T2> {
      public:
        using base = Base_Des<std::list<T2>, T2>;

        des_list(typename base::obj_type &obj, std::istream &is) : base(obj, is) { deserialize(); }
        void deserialize() override {
            size_t size;
            typename base::value_type tmpVal;
            base::buffer >> std::skipws >> size;
            base::obj.clear();
            for (; size-- > 0;) {
                base::buffer >> tmpVal;
                base::obj.push_back(tmpVal);
            }
        }
    };

    template <typename T2>
    class des_set : Base_Des<std::set<T2>, T2> {
      public:
        using base = Base_Des<std::set<T2>, T2>;

        des_set(typename base::obj_type &obj, std::istream &is) : base(obj, is) { deserialize(); }
        void deserialize() override {
            size_t size;
            typename base::value_type tmpVal;
            base::buffer >> std::skipws >> size;
            base::obj.clear();
            for (; size-- > 0;) {
                base::buffer >> tmpVal;
                base::obj.insert(tmpVal);
            }
        }
    };

    template <typename T2, typename T3>
    class des_map : Base_Des<std::map<T2, T3>, T2, T3> {
      public:
        using base = Base_Des<std::map<T2, T3>, T2, T3>;

        des_map(typename base::obj_type &obj, std::istream &is) : base(obj, is) { deserialize(); }
        void deserialize() override {
            size_t size;
            typename base::pair_type1 tmpVal1;
            typename base::pair_type2 tmpVal2;
            base::buffer >> std::skipws >> size;
            base::obj.clear();
            for (; size-- > 0;) {
                base::buffer >> tmpVal1 >> tmpVal2;
                base::obj.insert(std::pair<typename base::pair_type1, typename base::pair_type2>(
                    tmpVal1, tmpVal2));
            }
        }
    };
} // namespace des

#endif

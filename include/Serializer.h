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

#define USING_BASE64 0

namespace ser {
    template <typename T1, typename T2 = void, typename T3 = void>
    class Base_Ser {
      protected:
        using obj_type   = T1;
        using value_type = T2;
        using pair_type1 = T2;
        using pair_type2 = T3;

        const char *sep = " ";
        const obj_type &obj;
        std::ostream &os;
        std::stringstream buffer;

      public:
        Base_Ser(obj_type &obj, std::ostream &os) : obj(obj), os(os) { buffer.clear(); };
        ~Base_Ser() { toBase64(); }

      private:
        virtual void serialize() = 0;
        void toBase64() {
            if (USING_BASE64)
                os << b64::encode(buffer.str());
            else
                os << buffer.str();
            os.flush();
        }
    };

    template <typename T1>
    class ser_ari : public Base_Ser<T1> {
      private:
        using base = Base_Ser<T1>;
        void serialize() override { base::buffer << base::obj << std::endl; }

      public:
        ser_ari(typename base::obj_type &obj, std::ostream &os) : base(obj, os) { serialize(); }
    };

    template <typename T2, typename T3>
    class ser_pair : public Base_Ser<std::pair<T2, T3>, T2, T3> {
      private:
        using base = Base_Ser<std::pair<T2, T3>, T2, T3>;
        void serialize() override { base::buffer << base::obj.first << base::sep << base::obj.second << std::endl; }

      public:
        ser_pair(typename base::obj_type &obj, std::ostream &os) : base(obj, os) { serialize(); }
    };

    template <typename T2>
    class ser_ptr : public Base_Ser<T2 *, T2> {
      private:
        using base = Base_Ser<T2 *, T2>;
        void serialize() override { base::buffer << *(base::obj) << std::endl; }

      public:
        ser_ptr(typename base::obj_type &obj, std::ostream &os) : base(obj, os) { serialize(); }
    };

    template <typename T2>
    class ser_ptra : public Base_Ser<T2 *, T2> {
      private:
        using base = Base_Ser<T2 *, T2>;
        void serialize() override {
            base::buffer << size << base::sep;
            for (auto i = 0; i < size; i++)
                base::buffer << base::obj[i] << base::sep;
            // copy(base::obj, &(base::obj[size]),
            //     std::ostream_iterator<typename base::value_type>(base::buffer, base::sep));
            base::os.flush();
        }

        size_t size;

      public:
        ser_ptra(typename base::obj_type obj, size_t len, std::ostream &os) : base(obj, os), size(len) { serialize(); }
    };

    template <typename T2>
    class ser_uptr : public Base_Ser<std::unique_ptr<T2>, T2> {
      private:
        using base = Base_Ser<std::unique_ptr<T2>, T2>;
        void serialize() override { base::buffer << *(base::obj) << std::endl; }

      public:
        ser_uptr(typename base::obj_type &obj, std::ostream &os) : base(obj, os) { serialize(); }
    };

    template <typename T2>
    class ser_uptra : public Base_Ser<std::unique_ptr<T2[]>, T2> {
      private:
        using base = Base_Ser<std::unique_ptr<T2[]>, T2>;
        void serialize() override {
            base::buffer << size << base::sep;
            for (auto i = 0; i < size; i++)
                base::buffer << base::obj[i] << base::sep;
            // copy(base::obj, &(base::obj[size]),
            //     std::ostream_iterator<typename base::value_type>(base::buffer, base::sep));
            base::os.flush();
        }

        size_t size;

      public:
        ser_uptra(typename base::obj_type &obj, size_t len, std::ostream &os) : base(obj, os), size(len) {
            serialize();
        }
    };

    template <typename T2>
    class ser_sptr : public Base_Ser<std::shared_ptr<T2>, T2> {
      private:
        using base = Base_Ser<std::shared_ptr<T2>, T2>;
        void serialize() override { base::buffer << *(base::obj) << std::endl; }

      public:
        ser_sptr(typename base::obj_type &obj, std::ostream &os) : base(obj, os) { serialize(); }
    };

    template <typename T2>
    class ser_sptra : public Base_Ser<std::shared_ptr<T2[]>, T2> {
      private:
        using base = Base_Ser<std::shared_ptr<T2[]>, T2>;
        void serialize() override {
            base::buffer << size << base::sep;
            for (auto i = 0; i < size; i++)
                base::buffer << base::obj[i] << base::sep;
            base::os.flush();
        }

        size_t size;

      public:
        ser_sptra(typename base::obj_type &obj, size_t len, std::ostream &os) : base(obj, os), size(len) {
            serialize();
        }
    };

    template <typename T2>
    class ser_vec : public Base_Ser<std::vector<T2>, T2> {
      private:
        using base = Base_Ser<std::vector<T2>, T2>;
        void serialize() override {
            base::buffer << base::obj.size() << base::sep;
            for (auto &elem : base::obj)
                base::buffer << elem << base::sep;
            base::buffer << std::endl;
        }

      public:
        ser_vec(typename base::obj_type &obj, std::ostream &os) : base(obj, os) { serialize(); }
    };

    template <typename T2>
    class ser_list : public Base_Ser<std::list<T2>, T2> {
      private:
        using base = Base_Ser<std::list<T2>, T2>;
        void serialize() override {
            base::buffer << base::obj.size() << base::sep;
            for (auto &elem : base::obj)
                base::buffer << elem << base::sep;
            base::buffer << std::endl;
        }

      public:
        ser_list(typename base::obj_type &obj, std::ostream &os) : base(obj, os) { serialize(); }
    };

    template <typename T2>
    class ser_set : public Base_Ser<std::set<T2>, T2> {
      private:
        using base = Base_Ser<std::set<T2>, T2>;
        void serialize() override {
            base::buffer << base::obj.size() << base::sep;
            for (auto &elem : base::obj)
                base::buffer << elem << base::sep;
            base::buffer << std::endl;
        }

      public:
        ser_set(typename base::obj_type &obj, std::ostream &os) : base(obj, os) { serialize(); }
    };

    template <typename T2, typename T3>
    class ser_map : public Base_Ser<std::map<T2, T3>, T2, T3> {
      private:
        using base = Base_Ser<std::map<T2, T3>, T2, T3>;
        void serialize() override {
            base::buffer << base::obj.size() << base::sep;
            for (auto &elem : base::obj)
                base::buffer << elem.first << base::sep << elem.second << base::sep;
            base::buffer << std::endl;
        }

      public:
        ser_map(typename base::obj_type &obj, std::ostream &os) : base(obj, os) { serialize(); }
    };
}  // namespace ser

/* -------------------------------------------------------------------------- */

namespace des {
    template <typename T1, typename T2 = void, typename T3 = void>
    class Base_Des {
      protected:
        using obj_type   = T1;
        using value_type = T2;
        using pair_type1 = T2;
        using pair_type2 = T3;

        obj_type &obj;
        std::istream &is;
        std::stringstream buffer;

      public:
        Base_Des(obj_type &obj, std::istream &is) : obj(obj), is(is) { fromBase64(); }

      private:
        virtual void deserialize() = 0;
        void fromBase64() {
            buffer.clear();
            std::stringstream raw;
            raw << is.rdbuf();
            if (USING_BASE64)
                buffer << b64::decode(raw.str());
            else
                buffer << raw.str();
        }
    };

    template <typename T1>
    class des_ari : public Base_Des<T1> {
      private:
        using base = Base_Des<T1>;
        void deserialize() override { base::buffer >> std::skipws >> base::obj; }

      public:
        des_ari(typename base::obj_type &obj, std::istream &is) : base(obj, is) { deserialize(); }
    };

    template <typename T2, typename T3>
    class des_pair : Base_Des<std::pair<T2, T3>, T2, T3> {
      private:
        using base = Base_Des<std::pair<T2, T3>, T2, T3>;
        void deserialize() override {
            typename base::pair_type1 first;
            typename base::pair_type2 second;
            base::buffer >> std::skipws >> first >> second;
            base::obj = std::make_pair(first, second);
        }

      public:
        des_pair(typename base::obj_type &obj, std::istream &is) : base(obj, is) { deserialize(); }
    };

    template <typename T2>
    class des_ptr : Base_Des<T2 *, T2> {
      private:
        using base = Base_Des<T2 *, T2>;
        void deserialize() override {
            base::obj = new int;
            base::buffer >> std::skipws >> *(base::obj);
        }

      public:
        des_ptr(typename base::obj_type &obj, std::istream &is) : base(obj, is) { deserialize(); }
    };

    template <typename T2>
    class des_ptra : Base_Des<T2 *, T2> {
      private:
        using base = Base_Des<T2 *, T2>;
        void deserialize() override {
            size_t size;
            base::buffer >> std::skipws >> size;
            base::obj = new int[size];
            for (auto i = 0; i < size; i++)
                base::buffer >> base::obj[i];
            // copy(std::istream_iterator<typename base::obj_type>(base::is),
            //     std::istream_iterator<typename base::obj_type>(), base::obj);
        }

      public:
        des_ptra(typename base::obj_type &obj, std::istream &is) : base(obj, is) { deserialize(); }
    };

    template <typename T2>
    class des_uptr : Base_Des<std::unique_ptr<T2>, T2> {
      private:
        using base = Base_Des<std::unique_ptr<T2>, T2>;
        void deserialize() override {
            base::obj = std::unique_ptr<typename base::value_type>(new int);
            base::buffer >> std::skipws >> *(base::obj);
        }

      public:
        des_uptr(typename base::obj_type &obj, std::istream &is) : base(obj, is) { deserialize(); }
    };

    template <typename T2>
    class des_uptra : Base_Des<std::unique_ptr<T2[]>, T2> {
      private:
        using base = Base_Des<std::unique_ptr<T2[]>, T2>;
        void deserialize() override {
            size_t size;
            base::buffer >> std::skipws >> size;
            base::obj = std::unique_ptr<typename base::value_type[]>(new int[size]);
            for (auto i = 0; i < size; i++)
                base::buffer >> base::obj[i];
            // copy(std::istream_iterator<typename base::obj_type>(base::is),
            //     std::istream_iterator<typename base::obj_type>(), base::obj);
        }

      public:
        des_uptra(typename base::obj_type &obj, std::istream &is) : base(obj, is) { deserialize(); }
    };

    template <typename T2>
    class des_sptr : Base_Des<std::shared_ptr<T2>, T2> {
      private:
        using base = Base_Des<std::shared_ptr<T2>, T2>;
        void deserialize() override {
            base::obj = std::shared_ptr<typename base::value_type>(new int);
            base::buffer >> std::skipws >> *(base::obj);
        }

      public:
        des_sptr(typename base::obj_type &obj, std::istream &is) : base(obj, is) { deserialize(); }
    };

    template <typename T2>
    class des_sptra : Base_Des<std::shared_ptr<T2[]>, T2> {
      private:
        using base = Base_Des<std::shared_ptr<T2[]>, T2>;
        void deserialize() override {
            size_t size;
            base::buffer >> std::skipws >> size;
            base::obj = std::shared_ptr<typename base::value_type[]>(new int[size]);
            for (auto i = 0; i < size; i++)
                base::buffer >> base::obj[i];
        }

      public:
        des_sptra(typename base::obj_type &obj, std::istream &is) : base(obj, is) { deserialize(); }
    };

    template <typename T2>
    class des_vec : Base_Des<std::vector<T2>, T2> {
      private:
        using base = Base_Des<std::vector<T2>, T2>;
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

      public:
        des_vec(typename base::obj_type &obj, std::istream &is) : base(obj, is) { deserialize(); }
    };

    template <typename T2>
    class des_list : Base_Des<std::list<T2>, T2> {
      private:
        using base = Base_Des<std::list<T2>, T2>;
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

      public:
        des_list(typename base::obj_type &obj, std::istream &is) : base(obj, is) { deserialize(); }
    };

    template <typename T2>
    class des_set : Base_Des<std::set<T2>, T2> {
      private:
        using base = Base_Des<std::set<T2>, T2>;
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

      public:
        des_set(typename base::obj_type &obj, std::istream &is) : base(obj, is) { deserialize(); }
    };

    template <typename T2, typename T3>
    class des_map : Base_Des<std::map<T2, T3>, T2, T3> {
      private:
        using base = Base_Des<std::map<T2, T3>, T2, T3>;
        void deserialize() override {
            size_t size;
            typename base::pair_type1 tmpVal1;
            typename base::pair_type2 tmpVal2;
            base::buffer >> std::skipws >> size;
            base::obj.clear();
            for (; size-- > 0;) {
                base::buffer >> tmpVal1 >> tmpVal2;
                base::obj.insert(std::pair<typename base::pair_type1, typename base::pair_type2>(tmpVal1, tmpVal2));
            }
        }

      public:
        des_map(typename base::obj_type &obj, std::istream &is) : base(obj, is) { deserialize(); }
    };
}  // namespace des

#endif

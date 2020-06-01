#include "Serializer.h"
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <set>
#include <utility>
#include <vector>

using namespace std;

template <typename Type>
void foo(vector<Type> &obj, string path) {
    ifstream is;
    is.open(path);
    des::des_vec<Type>(obj, is);
}

template <typename Type>
void foo(list<Type> &obj, string path) {
    ifstream is;
    is.open(path);
    des::des_list<Type>(obj, is);
}

template <typename Type1, typename Type2>
void fuu(map<Type1, Type2> &obj, string path) {
    ofstream os;
    os.open(path);
    ser::ser_map<Type1, Type2>(obj, os);
}

template <typename Type1, typename Type2>
void foo(map<Type1, Type2> &obj, string path) {
    ifstream is;
    is.open(path);
    des::des_map<Type1, Type2>(obj, is);
}

int main(int argc, char const *argv[]) {
    int i, i0                     = 3;
    vector<int> vi, vi0           = {1, 3, 5, 7};
    list<int> li, li0             = {2, 4, 6, 8};
    set<int> si, si0              = {6, 7, 33, 9, 81, 31, 54};
    map<string, int> msi, msi0    = {pair<string, int>("SC", 666), pair<string, int>("cx", 999)};
    unique_ptr<int> upi, upi0     = unique_ptr<int>(new int(19));
    unique_ptr<int[]> upai, upai0 = unique_ptr<int[]>(new int[5]);
    shared_ptr<int> spi, spi0     = shared_ptr<int>(new int(89));
    // Since array of shared_ptr is only supported after c++17, we won't test it here(but still implemented)

    for (auto i = 0; i < 5; i++)
        upai0[i] = (i + 1) * (i + 1);

    /* Ser Test */
    // ostream &ofile = cout;
    ofstream ofile;
    ifstream ifile;
    const string path = "/Users/Ulysses/Desktop/Terminal Saved Output.txt";

    foo(vi, path);
    foo(li, path);
    foo(msi, path);

    enum typelist { ari, vec, list, uptr, uptra, sptr, set, map };
    switch (typelist(sptr)) {
        case typelist(ari):
            ofile.open(path);
            ifile.open(path);
            ser::ser_ari<int>(i0, ofile);
            des::des_ari<int>(i, ifile);
            break;

        case typelist(vec):
            ofile.open(path);
            ifile.open(path);
            ser::ser_vec<int>(vi0, ofile);
            des::des_vec<int>(vi, ifile);
            break;

        case typelist(list):
            ofile.open(path);
            ifile.open(path);
            ser::ser_list<int>(li0, ofile);
            des::des_list<int>(li, ifile);
            break;

        case typelist(uptr):
            ofile.open(path);
            ifile.open(path);
            ser::ser_uptr<int>(upi0, ofile);
            des::des_uptr<int>(upi, ifile);
            break;

        case typelist(uptra):
            ofile.open(path);
            ifile.open(path);
            ser::ser_uptra<int>(upai0, 5, ofile);
            des::des_uptra<int>(upai, ifile);
            for (auto i = 0; i < 5; i++)
                cerr << upai[i] << " ";
            break;

        case typelist(sptr):
            ofile.open(path);
            ifile.open(path);
            ser::ser_sptr<int>(spi0, ofile);
            des::des_sptr<int>(spi, ifile);
            break;

        case typelist(set):
            ofile.open(path);
            ifile.open(path);
            ser::ser_set<int>(si0, ofile);
            des::des_set<int>(si, ifile);
            break;

        case typelist(map):
            ofile.open(path);
            ifile.open(path);
            ser::ser_map<string, int>(msi0, ofile);
            des::des_map<string, int>(msi, ifile);
    }

    return 0;
}

#include "Bin_Ser.h"
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char const *argv[]) {
    int i, i0                   = 3;
    pair<string, int> psi, psi0 = make_pair("Good", 123);
    vector<int> vi, vi0         = {1, 3, 5, 7};
    list<int> li, li0           = {2, 4, 6, 8};
    set<int> si, si0            = {6, 7, 33, 9, 81, 31, 54};
    map<string, int> msi, msi0  = {pair<string, int>("SC", 666), pair<string, int>("cx", 999)};
    int *pi, *pi0               = &i0;
    int *pai;
    int pai0[] = {1, 45, 6, 3, 2};
    unique_ptr<int> upi, upi0     = unique_ptr<int>(new int(19));
    unique_ptr<int[]> upai, upai0 = unique_ptr<int[]>(new int[5]);
    shared_ptr<int> spi, spi0     = shared_ptr<int>(new int(89));

    for (auto i = 0; i < 5; i++)
        upai0[i] = (i + 1) * (i + 1);

    ofstream ofile;
    ifstream ifile;
    const string path = "./testfile/Bin_Ser_test.txt";

    vector<int> _vi1 = {2, 3, 4}, _vi2 = {5, 6, 7};
    map<string, int> _msi = {pair<string, int>("SC", 2), pair<string, int>("cx", 3)};
    set<string> _ss       = {"Hello", "World", "I", "Am"};
    pair<map<string, int>, set<string>> pmsiss, pmsiss0 = make_pair(_msi, _ss);

    ofile.open(path);
    ifile.open(path);
    enum typelist { ari, pair, vec, list, ptr, ptra, uptr, uptra, sptr, set, map, rr };

    switch (typelist(rr)) {
        case typelist(ari):
            Bin_Ser::Serializer(i0, ofile);
            ofile.close();
            Bin_Des::Deserializer(i, ifile);
            break;

        case typelist(pair):
            Bin_Ser::Serializer(psi0, ofile);
            ofile.close();
            Bin_Des::Deserializer(psi, ifile);
            break;

        case typelist(vec):
            Bin_Ser::Serializer(vi0, ofile);
            ofile.close();
            Bin_Des::Deserializer(vi, ifile);
            break;

        case typelist(list):
            Bin_Ser::Serializer(li0, ofile);
            ofile.close();
            Bin_Des::Deserializer(li, ifile);
            break;

        case typelist(ptr):
            Bin_Ser::Serializer(pi0, ofile);
            ofile.close();
            Bin_Des::Deserializer(pi, ifile);
            break;

        case typelist(ptra):
            Bin_Ser::Serializer(pai0, ofile, 5);
            ofile.close();
            Bin_Des::Deserializer(pai, ifile);
            for (auto i = 0; i < 5; i++)
                cerr << pai[i] << " ";
            break;

        case typelist(uptr):
            Bin_Ser::Serializer(upi0, ofile);
            ofile.close();
            Bin_Des::Deserializer(upi, ifile);
            break;

        case typelist(uptra):
            Bin_Ser::Serializer(upai0, ofile, 5);
            ofile.close();
            Bin_Des::Deserializer(upai, ifile);
            for (auto i = 0; i < 5; i++)
                cerr << upai[i] << " ";
            break;

        case typelist(sptr):
            Bin_Ser::Serializer(spi0, ofile);
            ofile.close();
            Bin_Des::Deserializer(spi, ifile);
            break;

        case typelist(set):
            Bin_Ser::Serializer(si0, ofile);
            ofile.close();
            Bin_Des::Deserializer(si, ifile);
            break;

        case typelist(map):
            Bin_Ser::Serializer(msi0, ofile);
            ofile.close();
            Bin_Des::Deserializer(msi, ifile);
            break;
        case typelist(rr):
            Bin_Ser::Serializer(pmsiss0, ofile);
            ofile.close();
            Bin_Des::Deserializer(pmsiss, ifile);
            break;
    }

    return 0;
}

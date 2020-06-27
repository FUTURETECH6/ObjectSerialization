#include "Serialize.h"

#include <list>
#include <map>
#include <set>
#include <utility>
#include <vector>

int main(int argc, char const *argv[]) {
    using namespace std;

    // Ser::enable_base64();
    // Des::enable_base64();
    Ser::disable_base64();
    Des::disable_base64();

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

    vector<int> _vi1 = {2, 3, 4}, _vi2 = {5, 6, 7};
    map<string, int> _msi = {pair<string, int>("SC", 2), pair<string, int>("cx", 3)};
    set<string> _ss       = {"Hello", "World", "I", "Am"};
    pair<map<string, int>, set<string>> pmsiss, pmsiss0 = make_pair(_msi, _ss);

    Ser::serialize(i0, "./testfile/bin_ari.txt");
    Des::deserialize(i, "./testfile/bin_ari.txt");

    Ser::serialize(psi0, "./testfile/bin_pair.txt");
    Des::deserialize(psi, "./testfile/bin_pair.txt");

    Ser::serialize(vi0, "./testfile/bin_vec.txt");
    Des::deserialize(vi, "./testfile/bin_vec.txt");

    Ser::serialize(li0, "./testfile/bin_list.txt");
    Des::deserialize(li, "./testfile/bin_list.txt");

    Ser::serialize(pi0, "./testfile/bin_ptr.txt");
    Des::deserialize(pi, "./testfile/bin_ptr.txt");

    // Ser::serialize(pai0, "./testfile/bin_ptra.txt", 5);
    // Des::deserialize(pai, "./testfile/bin_ptra.txt");
    // for (auto i = 0; i < 5; i++)
    //     cerr << pai[i] << " ";

    Ser::serialize(upi0, "./testfile/bin_uptr.txt");
    Des::deserialize(upi, "./testfile/bin_uptr.txt");

    Ser::serialize(upai0, "./testfile/bin_uptra.txt", 5);
    Des::deserialize(upai, "./testfile/bin_uptra.txt");
    for (auto i = 0; i < 5; i++)
        cerr << upai[i] << " ";

    Ser::serialize(spi0, "./testfile/bin_sptr.txt");
    Des::deserialize(spi, "./testfile/bin_sptr.txt");

    Ser::serialize(si0, "./testfile/bin_set.txt");
    Des::deserialize(si, "./testfile/bin_set.txt");

    Ser::serialize(msi0, "./testfile/bin_map.txt");
    Des::deserialize(msi, "./testfile/bin_map.txt");

    Ser::serialize(pmsiss0, "./testfile/bin_rr.txt");
    Des::deserialize(pmsiss, "./testfile/bin_rr.txt");

    // switch (typelist(rr)) {
    //     case typelist(ari):
    //         Ser::serialize(i0, "./testfile/bin_ari.txt");
    //         Des::deserialize(i, "./testfile/bin_ari.txt");
    //         break;

    //     case typelist(pair):
    //         Ser::serialize(psi0, "./testfile/bin_pair.txt");
    //         Des::deserialize(psi, "./testfile/bin_pair.txt");
    //         break;

    //     case typelist(vec):
    //         Ser::serialize(vi0, "./testfile/bin_vec.txt");
    //         Des::deserialize(vi, "./testfile/bin_vec.txt");
    //         break;

    //     case typelist(list):
    //         Ser::serialize(li0, "./testfile/bin_list.txt");
    //         Des::deserialize(li, "./testfile/bin_list.txt");
    //         break;

    //     case typelist(ptr):
    //         Ser::serialize(pi0, "./testfile/bin_ptr.txt");
    //         Des::deserialize(pi, "./testfile/bin_.txt");
    //         break;

    //     case typelist(ptra):
    //         Ser::serialize(pai0, "./testfile/bin_ptra.txt", 5);
    //         Des::deserialize(pai, "./testfile/bin_ptra.txt");
    //         for (auto i = 0; i < 5; i++)
    //             cerr << pai[i] << " ";
    //         break;

    //     case typelist(uptr):
    //         Ser::serialize(upi0, "./testfile/bin_uptr.txt");
    //         Des::deserialize(upi, "./testfile/bin_uptr.txt");
    //         break;

    //     case typelist(uptra):
    //         Ser::serialize(upai0, "./testfile/bin_uptra.txt", 5);
    //         Des::deserialize(upai, "./testfile/bin_uptra.txt");
    //         for (auto i = 0; i < 5; i++)
    //             cerr << upai[i] << " ";
    //         break;

    //     case typelist(sptr):
    //         Ser::serialize(spi0, "./testfile/bin_sptr.txt");
    //         Des::deserialize(spi, "./testfile/bin_sptr.txt");
    //         break;

    //     case typelist(set):
    //         Ser::serialize(si0, "./testfile/bin_set.txt");
    //         Des::deserialize(si, "./testfile/bin_set.txt");
    //         break;

    //     case typelist(map):
    //         Ser::serialize(msi0, "./testfile/bin_map.txt");
    //         Des::deserialize(msi, "./testfile/bin_map.txt");
    //         break;
    //     case typelist(rr):
    //         Ser::serialize(pmsiss0, "./testfile/bin_rr.txt");
    //         Des::deserialize(pmsiss, "./testfile/bin_rr.txt");
    //         break;
    // }

    return 0;
}

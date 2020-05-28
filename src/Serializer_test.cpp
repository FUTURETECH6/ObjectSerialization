#include "Serializer.h"
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <numeric> //accumulate 在此头文件定义
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char const *argv[]) {
    int i, i0                  = 3;
    vector<int> vi, vi0        = {1, 3, 5, 7};
    list<int> li, li0          = {2, 4, 6, 8};
    set<int> si, si0           = {6, 7, 33, 9, 81, 31, 54};
    map<string, int> msi, msi0 = {pair<string, int>("SC", 666), pair<string, int>("cx", 999)};
    unique_ptr<int> pi, pi0;

    /* Ser Test */
    // ostream &ofile = cout;
    ofstream ofile;
    ifstream ifile;
    const string path = "/Users/Ulysses/Desktop/Terminal Saved Output.txt";

    enum typelist { ari, vec, list, uptr, set, map };
    switch (typelist(set)) {
        case 0:
            ofile.open(path);
            ifile.open(path);
            ser::ser_ari<int>(i0, ofile);
            des::des_ari<int>(i, ifile);
            break;

        case 1:
            ofile.open(path);
            ifile.open(path);
            ser::ser_vec<int>(vi0, ofile);
            des::des_vec<int>(vi, ifile);
            break;

        case 2:
            ofile.open(path);
            ifile.open(path);
            ser::ser_list<int>(li0, ofile);
            des::des_list<int>(li, ifile);
            break;

        case 3:
            ofile.open(path);
            ifile.open(path);
            // ser::ser_uptr<int>(pi0, ifile);
            // des::des_uptr<int>(pi, ifile);
            break;

        case 4:
            ofile.open(path);
            ifile.open(path);
            ser::ser_set<int>(si0, ofile);
            des::des_set<int>(si, ifile);
            break;

        case 5:
            ofile.open(path);
            ifile.open(path);
            ser::ser_map<string, int>(msi0, ofile);
            des::des_map<string, int>(msi, ifile);
    }

    return 0;
}

#ifndef RSA_H
#define RSA_H
#include "..\operaciones.h"
class rsa{
public:
    rsa(int a);
    rsa(ZZ,ZZ,ZZ,ZZ);
    string cifrado(string);
    string descifrado(string);
    vector<ZZ> precalculo(ZZ,ZZ,ZZ);
    ZZ restochino(vector<ZZ>,ZZ);
    ZZ getd();
    ZZ gete();
    ZZ getn();
    ZZ getp();
    ZZ getq();
private:
    ZZ p;
    ZZ q;
    ZZ phi;
    ZZ n;
    ZZ n_ext;
    ZZ e_ext;
    ZZ e;
    ZZ d;
};
#endif // RSA_H

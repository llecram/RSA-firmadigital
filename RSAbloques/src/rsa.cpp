#include "rsa.h"
#include "rsa.h"
rsa::rsa(int a){
    p=GenPrime_ZZ(a);
    q=GenPrime_ZZ(a);
    n=p*q;
    phi=conv<ZZ>(((p-ZZ(1))*(q-ZZ(1))));
    e=generare(phi,a);
    d=inversa(modulo(phi,n),e);
    /*d=conv<ZZ>("12696576478809803");
    n=conv<ZZ>("33154604334023581");
    p=conv<ZZ>("239");
    q=conv<ZZ>("181");
    n_ext=conv<ZZ>("")
    e_ext=conv<ZZ>("")*/
}
rsa::rsa(ZZ e1,ZZ n1,ZZ n2,ZZ d1){
    e_ext=e1;
    n_ext=n1;
    n=n2;
    d=d1;
}
string rsa::cifrado(string mensaje){
    string result_aux;
    string tmp_1;
    string tmp_2;
    string tmp_3;
    vector <string> aux_1;
    vector <ZZ> aux_2;
    ZZ auxiliar;
    tmp_2=ZZ_to_string(n);
    ///variables para la firma digital
    string mi_n;
    mi_n=ZZ_to_string(n);
    string tempo1;
    ZZ tempo2;
    string tempo3;
    string tempo4;
    ZZ tempo5;
    string tempo6;
    int myblock=mi_n.size();

    for(int i=0;i<mensaje.size();i++){
        tmp_1+=arreglar_1(alfabeto.find(mensaje[i]));
    }
    while(modulo(ZZ(tmp_1.size()),ZZ(tmp_2.size()-1))!=0){
        tmp_1+=ZZ_to_string(ZZ(alfabeto.find('W')));
    }
    int bloques=tmp_2.size()-1;
    for(int i=0;i<tmp_1.size();i++){
        tmp_3+=tmp_1[i];
        if(tmp_3.size()==bloques){
            aux_1.push_back(tmp_3);
            tmp_3="";
        }
    }
    for(int i=0;i<aux_1.size();i++){
        auxiliar=bynexpo(string_to_ZZ(aux_1[i]),binario(e_ext),n_ext);
        result_aux+=arreglar_2(auxiliar,n_ext);
    }
    /// rubrica
    for(int i=0;i<result_aux.size();i++){
        tempo1+=result_aux[i];
        if(tempo1.size()==myblock){
            tempo2=bynexpo(string_to_ZZ(tempo1),binario(d),n);
            tempo3+=arreglar_2(tempo2,n);
        }
        if((i+1)==result_aux.size()){
            tempo2=bynexpo(string_to_ZZ(tempo1),binario(d),n);
            tempo3+=arreglar_2(tempo2,n);
        }
    }
    ///firma
    for(int i=0;i<tempo3.size();i++){
        tempo4+=tempo3[i];
        if(tempo4.size()==myblock){
            tempo5=bynexpo(string_to_ZZ(tempo4),binario(e_ext),n_ext);
            tempo6+=arreglar_2(tempo5,n_ext);
        }
        if((i+1)==tempo3.size()){
            tempo5=bynexpo(string_to_ZZ(tempo4),binario(e_ext),n_ext);
            tempo6+=arreglar_2(tempo5,n_ext);
        }
    }
    return tempo6;
}
string rsa::descifrado(string a){
    string result;
    string tmp_1=ZZ_to_string(n);
    string tmp_2;
    string tmp_3;
    string aux_2;
    string aux_3;
    ZZ auxiliar;
    vector <string> aux_1;
    int bloques=tmp_1.size();

    ///variables para la firma digital
    string mi_n;
    mi_n=ZZ_to_string(n);
    string tempo1;
    ZZ tempo2;
    string tempo3;
    string tempo4;
    ZZ tempo5;
    string tempo6;
    int myblock=mi_n.size();

    for(int i=0;i<a.size();i++){
        tmp_2+=a[i];
        if(tmp_2.size()==bloques){
            aux_1.push_back(tmp_2);
            tmp_2="";
        }
    }
    for(int i=0;i<aux_1.size();i++){
       auxiliar=restochino(precalculo(d,q,p),string_to_ZZ(aux_1[i]));
       aux_2+=arreglar_3(auxiliar,n);
    }
    /// rubrica
    for(int i=0;i<aux_2.size();i++){
        tempo1+=aux_2[i];
        if(tempo1.size()==myblock){
            tempo2=bynexpo(string_to_ZZ(tempo1),binario(e_ext),n_ext);
            tempo3+=arreglar_2(tempo2,n_ext);
        }
        if((i+1)==aux_2.size()){
            tempo2=bynexpo(string_to_ZZ(tempo1),binario(e_ext),n_ext);
            tempo3+=arreglar_2(tempo2,n_ext);
        }
    }
    ///firma
    for(int i=0;i<tempo3.size();i++){
        tempo4+=tempo3[i];
        if(tempo4.size()==myblock){
            tempo5=bynexpo(string_to_ZZ(tempo4),binario(d),n);
            tempo6+=arreglar_2(tempo5,n);
        }
        if((i+1)==tempo3.size()){
            tempo5=bynexpo(string_to_ZZ(tempo4),binario(d),n);
            tempo6+=arreglar_2(tempo5,n);
        }
    }
    for(int i=0;i<tempo6.size();i++){
        aux_3+=tempo6[i];
        string alf=int_to_string(alfabeto.size());
        if(aux_3.size()==alf.size()){
            //cout<<aux_3<<" ";
            result+=alfabeto[string_to_int(aux_3)];
            aux_3="";
        }
    }
    return result;
}
vector<ZZ> rsa::precalculo(ZZ d,ZZ q,ZZ p){
    vector<ZZ> auxiliar;
    ZZ dp;
    ZZ dq;
    dp=modulo(d,p-1);
    dq=modulo(d,q-1);
    ZZ p_inversa;
    p_inversa=bynexpo(p,binario(q-2),q);
    auxiliar.push_back(dp);
    auxiliar.push_back(dq);
    auxiliar.push_back(p_inversa);
    return auxiliar;
}
ZZ rsa::restochino(vector<ZZ> g,ZZ j){
    ZZ cp;
    ZZ cq;
    cp=modulo(j,p);
    cq=modulo(j,q);
    ZZ x1;
    ZZ x2;
    x1=bynexpo(cp,binario(g[0]),p);
    x2=bynexpo(cq,binario(g[1]),q);
    ZZ h;
    h=modulo(((x2-x1)*g[2]),q);
    ZZ x;
    x=x1+h*p;
    return x;
}
ZZ rsa::getd(){
    return d;
}
ZZ rsa::gete(){
    return e;
}
ZZ rsa::getn(){
    return n;
}
ZZ rsa::getp(){
    return p;
}
ZZ rsa::getq(){
    return q;
}

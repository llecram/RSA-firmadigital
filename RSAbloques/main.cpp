#include "rsa.h"
int main()
{
    //rsa objeto(8);
    //cout<<objeto.gete()<<endl<<objeto.getd()<<endl<<objeto.getn()<<endl<<objeto.getp()<<endl<<objeto.getq()<<endl;
    rsa objeto(conv<ZZ>("51"),conv<ZZ>("3127"),conv<ZZ>("11929"),conv<ZZ>("29143"));
    cout<<objeto.cifrado("HOLA");
}

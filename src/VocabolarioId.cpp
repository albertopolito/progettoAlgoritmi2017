#include "VocabolarioId.h"
#include<string>
using namespace std;
template<class T>
VocabolarioId<T>::VocabolarioId()
{

}
template<class T>
VocabolarioId<T>::~VocabolarioId()
{
    //dtor
}
template<class T>
VocabolarioId<T>::VocabolarioId(const VocabolarioId& other)
{
    //copy ctor
}

template<class T>
void VocabolarioId<T>::setNuovoElemento(const T id,const string testo)
{

}

template<class T>
string VocabolarioId<T>::getStringaDaId(const T id)
{

}

template<class T>
T VocabolarioId<T>::getIdDaStriga(const string testo)
{

}

//template class VocabolarioId<int>;
template class VocabolarioId<string>;

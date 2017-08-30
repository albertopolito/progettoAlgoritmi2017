#ifndef VOCABOLARIOID_H
#define VOCABOLARIOID_H
#include <string>
#include<vector>
#include<algorithm>
using namespace std;
template<class T>
class VocabolarioId
{
    struct _vocabolo{
        T _id;
        string _testo;
    };
    public:
        VocabolarioId();
        virtual ~VocabolarioId();
        VocabolarioId(const VocabolarioId& other);
        void setNuovoElemento(const T id,const string testo);
        string getStringaDaId(const T id);
        T getIdDaStriga(const string testo);
        vector<T> getTuttiGliId(); ///riempie un vettore con tutte le stringhe che sono all'interno del vocabolario
        bool controlloSintattico();
    protected:

    private:

    vector<_vocabolo> _vocaboli;
};

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
T VocabolarioId<T>:: getIdDaStriga(const string testo)
{

}

template<class T>
vector<T> VocabolarioId<T>:: getTuttiGliId()
{

}

template<class T>
bool VocabolarioId<T>:: controlloSintattico()
{

}

#endif // VOCABOLARIOID_H

#ifndef VOCABOLARIOID_H
#define VOCABOLARIOID_H
#include <string>
#include<vector>
#include<algorithm>
#include<iostream>
using namespace std;
template<class T>
class VocabolarioId
{
    struct _vocabolo{
        T _id;
        string _testo;
        _vocabolo(const T id, const string testo)
        {
            _id=id;
            _testo=testo;
        }
    };

    struct f_vocabolo{
        T f_id;
        string f_testo;
        bool f_ricerca_id_testo;
        f_vocabolo(T id) : f_id(id)
        {
            f_ricerca_id_testo=0;
        }

        f_vocabolo(const string testo, const bool diverso_da_template) : f_testo(testo)
        {
            f_ricerca_id_testo=1;
        }

        bool operator () ( const _vocabolo& f_vocabolo ) const
        {
            return ((!f_ricerca_id_testo&&f_vocabolo._id==f_id)||(f_ricerca_id_testo&&f_vocabolo._testo==f_testo));
        }
    };
    public:
        VocabolarioId();
        virtual ~VocabolarioId();
        VocabolarioId(const VocabolarioId& other);
        void setNuovoElemento(const T id,const string testo);
        string getStringaDaId(const T id);
        T getIdDaStriga(const string testo);
        vector<T> getTuttiGliId(); ///riempie un vettore con tutti gli id che sono all'interno del vocabolario
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
VocabolarioId<T>::VocabolarioId(const VocabolarioId& to_copy)
{
    this->_vocaboli=to_copy._vocaboli;
}

template<class T>
void VocabolarioId<T>::setNuovoElemento(const T id,const string testo)
{
    _vocaboli.push_back(_vocabolo(id,testo));
}

template<class T>
string VocabolarioId<T>::getStringaDaId(const T id)
{
    typename vector<_vocabolo>::iterator it;
    it=find_if(_vocaboli.begin(),_vocaboli.end(),f_vocabolo(id));
    if(it!=_vocaboli.end())
    {
        return _vocabolo(*it)._testo;
    }else{
        return "";
    }
}

template<class T>
T VocabolarioId<T>:: getIdDaStriga(const string testo)
{
    typename vector<_vocabolo>::iterator it;
    it=find_if(_vocaboli.begin(),_vocaboli.end(),f_vocabolo(testo,0));
    if(it!=_vocaboli.end())
    {
        return _vocabolo(*it)._id;
    }else{
        return T();
    }
}

template<class T>
vector<T> VocabolarioId<T>:: getTuttiGliId()
{
    vector<T> vettore_di_ritorno;
    for(typename vector<_vocabolo>::iterator it=_vocaboli.begin(); it!=_vocaboli.end();it++)
    {
        vettore_di_ritorno.push_back(_vocabolo(*it)._id);
    }
    return vettore_di_ritorno;
}

template<class T>
bool VocabolarioId<T>:: controlloSintattico()
{
    for(typename vector<_vocabolo>::iterator it=_vocaboli.begin();it!=_vocaboli.end();it++)
    {
        typename vector<_vocabolo>::iterator it_id=find_if(_vocaboli.begin(),it,f_vocabolo(_vocabolo(*it)._id));
        typename vector<_vocabolo>::iterator it_testo=find_if(_vocaboli.begin(),it,f_vocabolo(_vocabolo(*it)._testo,0));
        if((it_id!=it)||(it_testo!=it))
        {
            cout<<_vocabolo(*it)._testo<<endl;
            return 1;
        }
    }
    return 0;
}

#endif // VOCABOLARIOID_H

#ifndef VOCABOLARIOID_HPP_INCLUDED
#define VOCABOLARIOID_HPP_INCLUDED
#include <string>
#include<vector>
#include<algorithm>
using namespace std;
template<class T>
class VocabolarioId
{
    ///struttura di un vocabolo con costruttore
    struct _vocabolo{
        T _id;
        string _testo;
        _vocabolo(const T& id, const string& testo)
        {
            _id=id;
            _testo=testo;
        }
    };
    ///struttura che serve per ricercare un vocabolo all'interno del vocabolario dando in ingresso un id o una stringa
    struct f_vocabolo{
        T f_id;
        string f_testo;
        bool f_ricerca_id_testo;
        f_vocabolo(const T& id) : f_id(id)
        {
            f_ricerca_id_testo=0;
        }

        f_vocabolo(const string& testo, const bool& diverso_da_template) : f_testo(testo)
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
        VocabolarioId(const VocabolarioId& to_copy);
        ///immette un nuovo elemento all'interno della struttura dati
        void setNuovoElemento(const T& id,const string& testo);
        ///ricerca il vocabolo tramite il suo id e restituisce la stringa correlata
        const string getStringaDaId(const T& id);
        ///ricerca il vocabolo tramite la sua stringa e restituisce l'id correlato
        const T getIdDaStriga(const string& testo);
        ///riempie un vettore con tutti gli id che sono all'interno del vocabolario
        vector<T> getTuttiGliId();
        ///esegue il controllo sintattico sulla struttura trovando eventuali ripetizioni di id o di stringhe
        const bool controlloSintattico();
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
void VocabolarioId<T>::setNuovoElemento(const T& id,const string& testo)
{
    _vocaboli.push_back(_vocabolo(id,testo));
}

template<class T>
const string VocabolarioId<T>::getStringaDaId(const T& id)
{
    //tramite la struttura di find e il find_if ricerca il vocabolo attraverso il suo id
    typename vector<_vocabolo>::iterator it;
    it=find_if(_vocaboli.begin(),_vocaboli.end(),f_vocabolo(id));
    if(it!=_vocaboli.end())
    {
        return _vocabolo(*it)._testo;
    }else{
        return "";  //se non lo trova ritorna uja stringa vuota
    }
}

template<class T>
const T VocabolarioId<T>:: getIdDaStriga(const string& testo)
{
    //tramite la struttura di find e il find_if ricerca il vocabolo attraverso la sua stringa
    typename vector<_vocabolo>::iterator it;
    it=find_if(_vocaboli.begin(),_vocaboli.end(),f_vocabolo(testo,0));
    if(it!=_vocaboli.end())
    {
        return _vocabolo(*it)._id;
    }else{
        return T();//se non lo trova ritorna il valore nullo del tipo template T
    }
}

template<class T>
vector<T> VocabolarioId<T>:: getTuttiGliId()
{
    vector<T> vettore_di_ritorno;
    //inserisce in un vettore tutti gli id dei vocaboli
    for(typename vector<_vocabolo>::iterator it=_vocaboli.begin(); it!=_vocaboli.end();it++)
    {
        vettore_di_ritorno.push_back(_vocabolo(*it)._id);
    }
    return vettore_di_ritorno;
}

template<class T>
const bool VocabolarioId<T>:: controlloSintattico()
{
    //tramite la struttura di find e i find_if controlla che non vi siano stringhe uguali o id uguali
    for(typename vector<_vocabolo>::iterator it=_vocaboli.begin();it!=_vocaboli.end();it++)
    {
        typename vector<_vocabolo>::iterator it_id=find_if(_vocaboli.begin(),it,f_vocabolo(_vocabolo(*it)._id));
        typename vector<_vocabolo>::iterator it_testo=find_if(_vocaboli.begin(),it,f_vocabolo(_vocabolo(*it)._testo,0));
        if((it_id!=it)||(it_testo!=it))
        {
            return 1;
        }
    }
    return 0;
}
#endif // VOCABOLARIOID_HPP_INCLUDED

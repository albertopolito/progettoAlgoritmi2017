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
        vector<T> getTuttiGliId(); ///riempie un vettore con tutti gli id che sono all'interno del vocabolario
        bool controlloSintattico();
    protected:

    private:

    vector<_vocabolo> _vocaboli;
};

#endif // VOCABOLARIOID_H

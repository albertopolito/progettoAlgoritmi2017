#ifndef NODO_H
#define NODO_H
#include <string>
#include<vector>
#include<algorithm>
using namespace std;
template<class T,class R>
class Nodo
{
    struct adiacenza
        {
            short int _colore_arco;
            R _arco;
            Nodo *_nodo_adiacente;
        };
    public:
        Nodo(T id_domanda);
        virtual ~Nodo();
        Nodo(const Nodo& other);
        void setAdiacenza(const R arco,const Nodo *nodo_adiacente);
        T getContenuto();
        void setContenuto(const T nuovo_contenuto);
        vector<adiacenza> getAdiacenze();
        void setNuovoColore(const short int nuovo_colore);
        short int getColore();
        void setColoreArco(const short int nuovo_colore,Nodo *nodo_adiacente);
        short int getColoreArco(const Nodo *nodo_adiacente);
    protected:

    private:

        vector<adiacenza> _adiacenze;
        T _contenuto;
        short int _colore_nodo;
};

#endif // NODO_H

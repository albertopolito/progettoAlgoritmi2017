#ifndef NODO_H
#define NODO_H
#include <string>
#include<vector>
#define NEUTRO 0
#define TREE 1
#define BACKWARD 2
#define FORWARD 3
#define CROSS 4

using namespace std;
template<class T,class R>
class Nodo
{
    struct adiacenza
        {
            short int _tipologia_arco;
            R _arco;
            Nodo *_nodo_adiacente;
        };
    public:
        Nodo(T contenuto);
        virtual ~Nodo();
        Nodo(const Nodo& to_copy);
        void setAdiacenza(const R arco,const Nodo *nodo_adiacente);
        T getContenuto();
        void setContenuto(const T nuovo_contenuto);
        //vector<adiacenza> getAdiacenze();
        void setNuovoColore(const short int nuovo_colore);
        short int getColore();
        void setTipologiaArco(const short int nuova_tipologia,const Nodo *nodo_adiacente);
        Nodo<T,R> findArcoPerTipologia(const short int tipologia_ricerca);
        void resettaTipologiaArchi();
        vector<R> getPesoArchi();
        vector<Nodo<T,R> > getNodiAdiacentiDaPesoArco(R peso_arco);
    protected:

    private:

        vector<adiacenza> _adiacenze;
        T _contenuto;
        short int _colore_nodo;
        int _tempo_inizio_visita;
        int _tempo_fine_visita;
};

#endif // NODO_H

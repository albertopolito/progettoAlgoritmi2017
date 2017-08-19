#ifndef GRAFO_H
#define GRAFO_H
#include"Nodo.h"
#include <string>
#include<vector>
#include<algorithm>
#define NEUTRO 0
#define TREE 1
#define BACKWARD 2
#define FORWARD 3
#define CROSS 4
using namespace std;
template<class T,class R>
class Grafo
{
    public:
        Grafo();
        virtual ~Grafo();
        Grafo(const Grafo& other);
        void setNuovoNodo(const T contenuto,const R arco,const T contenuto_nodo_adiacente);
        vector<R> daContenutoAnalisiInProfondita(const T contenuto);
        vector<T> daArcoAnalisiInProfondita(const R arco);
        bool aciclico();
    protected:

    private:
        vector<Nodo<T,R>*> _lista_nodi;
        //secondo vettore su quaderno
        void analisiTotaleInProfondita();
};

#endif // GRAFO_H

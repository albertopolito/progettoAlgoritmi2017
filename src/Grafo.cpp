#include "Grafo.h"
#include"Nodo.h"
#include <string>
#include<vector>
#include<algorithm>
//tipologie degli archi
#define NEUTRO 0
#define TREE 1
#define BACKWARD 2
#define FORWARD 3
#define CROSS 4
//colori dei nodi
#define WHITE 0
#define GREY 1
#define BLACK 2
template<class T,class R>
Grafo<T,R>::Grafo()
{
    //ctor
}

template<class T,class R>
Grafo<T,R>::~Grafo()
{
    //dtor
}

template<class T,class R>
Grafo<T,R>::Grafo(const Grafo& other)
{
    //copy ctor
}

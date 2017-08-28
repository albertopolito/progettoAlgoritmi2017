#include "FileRisposte.h"
#include <iostream>

template<class R>
FileRisposte<R>::~FileRisposte()
{
    //dtor
}

template<class R>
bool FileRisposte<R>::leggiFile()
{
    return 0;
}

template<class R>
string FileRisposte<R>::getRispostaDaId(const R id)
{
    return _vocabolario_risposte.getIdDaStriga(id);
}


template class FileRisposte<string>;
//template class FileRisposte<int>;         //non funziona se li mettiamo entrambi,
                                            //stessa cosa per VocabolarioId.cpp

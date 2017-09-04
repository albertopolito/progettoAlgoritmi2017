#ifndef FILELOG_H
#define FILELOG_H
#include <string>
#include<vector>
#include<algorithm>
#include "FileOutput.h"
#include <iostream>
using namespace std;

template<class T, class R>
class FileLog : public FileOutput
{
    public:
        FileLog(const string nome_file) : FileOutput(nome_file)
        {
        };
        virtual ~FileLog();
        void apriFileLog();
        bool getErrore();
        FileLog(const FileLog& other);
        void chiudiFileLog();
        void scriviFileOutput(const R id_risposta,const T id_domanda, const string domanda, const string risposta, const vector<T> domande_successive);
    protected:
    private:
        bool _errore_apertura;
};
template<class T, class R>
FileLog<T,R>::~FileLog()
{
    //dtor
}

template<class T, class R>
FileLog<T,R>::FileLog(const FileLog& other)
{
    //copy ctor
}

template<class T, class R>
void FileLog<T,R>::apriFileLog()
{
    _errore_apertura=apriFileOutput();
}

template<class T, class R>
bool FileLog<T,R>::getErrore()
{
    return _errore_apertura;
}

template<class T, class R>
void FileLog<T,R>::chiudiFileLog()
{
    chiudiFileOutput();
}


template<class T, class R>
// Scrive il file di log
void FileLog<T,R>::scriviFileOutput(const R id_risposta,const T id_domanda, const string domanda, const string risposta, const vector<T> domande_successive)
{

    if(!_errore_apertura)
    {
        _file_output << id_domanda << " " << id_risposta << "\n";
        _file_output << domanda << " "<< risposta << "\n" << "Nuove domande:";
        for (typename vector<T>::iterator it=domande_successive.begin();it!=domande_successive.end(); it++){
            _file_output << " "<< *it;
        }
        _file_output << "\n";
    }
}

#endif // FILELOG_H

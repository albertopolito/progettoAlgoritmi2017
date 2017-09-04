#ifndef FILELOG_H
#define FILELOG_H
#include <string>
#include<vector>
#include<algorithm>
#include "FileOutput.h"
using namespace std;

template<class T, class R>
class FileLog : public FileOutput
{
    public:
        FileLog(const string nome_file) : FileOutput(nome_file)
          {
        };
        virtual ~FileLog();
        FileLog(const FileLog& other);
        FileLog(){
        };
        void scriviFileOutput(const R id_risposta,const T id_domanda, const string domanda, const string risposta, const vector<T> domande_successive);
    protected:

    private:
        string _log_file_name;

        ofstream _log_file;

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
// Scrive il file di log
void FileLog<T, R>::scriviFileOutput(const R id_risposta,const T id_domanda, const string domanda, const string risposta, const vector<T> domande_successive){
    cout << "Inserisci nome del file di log: " << endl;
    cin >> _log_file_name;

    ifstream f(_log_file_name.c_str());

    if (!f.good()){
        cout << "File non esistente" <<endl;
        exit(EXIT_FAILURE);
}

_log_file.open(_log_file_name.c_str(), ofstream::app);

_log_file << id_domanda << " " << id_risposta << "\n";

_log_file << domanda << " "<< risposta << "\n" << "Nuove domande:";

for (int i = 0; i <domande_successive.size(); i++){
    _log_file << " "<< domande_successive.at(i) ;
}
_log_file << "\n";

_log_file.close();
}

#endif // FILELOG_H

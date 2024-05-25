#include "manoBiblioteka.h"

void tvarkymas (string& zodis, const int pos){

    string mark = "“";
    size_t rasti = zodis.find(mark);
    
    if (rasti == string::npos) {
        rasti = zodis.find("”");
        mark = "”";
    }
    if (rasti == string::npos) {
        rasti = zodis.find("„");
        mark = "„";
    }
    if (rasti == string::npos) {
        rasti = zodis.find("–");
        mark = "–";
    }
    if (rasti == string::npos) {
        rasti = zodis.find("-");
        mark = "-";
    }
    if (rasti == string::npos) {
        rasti = zodis.find(",");
        mark = ",";
    }
    if (rasti == string::npos) {
        rasti = zodis.find('"');
        mark = '"';
    }
    if (rasti != string::npos) {
        /// istrinamas simbolis
        zodis.erase(rasti, mark.length());
    }

    /// atskirai rasti zodzius su "." 
    if (!zodis.empty() && (zodis.front() == '.' || zodis.back() == '.')) {
        if (zodis.front() == '.') {
            zodis.erase(0, 1);
        }
        if (!zodis.empty() && zodis.back() == '.') {
            zodis.erase(zodis.size() - 1, 1);
        }
    }

}

bool ArLink ( const string& link )
{    
    return link.find('.') != string::npos;
}

void spausdinimas(map <string, vector <int>>& zodziai){

    ofstream isvesti ("rez.txt");

    for( auto it = zodziai.begin(); it!= zodziai.end(); it++){
        if(it->second.size() >1){
            isvesti<< "„" << it->first << "“ buvo paminetas: "<<it->second.size()<<" kartus ";
            isvesti<<"eiluteses: ";

            for(size_t i=0; i < it->second.size(); ++i){
                isvesti<<it->second[i]<<" ";
                if(i< it->second.size()-1) isvesti <<", ";
            }
            isvesti<<endl;
        }              
    }
    
    isvesti<<endl<<"Rasti URL: "<<endl;

    for( auto it = zodziai.begin(); it!= zodziai.end(); it++){
        
        if( ArLink(it->first) ){
            isvesti<<it->first<<endl;
        }
    }

    isvesti.close();
}

void pridetiMAP(map <string, vector <int>>& zodziai, int& eil, string& zodis){

    if (zodis.empty())  return;

    auto it = zodziai.find(zodis);              /// iesko ar jau yra paminetas toks zodis
    /// jei zodzio neranda, tai iteratoriu grazina i zodziai.end()
    if(it == zodziai.end()){
        vector<int>eilute;
        eilute.push_back(eil);

        auto pp = zodziai.insert(pair<string, vector<int>>(zodis, eilute));

        // cout << pp.first->first << endl;

    }
    else{  /// kai toks zodis jau buvo paminetas
        it->second.push_back(eil);
        // cout<<it->first<<endl;
    }


}

void skaitymas(map <string, vector <int>>& zodziai, vector <string> linkai){

    ifstream failas("tekstas.txt");
    SetConsoleOutputCP(CP_UTF8);                                            /// naudoja lietuviska abecele
 
    try
    {
        if (!failas.is_open()) /// patikrina ar failas egzustuoja
        {
            throw std::runtime_error("Failas nerastas");
        }
    }
    catch (const std::exception &e)
    {
        cerr << "Klaida: " << e.what() << endl;
        cout << endl;
        return;
    }


    // char raide;
    string line, zodis;
    int eilute=0;

    /// Prasideda skaitymas
    while (getline(failas, line))
    {
        
        istringstream dalijimas(line); /// leidzia is eilutes skaityti kaip is failo
        eilute++;
        cout<<eilute<<endl;

        while( dalijimas >> zodis){

            std::transform(zodis.begin(), zodis.end(), zodis.begin(), ::towlower);
            
            tvarkymas(zodis, 0);
            tvarkymas(zodis, zodis.length()-1);
            // cout<<zodis<<" ";

            // if(ArLink(zodis)) linkai.push_back(zodis);
           
            pridetiMAP(zodziai, eilute, zodis);

        }
        
    }



    failas.close();

}    


#include "manoBiblioteka.h"


void tvarkymas (string& zodis, const int pos){


    vector<string> marks = {"“", "”", "„", "–", "-", ",", ")", "(", "[", "]", "%", "~"};

    for (const string& mark : marks) {
        size_t rasti = zodis.find(mark);
        while (rasti != string::npos) {
            zodis.erase(rasti, mark.length());
            rasti = zodis.find(mark); 
        }
    }

    /// istrina skaicius
    auto it = remove_if(zodis.begin(), zodis.end(), ::isdigit);
    zodis.erase(it, zodis.end());

    /// istrina zodzius su "."
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
    // const std::regex httpsPattern
    //         ("https?:\\/\\/(www\\.)?[-a-zA-Z0-9@:%._\\+~#=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%_\\+.~#?&//=]*)");
    // const std::regex wwwPattern
    //         ("[-a-zA-Z0-9@:%._\\+~#=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%_\\+.~#?&//=]*)");

    // return (std::regex_match(link, httpsPattern) || std::regex_match(link, wwwPattern));

    return (link.find(".com") != string::npos) || 
           (link.find(".lt") != string::npos)  || 
           (link.find("http") != string::npos) || 
           (link.find("www") != string::npos);
    /*
    npos reiškia eilučių paieškų sąlygą „nerasta“, reikšmė paprastai yra didžiausia dydis,
    kurį nurodo dydis_t tipas, nurodant, kad eilutėje nerasta simbolio arba poeilutės.
    */ 
}

bool ArEmail(const std::string& email)
{
    return email.find('@') != string::npos; 
}

void spausdinimas(map <string, vector <int>>& zodziai,  vector <string>& linkai){

    ofstream isvesti ("rez.txt");  

    for( auto it = zodziai.begin(); it!= zodziai.end(); it++){
        if(it->second.size() >1){
            isvesti<< "„" << it->first << "“ buvo paminetas: "<<it->second.size()<<" kartus ";
            isvesti<<"eiluteses: ";

            for(size_t i=0; i < it->second.size(); ++i){
                isvesti<<it->second[i];
                if(i< it->second.size()-1) isvesti <<", ";
            }
            isvesti<<endl;
        }     
    }

    isvesti<<endl<<"Rasti URL: "<<endl;

    for(size_t i=0; i<=linkai.size(); i++){
        isvesti<<linkai[i]<<endl;
    }

    isvesti.close();
}

void pridetiMAP(map <string, vector <int>>& zodziai, int& eil, string& zodis, vector <string>& linkai){

    if (zodis.empty())  return;

    auto it = zodziai.find(zodis);              /// iesko ar jau yra paminetas toks zodis
    /// jei zodzio neranda, tai iteratoriu grazina i zodziai.end()
    if(ArLink(zodis) || ArEmail(zodis)) {
        linkai.push_back(zodis); 
             
    }
    else if(it == zodziai.end()){
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

void skaitymas(map <string, vector <int>>& zodziai,  vector <string>& linkai){

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

    string line, zodis;
    int eilute=0;

    /// Prasideda skaitymas
    while (getline(failas, line))
    {
        
        istringstream dalijimas(line); /// leidzia is eilutes skaityti kaip is failo
        eilute++;

        while( dalijimas >> zodis){

            std::transform(zodis.begin(), zodis.end(), zodis.begin(), ::towlower);
            
            tvarkymas(zodis, 0);
            tvarkymas(zodis, zodis.length()-1);    
            pridetiMAP(zodziai, eilute, zodis, linkai);

        }
        
    }

    failas.close();

}    


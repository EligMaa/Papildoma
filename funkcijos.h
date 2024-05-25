#include "manoBiblioteka.h"


void tvarkymas (string& zodis, const int pos){

    size_t rasti = zodis.find("“");
    string mark = "“";
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
    if (rasti != string::npos) {
        /// istrinamas simbolis
        zodis.erase(rasti, mark.length());
    }

}

bool ArLink (const string& link)
{
    
    const regex https
            ("https?:\\/\\/(www\\.)?[-a-zA-Z0-9@:%._\\+~#=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%_\\+.~#?&//=]*)");
    const regex www
            ("[-a-zA-Z0-9@:%._\\+~#=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%_\\+.~#?&//=]*)");

    // try to match the string with the regular expressions
    return (regex_match(link, https) || regex_match(link, www));
}

void skaitymas(map <string, vector <int>> zodziai){

    ifstream failas("tekstas.txt");
    SetConsoleOutputCP(CP_UTF8);

  
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
    int eilute, zodSk=0;

    /// Prasideda skaitymas
    while (getline(failas, line))
    {
        
        istringstream dalijimas(line); /// leidzia is eilutes skaityti kaip is failo
        eilute++;

        while( dalijimas >> zodis){

            std::transform(zodis.begin(), zodis.end(), zodis.begin(), ::towlower);
            
            zodSk++;
            tvarkymas(zodis, 0);
            tvarkymas(zodis, zodis.length()-1);
            
            // if(ArLink(zodis)) cout<<"AAAAAAAAAAAAAAAAAAAAA";
            cout<<zodis<<" ";

        }
        
        
        
    }



    failas.close();

}    


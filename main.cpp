#include "manoBiblioteka.h"
#include "funkcijos.h"

int main() {

    map <string, vector <int> > zodziai;
    vector <string> linkai; 

    skaitymas(zodziai, linkai);
    spausdinimas(zodziai);

   

    return 0;
}


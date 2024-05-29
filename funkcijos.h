#include "manoBiblioteka.h"

bool ArLink (  string& link );
bool ArEmail( string& email);

void tvarkymas (string& zodis, const int pos){


    vector<string> marks = {
        "“", "”", "„", "–", "-", ",", ")", "(", "[", "]", "%", "~", "°", ":", "\"", "`", "&", "+", 
        ".", ";", "!", "?", "/", "\\", "|", "{", "}", "<", ">", "=", "*", "^", "#", "@", "$", 
        "'", "_", "…", "•", "″", "—"
    };

    if( !(ArLink(zodis))){
    for (const string& mark : marks) {
            size_t rasti = zodis.find(mark);
            while (rasti != string::npos) {
                zodis.erase(rasti, mark.length());
                rasti = zodis.find(mark); 
            }
        }
    }
    /// istrina skaicius
    if( !(ArLink(zodis)||ArEmail(zodis))){ 
        auto it = remove_if(zodis.begin(), zodis.end(), ::isdigit);
        zodis.erase(it, zodis.end());
    }

    // if( (ArLink(zodis)||ArEmail(zodis))){ 
    //     // auto it = remove_if(zodis.end()-2, zodis.end(), ::isdigit);
    //     // zodis.erase(it, zodis.end());
    // }

    /// istrina su "."
    if (!zodis.empty() && (zodis.front() == '.' || zodis.back() == '.')) {
        if (zodis.front() == '.') {
            zodis.erase(0, 1);
        }
        if (!zodis.empty() && zodis.back() == '.') {
            zodis.erase(zodis.size() - 1, 1);
        }
    }
    
    size_t dot_pos = zodis.find('.');
    if (dot_pos != string::npos && dot_pos + 1 < zodis.size() && isdigit(zodis[dot_pos + 1])) {
        zodis.clear();
    }


    

}

bool containsValidDomainExtension(const std::string& link) {
    static const std::unordered_set<std::string> domainExtensions = {
        ".lt", ".eu", ".com", ".net", ".abogado", ".ac", ".academy", ".accountant", ".accountants", 
        ".actor", ".adult", ".ae", ".af", ".africa", ".ag", ".agency", ".ai", ".airforce", ".al", 
        ".alsace", ".am", ".amsterdam", ".apartments", ".app", ".archi", ".army", ".art", ".as", 
        ".asia", ".associates", ".at", ".attorney", ".auction", ".audio", ".auto", ".autos", ".ax", 
        ".ba", ".baby", ".band", ".bar", ".barcelona", ".bargains", ".basketball", ".bayern", ".be", 
        ".beauty", ".beer", ".berlin", ".best", ".bet", ".bg", ".bh", ".bi", ".bible", ".bid", ".bike", 
        ".bingo", ".bio", ".biz", ".bj", ".black", ".blackfriday", ".blog", ".blue", ".boats", ".bond", 
        ".boo", ".boutique", ".com.br", ".org.br", ".net.br", ".broker", ".brussels", ".build", 
        ".builders", ".business", ".buzz", ".co.bw", ".by", ".com.by", ".bz", ".ca", ".cab", ".cafe", 
        ".cam", ".camera", ".camp", ".capetown", ".capital", ".car", ".cards", ".care", ".career", 
        ".careers", ".cars", ".casa", ".case", ".cash", ".casino", ".cat", ".catering", ".cc", 
        ".center", ".ceo", ".cf", ".cfd", ".cg", ".ch", ".charity", ".chat", ".cheap", ".christmas", 
        ".church", ".ci", ".city", ".cl", ".claims", ".cleaning", ".click", ".clinic", ".clothing", 
        ".cloud", ".club", ".cm", ".com.cn", ".net.cn", ".cn", ".org.cn", ".cn-com", ".co", ".coach", 
        ".codes", ".coffee", ".coiin", ".college", ".cologne", ".eu.com", ".comcom", ".comesc", 
        ".community", ".company", ".computer", ".comsec", ".comua", ".comza", ".condos", ".construction", 
        ".consulting", ".contact", ".contractors", ".conza", ".cooking", ".cool", ".coop", ".country", 
        ".coupons", ".cr", ".credit", ".creditcard", ".cricket", ".cruises", ".cx", ".com.cy", ".cymru", 
        ".cyou", ".cz", ".dad", ".dance", ".date", ".dating", ".day", ".de", ".dealer", ".deals", 
        ".degree", ".delivery", ".democrat", ".dental", ".dentist", ".desi", ".design", ".dev", 
        ".diamonds", ".diet", ".digital", ".direct", ".directory", ".discount", ".dk", ".dm", ".do", 
        ".doctor", ".dog", ".domains", ".download", ".durban", ".earth", ".ec", ".eco", ".education", 
        ".ee", ".com.eg", ".email", ".energy", ".engineer", ".engineering", ".enterprises", ".equipment", 
        ".es", ".estate", ".et", ".eus", ".events", ".exchange", ".expert", ".exposed", ".express", 
        ".fail", ".faith", ".family", ".fan", ".fans", ".farm", ".fashion", ".feedback", ".fi", ".film", 
        ".finance", ".financial", ".fish", ".fishing", ".fit", ".fitness", ".flights", ".florist", 
        ".flowers", ".fm", ".fo", ".foo", ".food", ".football", ".forex", ".forsale", ".forum", 
        ".foundation", ".fr", ".fun", ".fund", ".furniture", ".futbol", ".fyi", ".ga", ".gal", ".gallery", 
        ".game", ".games", ".garden", ".gay", ".gd", ".ge", ".gent", ".gf", ".gg", ".gift", ".gifts", 
        ".gives", ".gl", ".glass", ".global", ".gmbh", ".com.gn", ".gold", ".golf", ".gp", ".gq", ".gr", 
        ".graphics", ".gratis", ".green", ".gripe", ".group", ".gs", ".gt", ".guide", ".guitars", ".guru", 
        ".gy", ".hair", ".hamburg", ".haus", ".health", ".healthcare", ".help", ".hiphop", ".hk", ".hm", 
        ".hn", ".hockey", ".holdings", ".holiday", ".homes", ".horse", ".hospital", ".host", ".hosting", 
        ".house", ".how", ".hr", ".com.hr", ".ht", ".hu", ".icu", ".co.id", ".id", ".ie", ".co.il", 
        ".org.il", ".im", ".immo", ".immobilien", ".in", ".inc", ".industries", ".info", ".ing", ".ink", 
        ".institute", ".insure", ".international", ".investments", ".io", ".iq", ".ir", ".irish", ".is", 
        ".ist", ".it", ".je", ".jetzt", ".jewelry", ".joburg", ".jp", ".juegos", ".kaufen", ".ke", 
        ".co.ke", ".ki", ".kids", ".kim", ".kitchen", ".kiwi", ".koeln", ".kr", ".la", ".land", ".lat", 
        ".lawyer", ".lc", ".lease", ".legal", ".lgbt", ".li", ".life", ".lighting", ".limited", ".limo", 
        ".link", ".live", ".living", ".lk", ".llc", ".loan", ".loans", ".lol", ".london", ".love", ".ltd", 
        ".ltda", ".lu", ".luxe", ".luxury", ".lv", ".ly", ".ma", ".madrid", ".maison", ".makeup", 
        ".management", ".market", ".marketing", ".markets", ".mba", ".md", ".me", ".media", ".meme", 
        ".memorial", ".men", ".menu", ".mg", ".miami", ".mk", ".ml", ".com.mm", ".mn", ".mobi", ".moda", 
        ".moe", ".mom", ".money", ".monster", ".mortgage", ".motorcycles", ".mov", ".movie", ".mq", ".mr", 
        ".ms", ".com.mt", ".mt", ".mu", ".museum", ".music", ".mw", ".mx", ".my", ".co.mz", ".na", 
        ".co.na", ".nagoya", ".name", ".navy", ".ne", ".network", ".news", ".nexus", ".nf", ".ng", ".ngo", 
        ".com.ni", ".ni", ".ninja", ".nl", ".no", ".nu", ".nyc", ".nz", ".org.nz", ".co.nz", ".observer", 
        ".one", ".ong", ".onl", ".online", ".ooo", ".org", ".organic", ".com.pa", ".pa", ".page", ".paris", 
        ".partners", ".parts", ".party", ".pe", ".pet", ".ph", ".phd", ".photo", ".photography", ".photos", 
        ".pics", ".pictures", ".pink", ".pizza", ".pk", ".com.pl", ".pl", ".plumbing", ".plus", ".pm", 
        ".poker", ".porn", ".pr", ".press", ".pro", ".productions", ".promo", ".properties", ".property", 
        ".protection", ".ps", ".pt", ".pub", ".pw", ".com.py", ".qa", ".quebec", ".quest", ".racing", 
        ".radio", ".re", ".realestate", ".realty", ".recipes", ".red", ".rehab", ".reise", ".reisen", 
        ".reit", ".rent", ".rentals", ".repair", ".report", ".republican", ".rest", ".restaurant", 
        ".review", ".reviews", ".rip", ".ro", ".rocks", ".rodeo", ".rs", ".ruhr", ".run", ".rw", ".sa", 
        ".saarland", ".sale", ".salon", ".sarl", ".sb", ".sbs", ".sc", ".school", ".schule", ".science", 
        ".scot", ".sd", ".se", ".security", ".select", ".services", ".sex", ".sexy", ".sg", ".sh", 
        ".shiksha", ".shoes", ".shop", ".shopping", ".show", ".si", ".singles", ".site", ".sk", ".ski", 
        ".skin", ".sl", ".sn", ".so", ".soccer", ".social", ".software", ".solar", ".solutions", ".soy", 
        ".spa", ".space", ".sport", ".sr", ".st", ".storage", ".store", ".stream", ".studio", ".style", 
        ".sucks", ".supplies", ".supply", ".support", ".surf", ".surgery", ".com.sv", ".swiss", ".sx", 
        ".systems", ".tattoo", ".tax", ".taxi", ".td", ".team", ".tech", ".technology", ".tel", ".tennis", 
        ".tf", ".tg", ".theater", ".tickets", ".tienda", ".tips", ".tires", ".tirol", ".tk", ".tl", ".tn", 
        ".to", ".today", ".tokyo", ".tools", ".top", ".tours", ".town", ".toys", ".tr", ".gen.tr", 
        ".trade", ".trading", ".training", ".tube", ".tv", ".com.tw", ".tw", ".tz", ".co.tz", ".com.ua", 
        ".org.ua", ".ug", ".co.uk", ".org.uk", ".uk", ".university", ".uno", ".us", ".uy", ".vacations", 
        ".vc", ".ve", ".vegas", ".ventures", ".vet", ".vg", ".viajes", ".video", ".villas", ".vin", ".vip", 
        ".vision", ".vlaanderen", ".vn", ".com.vn", ".vodka", ".vote", ".voto", ".voyage", ".vu", ".wales", 
        ".watch", ".webcam", ".website", ".wedding", ".wf", ".wien", ".wiki", ".win", ".wine", ".work", 
        ".works", ".world", ".ws", ".wtf", ".xn--p1ai", ".xyz", ".yachts", ".yoga", ".yt", ".org.za", 
        ".co.za", ".net.za", ".zip", ".zone"
    };

    if (link.find("http://") != std::string::npos ||
        link.find("https://") != std::string::npos ||
        link.find("www.") != std::string::npos) {
        return true;
    }

    // Check for the domain extensions
    for (const std::string& ext : domainExtensions) {
        if (link.find(ext) != std::string::npos) {
            return true;
        }
    }

    return false;
}

bool ArLink ( string& link )
{    
    // const std::regex httpsPattern
    //         ("https?:\\/\\/(www\\.)?[-a-zA-Z0-9@:%._\\+~#=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%_\\+.~#?&//=]*)");
    // const std::regex wwwPattern
    //         ("[-a-zA-Z0-9@:%._\\+~#=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%_\\+.~#?&//=]*)");

    // return (std::regex_match(link, httpsPattern) || std::regex_match(link, wwwPattern));
    
    // return (link.find(".com") != string::npos)  || 
    //         (link.find(".lt") != string::npos)  || 
    //         (link.find(".eu") != string::npos)  ||
    //         (link.find("http://") != string::npos) || 
    //         (link.find("https://") != string::npos) || 
    //         (link.find("www") != string::npos)  ||
    //         (link.find('.') != string::npos && link.find('.') != link.size() - 1 && link.find('.') != 0);
    
    if (!link.empty() && (link.front() == '.' || link.back() == '.')) {
        if (link.front() == '.') {
            link.erase(0, 1);
        }
        if (!link.empty() && link.back() == '.') {
            link.erase(link.size() - 1, 1);
        }
    }

    if (!link.empty() && (link.front() == ',' || link.back() == ',')) {
        if (link.front() == ',') {
            link.erase(0, 1);
        }
        if (!link.empty() && link.back() == ',') {
            link.erase(link.size() - 1, 1);
        }
    }

    return containsValidDomainExtension(link);

    
    
    /*
    npos reiškia eilučių paieškų sąlygą „nerasta“, reikšmė paprastai yra didžiausia dydis,
    kurį nurodo dydis_t tipas, nurodant, kad eilutėje nerasta simbolio arba poeilutės.
    */ 
}

bool ArEmail( string& email)
{
    return email.find('@') != string::npos; 
}

void spausdinimas(map <string, vector <int>>& zodziai,  vector <string>& linkai){

    ofstream isvesti ("rez.txt");  

    isvesti << left << setw(20) << "Zodis" 
            << setw(10) << "Kiekis" 
            << "Eilutes" << endl;
            isvesti<<"-------------------------------------------------------------------------"<<endl;

    for( auto it = zodziai.begin(); it!= zodziai.end(); it++){
        if(it->second.size() >1){
            isvesti<< left << setw(20)  << it->first << setw(10) <<it->second.size();
            
            for(size_t i=0; i < it->second.size(); ++i){
                isvesti<<it->second[i];
                if(i< it->second.size()-1) isvesti <<", ";
            }
            isvesti<<endl;
        }     
    }

    isvesti<<endl<<"Rasti URL ir mail: "<<endl;

    for(size_t i=0; i<=linkai.size()-1; i++){
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
            
            if(!(ArLink (zodis) || ArEmail(zodis) )){
                tvarkymas(zodis, 0);
                tvarkymas(zodis, zodis.length()-1);    
            }
            pridetiMAP(zodziai, eilute, zodis, linkai);

        }
        
    }

    failas.close();

}    


# Egzamino užduotis
Užduoties formuluotė:

* Suskaičiuokite, kiek kartų kiekvienas skirtingas žodis pasikartoja Jūsų tekste. Tekstą galite paimti iš bet kur, pvz.: Vikipedijos straipsnis apie Vilnių (geriau kad būtu kitoks tekstas, ne mažiau 1000 žodžių, nereikia traukti straipsnio programiškai, užtenka nukopijuoti ir įkelti į apdorojamą failą). Tuomet realizacijos išoriniame faile išveskite skirtingus žodžius (kableliai, taškai ir kiti skyrybos ženklai nėra žodžiu dalis), kurie pasikartojo dažniau negu 1 kartą, o taip pat ir count'erį, nurodantį kiek kartų konkretus žodis pasikartojo.
* Sukurkite failą su cross-reference tipo lentelę kurioje būtų nurodyta, kurioje teksto vietoje (kurioje(-iose) teksto eilutėse) kiekvienas iš daugiau negu vieną kartą pasikartojantis žodis buvo paminėtas.
* URL adresų suradimas Jūsų tekste. Kaip ir pirmos užduoties atveju, tekstą galite paimti iš bet kur, tačiau būtina, kad tame tekste būtų bent keli URL'ai, pateikti "pilnu" https://www.vu.lt/, https://vu.lt/ ar "sutrumpintu" pavidalu: www.vu.lt, vu.lt. Jūsų tikslas, iš to teksto išrinkti visus šiuos URL'us ir gražiai išvesti į failą. Repozitorija turi būti parengta pagal visus ankstesnių darbų galutinėms versijoms galiojančius reikalavimus.

### Programos veikimas
Paleidus programą yra nuskaitomas ``tekstas.txt`` failas ir atrūšiavus duomenis yra išrenkami visi URL ir žodžiai, kurie tekste kartojosi daugiau nei vieną kartą. Žodžiai yra saugomi `` map <string, vector <int> > zodziai;``. Šis konteineris automatiškai surūšiuoja duomenis. Išvedami rezultatai yra išsaugomi ``rez.txt`` faile.

## Programos paleidimas
1. Parsisiųskite failus iš pateikto linko: https://github.com/EligMaa/Papildoma naudodami instrukciją pateiktą šiame linke: https://blog.hubspot.com/website/download-from-github <br>
2. Susiinstaliuokite VisualStudioCode pagal pateiktą linką: https://www.youtube.com/watch?v=DMWD7wfhgNY <br>
3. Atidarykite parsisiųstą dokumentą iš github ir paspauskite dešiniu klavišu ant juostos su dokumento pavadinimu:<br>
   ![image](https://github.com/EligMaa/Darbas_1/assets/151032480/6177c4ce-f06c-4caf-8a94-6c3132fbf582)<br>
Paspauskite 'Kopijuoti adresą kaip tekstą'.<br>
4. Parsisiųstą aplankalą atsidarykite VisualStudioCode. Įrankių juostoje paspauskite ``'Terminal' -> 'New terminal'`` ir įveskite pateiktas eilutes: <br>
 + ``cd 'jūsų nukopijuotas adresas'`` <br>
 + ``make paleisti``
 + ``./prog``

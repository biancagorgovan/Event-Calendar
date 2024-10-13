# Event-Calendar
TASK 1
-restul impartirii timestampului la 86400(=60*60*24)(cate secunde sunt intr o zi) reprezinta nr de secunde trecute de la inceputul zilei timetsampului, astfel pt a determina nr de ore, aflam catul impartirii acestui rezultat la 3600 (nr de secunde dintr-o ora)
-restul impartirii timestampului la 3600(=60*60)(cate secunde sunt intr o ora) reprezinta nr de secunde trecute de la inceputul orei curente, astfel pt a determina nr de minute, aflam catul impartirii acestui rezultat la 60 (nr de secunde dintr-un minut)
-restul impatirii timetsampului la 60 (nr cuprins intre 0 si 59) determina nr de secunde curent
TASK 2
-restul imaprtirii variabilelei days_number_start_year la 365*3600*24 (nr de secunde intr_un an, fara a trata si cazul anilor bisecti) reprezinta nr de secunde trecute de la inceperea anului curent, astfel impartim acest rezultat la 3600*24 (nr de secunde intr-o zi) pentru a obtine nr de zile trecute de la 1 ian anul curent
-pt a afla nr lunii curente, dar si ziua curenta este necesara sa scadem din variabila days_number_start_year treptat nr de zile al lunilor ce au trecut
-in momentul in care aceasta variabila este mai mica decat 28(nr minnim de zile dintr-o luna), ne aflam in luna curenta, si nr zilei curente este days_number_start_year +1
-dupa fiecarea scadere a nr complet de zile dintr-o luna din variabila days_number_start_year incrementam variabila month care functioneaza ca un contor pentru nr lunii curente
-in while, verificam ce fel de luna este ca sa stim cate zile trb sa scadem din variabila days_number_start_year
-luna a 2-a (februarie) are 28 zile (ignoram anii bisecti); lunile impare pana in iulie inclusiv si cele pare dupa august inclusiv au 31 zile, restul 30
-in variabila month obtinem nr lunii curente
-impartind timestampul la 365*3600*24(nr de sceunde intr-un an) obtinem nr de anii trecuti de la 1970
-anul curent este rezultatul anterior + 1970
TASK 3 
-asemanator taskului anterior, determin nr de zile din timestamp
-determin atat anul curent, cat si nr de zile din anul curent prin scaderi repetitive a nr de zile dintr-un an din variabila mea day_number ce contine nr de zile din timestamp
-in aceste scaderi, verific daca anul indeplineste condiitii de an bisect si scad nr corespunzator de zile, respectiv 366 si 365 daca nu este bisect
-in functie de tipul anului initilizez variabila cu nr de zile din luna februarie
-determin asemenea taskului 2, tinand cont de nr de zile specific lunii februarie in anii bisecti, luna curenta si ziua curent
TASK 4
-pt a aduce timestampul in UTC, ii adaug diferenta de fus orar corespunzatoare, aflata la indexul dat in vector, inmultita cu nr de sec intr-o ora  
-folosesc functiile definite anterior pentru a obtine data si timpul din timestamp
-egaleze si componenta tz cu adresa corespunzatoare (cea la care pointeaza timezones+timezone_index)
TASK 5
-adaug la timestampul, ce se doreste sa fie obtinut, nr de sec din structura
-nr de sec a min din strcutura, analog pt ora, diferenta de fus orar si nr de zile
-deoarece lunile au nr variabile de zile, adaug treptat nr de secunde din fiecare luna din anul timestampului, determinand nr de zile corespunzator fiecarei luni cu criteriile definite anterior
-asemenator cu secundele din fiecare an de la 1970 pana la cel curent, verificand daca acesta este bisect
TASK 6
-compar luna cu nr corrspunzator pentru a determina ce carectere trebuiesc afisate ca denumire a acesteia
-folosesc %02 pentru a afisa nr cu 2 cifre (de forma 02, etc)
-definesc in printf fromatul cerut in ex, folosesc %hhu pt unsigned char, %u pt unsigned int, %s pt siruri de caractere, %hhd pt signed char
TASK 7
-citesc nr task -ului, il compar cu 7 sau 8 pt a sti ce se executa
-citesc nr de date, citesc int-urile ce contin datele si fac un "si" logic intre acestea si 32767 pt a determina primii 15 biti si salvez valorile intr-un vector
-sorteaza valorile din vector in ordine crescatoare pt ca datele sa fie ordonate cronologic cronologic (int-ul mai mare va avea data mai "tarzie", dpdv cronolgic)
-salvez pt fiecare int valorile pt zi, luna si an intr-o structura de tip TDate
-obtin ziua facand "si" logic intre valoarea din vector si 31 (11111, in format binar, primii 5 cei mai nesemnificativi biti)
-luna se obtine shiftand valoare din vector cu 5 biti(cat ocupa ziua, care se afla anterior) si ulterior facand un "si" logic cu 15(1111, in format binar, primii 4 cei mai nesemnificativi biti, spatiul ocupat de luna fiind de 4 biti)
-anul se obtine shiftand valoarea din vector cu 9 biti(cat ocupa luna si ziua) si ulterior facand un "si" logic cu 63(111111, in format binar, primii 6 cei mai nesemnificativi biti, spatiul ocupat de luna si zi fiind de 9 biti)
-imi definesc o functie pt afisare in formatul cerut, asemanator taskului 6
TASK 8
--pt a calcula nr de biti de 1 din fiecare int se face "si" logica cu 1 shiftat treptat, de 32 ori
-pt a afla valoarea citita pt bitul de control, salvata in bitii elemntelor vect c, tin cont de faptul ca fiecare int de control contine cate 32 biti de control si am gasit relatia de recurenta pt pozitia fiecarui bit de control
-mi-am construit functia DateExtract care extrage asemenea taskului 7, o data din primii 15 cei mai putini semnificativi biti ai unui int, pe care o folosesc la extragerea fiecarei date
-mi-am construit functia DatePack care atribuie fiecarei date un int, asemenea task 7, pt a le putea ordona cronologic usor (pt a obtine acest int, se shifteaza cu nr coresp de pozitii valoarea zilei, lunii, anului si se concateneaza)
-pt extragerea datelor, shiftuiesc constant valoarea primului element al vectorului cu 15 biti(in urma extragerii) si concatenez primii 15 biti din urmatorul element al vectorului(am garantia astfel ca este o data completa acolo)(dupa 2 concatenarii, raman biti nefolositi, shiftati la stanga si concatenati ulterior)
-am grija ca dupa fiecare doua extrageri, raman in element 2*(pozitia in functie de i) biti(pt pozitii pana in i+8), asa ca shituiesc valoarea concatenata cu multiplu coresp al lui 2 
-in extragerea datelor din int-uri, am observat ca in cel de-al 8-lea int (pe pozitia 7 in vect), se ve afla pe primul bit cel mai semnificativ bit al unei date, doua date complete si cel mai nesmnificativ bit din alta data
-imi adaptez for-uri,astfel incat sa imi permita dupa extragerea din i+7 sa fac o extragere in plus
-de aici in primul element al vectorului raman un bit nefolosit in extrageri
-modific regula de mai sus in care raman 
2*(pozitia in functie de i) biti in primul el, pt numar impar de biti ramasi
-repet procedeul de concatenare, extragere, shiftare
-in cel de-al 14-lea int se afla o data completa in plus
-imi adapteze for-urile la aceste comportmanete in extragere
-elimin datele corupte, folosindu-ma de vectroii in care salvez indexul pe care incepe si se termina fiecare data
-sortez inturile extrase
-extrag datele in format explicit
-le afisez
TASK 9
-imi definesc structura TEevent pt a salva nr min de pers di durata evenimentului
-imi definesc structura TInterval pt a salva durata, data(cu ora) la care incepe in format TDateTimeTZ(pt a avea si timezone-ul), codul unxi pt inceput si codul unix pt final pt fiecare eveniment
-imi definesc structura TPerson pt a imi declara vectorul de persoane si pt a salva fiecare numele, timezone-ul, nr de intervale libere si vectorul de intervale de tip TInterval, care salveaza fiecare din informatiile enumerate anterior
-imi definesc structura TPosibility ce contin un unix code pt inceput si unul pt final, pt a declara si utiliza vectorul p in care salvez posibile intervale pt eveniment si timestampurile lor pt inceput si final
-imi definesc functia Compare, pe care o utilizez ulterior pt a ordona cronologic posibilitatile de evenimente
-imi definesc functia comparePeopel pt a ordona ulterior alfabetic persoanele
-citesc informatiile date si mi le completez/calculez pe cele necesare cu ajutorul functiilor create anterior in timelib.c (ex date necesare: min pt data fiecarui intevral-o; asemena seunda; pointer la timezone-ul persoanei pt fiecare intevral; codul unix al inceputului si finalului fiecarui interval)
-alipesc intervalele vecine pt fiecare pers, pt a obtine continuitate
-salvez in vectorul p info prezentate anterior pt fiecare interval posibil(determin in intervalele, fiecarei persoane, care au o durata mai mare sau egala cu durata evenimentului, cat se poate de multe intervale care au durata evenimentului)
-daca nu se gasesc, este clara imposibilitatea evenimentului
-daca exista, le ordonez cronologic ca sa facilitez aflarea primului interval
-verific pe rand, pt fiecare interval posibil cate persoane au interval liber ce il contine, pana cand nr de persoane este egal cu cel min de pers participant
-daca nicio posibiliatea nu satisface conditia asta, evenimentul este imposibil
-verific iarasi pt fiecare persoana daca are un interval ce il contine pe acesta determinat, daca are, afisez data acestui interval in timezone-ul persoanei si timezone ul persoanei(folosesc o variabial auxiliara de tip TDateTimeTz care inglobeaza toate aceste informatii), daca nu invalid

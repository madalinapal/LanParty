Main:
    Pentru functionarea programului, folosesc un "meniu": citesc din fisierul c.in in vectorul "cerinte" 5 elemente, care 
pot avea ca valori doar 0 si 1, in functie de cerinta pe care o verifica checker-ul. Voi avea un set de instructiuni
"if" in care voi apela functiile necesare rezolvarii cerintei respective. 

Cerinta 1:
    Lista mea va fi formata din noduri de tip echipa, prin urmare definesc structura Team ce va avea in componenta
sa: numarul de jucatori (nrj), numele echipei (pointer la char) si un pointer la structura Player, in care voi memora
toti jucatorii din acea echipa. Structura Player are urmatoarele componente: nume, prenume (pointeri la char) si 
numarul de puncte aferente jucatorului(de tip int). Pentru ca pe prima linie din fiecare fisier se afla numarul de
echipe, in main voi face citirea acestuia direct din fisier, apoi il voi transmite ca parametru functiei "Citire". 
In aceasta functie, intr-un for voi citi din fisier cele "nrechipe" linii, si voi face separarea numarului de jucatori 
de restul numelui folosind strtok. Apoi apelez functia "addAtBeggining" care imi adauga in lista fiecare echipa, la inceput. 
In continutul acestei functii, intr-un for pana la numarul de jucatori din echipe, voi citi urmatoarele linii si voi 
adauga jucatorii in campul Team->jucatori (facand din nou separarea punctajului de nume, prenume cu strtok). 

Cerinta 2:
    Implementez functia "putere2" pentru a calcula cea mai mica putere a lui 2 <= numarul de echipe. De asemenea,
creez functia "Punctaj_Echipa" ce imi va returna un float, si anume media punctajelor jucatorilor din acea echipa. Cu
ajutorul functiei "CMMPunctajEchipa" parcurg lista si returnez cel mai mic punctaj de echipa din toata lista de echipe.
In functia "DeleteFromTeam" ii atribui lui n valoarea celei mai mici puteri de-ale lui 2 <=nr de echipe. Creez o copie 
a numarului de echipe in variabila NRech, si realizez stergerea echipelor cu cel mai mic punctaj de echipa in felul urmator:
intr-o bucla while ce are conditia "NRech > n" (adica atat timp cat numarul de echipe din lista este mai mare decat puterea
lui 2) retin in variabila "punctaj" cel mai mic punctaj de echipa din lista, apoi parcurg lista de la inceput si compar 
pentru fiecare element punctajul sau cu valoarea variabilei "punctaj". In caz de egalitate apelez functia "delete1Team" 
(care se ocupa cu stergerea unui nod), decrementez "NRech" si fac break pentru a relua instructiunile de la capat si pentru
a actualiza cel mai mic punctaj de echipa. 

    Atat pentru Cerinta 1, cat si pentru Cerinta 2, afisarea in fisier o fac dupa cele 2 if-uri folosind functia "Afisare".

Cerinta 3:
    Pentru ca in urma fiecarui meci disputat intre echipe, numarul celor care vor ramane in joc se injumatateste, ma voi folosi in 
main de variabila "n" pe care o voi initializa cu putere2(nrechipe). De asemenea voi folosi un "index" pentru a retine numarul 
fiecarei runde disputate. Pentru rezolvarea acestei cerinte, voi avea nevoie de definirea unor noi structuri de date: "Match", 
unde voi retine numele d=celor 2 echipe intre care se va disputa partida si scorul fiecareia. De asemenea, voi considera si 
structura "Queue", cu cei doi pointeri la structura: front si rear. Pentru nodurile din cele doua stive declar structura "SNode"
ce va contine numarul echipei si punctajul aferent. Intr-un while al carui conditie va fi n>1:
    Pentru prima runda si anume cazul in care n == putere2(nrechipe), coada o voi crea direct din lista creata
la Cerinta1, folosind functia "CreateQueueL" in care voi parcurge lista de echipe (din 2 in 2) si voi adauga in coada informatiile 
din fiecare nod (si succesorul sau), folosind functia "AdaugareElementInCoadaL". Dupa ce am creat aceasta coada, o parcurg si afisez
in fisier meciurile disputate, apoi creez stivele de invinsi, respectiv castigatori, folosind functia "CreateStacks": pentru
fiecare element din coada compar scorurile celor 2 echipe din fiecare nod, facand "push" pe stiva de castigatori a echipei cu scorul 
mai mare, dupa care il incrementez, iar pe stiva de invinsi fac "push" echipei cu scorul mai mic. Dupa ce am creat stivele, afisez
in fisier castigatorii rundei respective.
    Dupa primul pas, crearea cozii se va face din stiva de castigatori, asa ca pe else voi: sterge coada q, o voi initializa folosind
Init(), voi folosi functia "CreateQueueS" pentru a o crea din stiva de castigatori, afisez meciurile, sterg stivele de invinsi si castigatori
si reinitializez top-urile acestor stive cu NULL si apelez din nou functiile "CreateStacks" si "PrintWinners" pentru a crea stivele si 
a afisa castigatorii.
    Pentru a afla echipele aflate pe primele 8 locuri, pun conditia ca numarul de echipe ramase in joc sa fie 16 (8 de castigatoti,
8 de invinsi), iar apoi, cu un for care parcurge stiva de castigatori voi adauga folosind functia "AddPrimele8final" (adauga fiecare el 
la finalul listei) in lista ce are ca head un pointer "primele8" la structura SNode, fiind de acelasi fel.
    La finalul acestor operatii, tot in bucla while, injumatatesc n-ul si cresc index-ul.

Cerinta 4:
    Declar o noua structura, pentru arborele BST: ANode, in care retin numele echipei, punctajul, dar voi avea si cei doi pointeri
la structura, pentru left si right. In main, parcurgand lista primele8, inserez fiecare nod in arbore, folosind functia "insert".
In aceasta functie compar punctajul nodului curent cu cel al parintelui sau. Daca este mai mare, inserez in dreapta, daca este mai mic,
in stanga, iar daca sunt egale, fac comparatia in functie de nume, in ordine descrescatoare. Daca nodul curent este chiar root, apelez
functia newnode si returnez nodul astfel creat. Pentru a afisa continutul clasamentului in ordine descrescatoare, folosesc functia
"reverseinOrderTraversal" ce este o parcurgere inordine (SDR), dar inversata. (punctajele cele mai mari aflandu-se in dreapta).

Cerinta 5
    Voi avea nevoie de o noua structura de date AVLNode, asemanatoare cu ANode, dar ce are in plus si inaltimea nodului.
    Imi creez AVL-ul pe acelasi principiu de la 4. Parcurg BST-ul invers inordine, adica merg pe subarborele drept, 
"Root" va primi "insertAVL" de nodul curent root din BST, apoi merg pe subarborele stang.
    "insertAVL": inserarea este exact ca la BST, cu toate comparatiile aferente. Diferenta apare la echilibrare. astfel: 
pentru fiecare nod calculez inaltimea, adaugand 1 la maximul dintre inaltimea nodului stang si cel drept. (pe care le calculez
cu functia "nodeHeight" si le compar folosind functia "max"). Calculez apoi factorul de echilibru, scazand din inaltimea subarborelui
stang, inaltimea subarborelui drept. De asemenea, pentru a-mi usura munca folosesc functia "comp", ce imi returneaza -1 pentru cazul 
in care punctajul nodului din BST este mai mic decat a celui din AVL (la fel si pentru nume) sau 1 in caz contrar.
    Apoi, folosind 4 if-uri in care pun combinatiile conditiilor pentru k si comp, realizez rotatiile:
    - daca k > 1 si comp(node->left, p) < 0 returnez (nodul) rotatia la dreapta a nodului node;
    - daca k < -1 si comp(node->right, p) > 0 returnez (nodul) rotatia la stanga a nodului node;
    - daca k > 1 si comp(node->left, p) > 0 returnez (nodul) rotatia dubla dreapta-stanga a nodului node;
    - daca k < -1 si comp(node->right, p) < 0 returnez (nodul) rotatia subla stanga-dreapta a nodului node;
    In main, folosind functia PrintLevelNodes afisez nodurile de pe nivelul 2 din AVL.

La final, eliberez memoria si inchid fisierele.
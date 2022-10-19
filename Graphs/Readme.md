
# Prima parte
Dupa ce am citit tot input-ul specificat asa cum este in cerinta, am luat o structura output pentru task-ul 1 in care am stocat toate elementele modificate din functia dijkstra, un algoritm prin care
 am aflat costul minim dintr-un punct ales, catre toate punctele din graf, specificand la sfarsit sfasitul drumului pentru a afla exact drumul care ne intereseaza.Am folosit acest algoritm de 2 ori, o data de la depozit pana la punctul dat si dupa de la punctul dat pana la depozit.
 Dupa care am printat output-ul asa cum ne este precizat si am dezalocat memoria.

# A doua parte

Deoarece nu trebuia sa trecem prin depozite, am luat un sir de puncte care reprezenta daca s-a trecut deja printr-un anumit punct folosind diversi algoritmi, initializand pentru depozite valoarea -1, pentru a evidentia faptul ca nu trebuie sa trecem prin ele.
 Dupa care am folosit DFS,prin care am aflat nodurile deja conectate si pe care le-am pus intr-o stiva, reluand DFS-ul pana cand fiecare element din vectorul de vizitat sunt 1, exceptie facand depozitele care vor ramane tot 1.
 Dupa ce am stocat toate aceste elemente in stiva, pentru a afla componentele tare conexe va trebui sa facem tot un DFS(numai ca de date asta difera datele de intrare) dar vom incepe cu primul element din stiva(elementul de return al lui pop de stiva) oprindu-ne pana cand fiecare nod este vizitat.
 Astfel, am aflat componentele tare conexe pe care le-am salvat intr-un vector de stive si pe care l-am sortat, exact cum ne este cerut in cerinta. In final, am afisat componentele tare conexe, si am dezalocat dinamic

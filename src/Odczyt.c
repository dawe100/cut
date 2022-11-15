 #include "Odczyt.h"


 //może być różna liczba cpu oraz różna liczba pól dla każdego cpu (max 10)
 //cpuNo sluzy do wyboru numeru cpu, ktory chcemy odczytac (przy zalozeniu, ze jestesmy na poczatku pliku)
bool cpuRead(FILE* file, cpustat_t* cpustat, int cpuNo){
    if(file == NULL)
        return false;

    char cpuname[6];
    int  cpuno_read;
    unsigned long read;

    while(cpuNo+1){                 //wybór cpu
        fscanf(file, "%*[^\n]\n");  //pominiecie linii
        --cpuNo;
    }

    fscanf(file, "%s", cpuname);
    if (strncmp(cpuname, "cpu", 3) != 0)
        return false;

    if(sscanf(cpuname, "%*3c%d", &cpuno_read) != EOF)  //odrzucenie trzech znakow i proba odczytu liczby
        cpustat->No = cpuno_read;                      //gdy odczytywane statystyki jednego z cpu ("cpu[x]")
    else
        cpustat->No = -1;                              //gdy odczytawane statystyki laczne ("cpu")


    unsigned long *ptr = &(cpustat->user);

    while(fscanf(file, "%ld", &read)){  //dopóki odczytuje poprawnie long (czyli do konca linii)
        *ptr = read;
        ++ptr;
    }


    return true;
 }

 bool cpuReadAll(const char* filename, cpustat_t CPUs[]){

    FILE* file = fopen(filename, "r");
    if(file == NULL)
        return false;

    int i = 0;
    while(cpuRead(file, &CPUs[i], -1)){     //odczyt tak długo jak kolejne linie zaczynają się od "cpu"
        ++i;
    }

    fclose(file);
    return true;
 }



unsigned int cpuCount(const char* filename){

    FILE* file = fopen(filename, "r");
    if(file == NULL)
        return 0;

    char line[200];
    unsigned int count = 0;

    fgets(line, 200, file);

    while(strncmp(line, "cpu", 3) == 0){
        ++count;
        fgets(line, 200, file);
    }

    fclose(file);
    return count;
}




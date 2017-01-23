#include <stdio.h>
#include "France.h"

int main(){

    char starts[15],finishs[15];

    FILE * file;
    file = fopen("FRANCE.MAP", "r");
    if (!file) return NULL;
    char city[100];
    int lati;
    int loni;
    City * ct = malloc(sizeof(City));
    List * dp = newList(Eltcmp, CitDisp);
    int returnVal;
    while(returnVal!=-1){

        returnVal = fscanf(file,"%s %d %d\n", city, &lati, &loni);
        City * already = lookupCity(dp, city);

        if (returnVal == 3){
            if(already == 0){
                ct =BuildCity(city, lati, loni);
                addList(dp, ct);
            }else{
                ct = already;
                ct->lati = lati;
                ct->loni = loni;
            }
        }

        else if (returnVal == 2){
            Neighbours * nb = malloc(sizeof(Neighbours));
            if (already==0){
                City * nb_city = BuildCity(city, -1, -1);
                addList(dp, nb_city);
                nb = CreateNeighbour(nb_city,lati);
                addList(ct->neighbours, nb);
            }else{
                nb=CreateNeighbour(already, lati);
                addList(ct->neighbours, nb);
            }
        }
    }
    fclose(file);
    forEach(dp, CitDisp);

    List * exposed = newList(citycmp, CitDisp);
    List * bolted = newList(Eltcmp, CitDisp);
    printf("\nEnter city where want to go:");
    gets(starts);
    printf("\nEnter city where want to reach:");
    gets(finishs);
    
    City * actual = lookupCity(dp, starts);
    City * reach = lookupCity(dp, finishs);

    addList(exposed, actual);
    actual->Startdistance = 0;
    actual->Finishdistance=rennesTolyon(actual, reach);

    while(exposed->head){
        void * dp;
        remFromListAt(exposed, 1, &dp);
        addList(bolted, dp);
        City * ct = (City *) dp;

        if(ct == reach){
            printf("Reached:\n");
            while(ct){
                printf("%s %d %d \t",ct->name,ct->lati,ct->loni);
                ct = ct ->ctr;
            }
            return 0;
        }
        Node * nd = ct->neighbours->head;
        while(nd){

            City * achieve = ((Neighbours *)nd->val)->city;
            int cover =((Neighbours *)nd->val)->distance;
            int covered = ct->Startdistance + cover;

            if((isInList(exposed, achieve)!=0) ||
              ((isInList(bolted, achieve)!=0) &&
                    (covered > achieve->Startdistance)))
            {
                    nd = nd->next;
            }
            else{
                if(isInList(exposed, achieve)!=0){
                    remFromList(exposed, achieve);
                }
                if(isInList(bolted, achieve)!=0){
                    remFromList(bolted, achieve);
                }
                achieve->Startdistance = covered;
                achieve->ctr = ct;
                addList(exposed, achieve);
                nd = nd->next;
            }
        }
    }
    printf("Sorry! Not available");
    return 0;
}

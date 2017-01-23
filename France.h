#ifndef __List_H
#define __List_H

#include <stdlib.h>
#include "status.h"

typedef struct Node {
    void		*val;
    struct Node	*next;
} Node;

typedef int(*compFun)   (void* e1, void* e2);
typedef void(*prFun)   (void*);
typedef struct List {
    int nelts;
    Node * head;
    compFun comp;
    prFun pr;
} List;
List*	newList	(compFun,prFun);
void 	delList	(List*);
status 	nthInList	(List*,int,void**);
status 	addListAt	(List*,int,void*);
status 	remFromListAt	(List*,int,void**);
status 	remFromList	(List*,void*);
status 	displayList	(List*);
void	forEach		(List*,void(*)(void*));
int	lengthList	(List*);
status	addList	(List*,void*);
Node*	isInList	(List*,void*);

typedef struct City{
    char name[100];
    int lati;
    int loni;
    List * neighbours;
    //struct City link;
    int Startdistance;
    int Finishdistance;
    struct City * ctr;
    
}City;

typedef struct Neighbours{
    int distance;
    City * city;
}Neighbours;
int DisttwoCity(void *, void *);
int curr_to_go(City *);
int citycmp(void *, void *);
int rennesTolyon(City *, City *);
int Neighbcmp(void *, void *);
City * BuildCity(char*,int, int);
void copy_string(char [], char []);
int Eltcmp(void *, void *);
void CitDisp(void * );
City * lookupCity(List * l, char[100]);
Neighbours * CreateNeighbour(City *,int);
void NeigDisp(void *);

#endif

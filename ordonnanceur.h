#ifndef __ORDONNANCEUR_H__
#define __ORDONNANCEUR_H__

#include "processus.h"

// Table des processus activablesssss
extern processus_t* table_processus[2];

// Prototype de la fonction d'ordonnancement
void ordonnance(void);
void ajouter_processus(processus_t* proc);

#endif

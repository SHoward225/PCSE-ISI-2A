/**
 * \file processus.h
 * \brief Pour gerer les structures des threads, leurs creation et l'ordonnancement
 * \author konan-junior.kouadio@grenoble-inp.org
 * \date 11/10/2024
 */

#ifndef __PROCESSUS_H__
#define __PROCESSUS_H__

#define NB_REGISTRES 5  
#define TAILLE_PILE 512

extern void ctx_sw(int *ancien_ctx, int *nouveau_ctx);


typedef enum {
    ELU,        // Processus en cours d'exécution
    ACTIVABLE,  // Processus prêt à être exécuté
    ENDORMI     // Processus endormi (si applicable dans les étapes futures)
} etat_processus;


typedef struct processus {
    int pid;                    // Identifiant unique du processus
    char nom[32];               // Nom du processus (pour le débogage)
    etat_processus etat;        // État du processus
    int registre[NB_REGISTRES]; // Zone pour sauvegarder les registres (ebx, esp, ebp, esi, edi)
    int pile[TAILLE_PILE];      // Pile d'exécution du processus
} processus_t;


// Table des processus (statiquement définie pour 2 processus : idle et proc1)
extern processus_t processus_table[2];


// Prototypes des fonctions
void init_processus(void);
void ordonnance(void);
void idle(void);
void proc1(void);

#endif
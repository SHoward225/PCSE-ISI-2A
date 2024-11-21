#ifndef __PROCESSUS_H__
#define __PROCESSUS_H__

#include <inttypes.h>

typedef enum {
    ELU,
    ACTIVABLE
} etat_t;


// =======================  Cas de base =======================

// // Table des processus contenant des *pointeurs* vers des structures de processus
// extern processus_t* table_processus[2];

// // Déclarations pour les processus idle et proc1
// extern processus_t* idle_process;
// extern processus_t* proc1_process;

// typedef struct contexte {
//     uint32_t ebx;
//     uint32_t esp;
//     uint32_t ebp;
//     uint32_t esi;
//     uint32_t edi;
// } contexte_t;

// typedef struct processus {
//     uint32_t pid;
//     char* nom;
//     contexte_t regs;
//     uint32_t* pile;
//     uint32_t* pile_base;
//     etat_t etat;
// } processus_t;



// // Fonctions pour initialiser les processus
// void init_processus(processus_t* proc, uint32_t pid, char* nom, void (*fonction)(void));

// // Exemple avec 2 processus
// void init_processus_idle_proc1(void);
// void idle(void);
// void proc1(void);
// int32_t mon_pid(void);
// char *mon_nom(void);

// ======================= generalisation a N processus =======================

typedef struct contexte {
    uint32_t ebx;
    uint32_t esp;
    uint32_t ebp;
    uint32_t esi;
    uint32_t edi;
} contexte_t;


typedef struct processus {
    uint32_t pid;
    char* nom;
    contexte_t regs;
    uint32_t* pile;
    uint32_t* pile_base;
    etat_t etat;
} processus_t;


// Fonctions pour initialiser les processus
void init_processus(processus_t* proc, uint32_t pid, char* nom, void (*fonction)(void));
uint32_t creer_processus(void (*code)(void), char* nom);

void idle(void);
void proc1(void);
void proc2(void);
void proc3(void);
void proc4(void);
void proc5(void);
void proc6(void);
void proc7(void);
int32_t mon_pid(void);
char *mon_nom(void);


// ============== Utilisation de listes de processus =====================



#endif

#ifndef __PROCESSUS_H__
#define __PROCESSUS_H__

#include <inttypes.h>

typedef enum {
    ELU,
    ACTIVABLE
} etat_t;

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


// Pointeurs vers les processus idle et proc1
extern processus_t* idle_process;
extern processus_t* proc1_process;


// Fonctions pour initialiser les processus
void init_processus(processus_t* proc, uint32_t pid, char* nom, void (*fonction)(void));

// Exemple avec 2 processus
void init_processus_idle_proc1(void);
void idle(void);
void proc1(void);
int32_t mon_pid(void);
char *mon_nom(void);

#endif

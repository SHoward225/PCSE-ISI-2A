
#include <stdio.h>
#include <tinyalloc.h>

#include "ordonnanceur.h"
#include "processus.h"
#include "cpu.h"
#include "ctx_sw.h"

#define TAILLE_PILE 512  // Taille de la pile pour chaque processus
extern processus_t* proc1_process;


processus_t* idle_process;
processus_t* proc1_process;

// Fonction pour initialiser un processus avec les informations fournies
void init_processus(processus_t* proc, uint32_t pid, char* nom, void (*fonction)(void)) {
    proc->pid = pid;
    proc->nom = nom;
    proc->etat = ACTIVABLE;

    // Allouer la pile pour le processus
    proc->pile = (uint32_t*) malloc(TAILLE_PILE * sizeof(uint32_t));
    proc->pile_base = proc->pile;

    // Préparer la pile pour la première exécution
    proc->pile[TAILLE_PILE - 1] = (uint32_t) fonction;  // Adresse de la fonction
    proc->regs.esp = (uint32_t) &proc->pile[TAILLE_PILE - 1];  // ESP pointe vers cette adresse
    proc->regs.ebx = 0;
    proc->regs.ebp = 0;
    proc->regs.esi = 0;
    proc->regs.edi = 0;

    printf("Processus %s (PID=%u) initialisé avec succès.\n", nom, pid);
}

void idle(void) {
    printf("[idle] je tente de passer la main à proc1...\n");
    ctx_sw(&(idle_process->regs), &(proc1_process->regs));  // Passage de idle à proc1
}

void proc1(void) {
    printf("[proc1] idle m’a donné la main\n");
    printf("[proc1] j’arr\`ete le système\n");
    hlt();  // Arrête le système
}

// Initialiser les processus idle et proc1
void init_processus_idle_proc1(void) {
    idle_process = (processus_t*) malloc(sizeof(processus_t));
    proc1_process = (processus_t*) malloc(sizeof(processus_t));
    
    // Initialiser le processus idle (PID 0)
    init_processus(idle_process, 0, "idle", idle);

    // Initialiser le processus proc1 (PID 1)
    init_processus(proc1_process, 1, "proc1", proc1);
}

#include <stdio.h>
#include "cpu.h" // Pour la manipulation des fonctions outb et inb
#include <inttypes.h> // Pour les types uint32
#include "traitants.h" // Pour utiliser traitant_IT_32 de la fonction assembleur
#include "segment.h" // POur la variable globale KERNEL_CS
#include <stdbool.h> // Pour les bool

#define IDT_BASE 0x1000 
#define QUARTZ 0x1234DD  // Fréquence du quartz en Hz


// Configure le PIT pour générer des interruptions à une certaine fréquence (50 Hz)
void regle_frequence_PIT(uint32_t frequence) {
    uint32_t divisor = QUARTZ / frequence;
    outb(0x34, 0x43);  // Commande pour configurer le PIT
    outb(divisor & 0xFF, 0x40);  // Bits de poids faibles
    outb((divisor >> 8) & 0xFF, 0x40);  // Bits de poids forts
}


// Initialiser le traitant d'interruption pour l'IT 32 (PIT)
void init_traitant_IT(uint32_t num_IT, void (*traitant)(void)) {
    uint32_t* entry = (uint32_t*)(IDT_BASE + 2*num_IT * sizeof(void *));  // Adresse de l'entrée dans l'IDT
    uint32_t addr = (uint32_t)traitant;

    // Remplir les deux mots de l'entrée dans l'IDT
    entry[0] = (KERNEL_CS << 16) | (addr & 0xFFFF);  // Bas 16 bits de l'adresse et segment
    entry[1] = (addr & 0xFFFF0000) | 0x8E00;  // Haut 16 bits de l'adresse et attributs
}


// Démasquer l'IRQ0 pour activer les interruptions de l'horloge (PIT)
void masque_IRQ(uint32_t num_IRQ, bool masque) {
    uint8_t masque_ancien = inb(0x21);
    if (masque)
        masque_ancien |= (1 << num_IRQ);  // Masquer l'IRQ
    else
        masque_ancien &= ~(1 << num_IRQ);  // Démasquer l'IRQ
    outb(masque_ancien, 0x21);
}



void init_system() {
    // Configurer la fréquence du PIT à 50 Hz
    regle_frequence_PIT(50);

    // Associer l'IT 32 à `traitant_IT_32` pour gérer les interruptions du PIT
    init_traitant_IT(32, traitant_IT_32);

    // Démasquer l'IRQ0 pour activer les interruptions de l'horloge
    masque_IRQ(0, false);

    // Activer les interruptions
    sti();
}
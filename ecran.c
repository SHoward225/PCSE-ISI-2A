//************** IMPORT LIBRARY **************

#include <stdio.h> 
#include "ecran.h"
/* CR begin */
// #include <stdint.h>
#include <inttypes.h>
/* CR end */


// ************** CONSTANT DEFINITION **************

#define LIG_MAX 25 // Nombre de ligne maximale
#define COL_MAX 80 // Nombre de colonne maximale
#define MEMOIRE_VIDEO_BASE 0xB8000 //adresse de base de la memoire video CGA


static uint32_t position_colonne =0 ;
static uint32_t position_ligne =0 ;


// ************** DATA STRUCTURES DEFINITION **************
enum {
    NOIR,
    BLEU,
    VERT,
    CYAN,
    ROUGE,
    MAGENTA,
    MARRON,
    GRIS,
    GRIS_FONCE,
    BLEU_CLAIR,
    VERT_CLAIR,
    CYAN_CLAIR,
    ROUGE_CLAIR,
    MAGENTA_CLAIR,
    JAUNE,
    BLANC
};

// ************** CODE IMPLEMENTATION **************

/*
 * Cette fonction renvoie un pointeur sur la case memoire 
 * correspondante aux cordonnées fournies
 */

uint16_t *ptr_mem(uint32_t lig, uint32_t col ){
    uint32_t *pos = (uint32_t*) (MEMOIRE_VIDEO_BASE + 2*(lig*80 + col));
    return (uint16_t *) pos;
}

/*
 * Ecrit le caractere c aux coordonnées specifiées 
 * Ajout : paramettre pour preciser couleur du caractere, celle de fond et bit de clignotement
 */

void ecrit_car(uint32_t lig, uint32_t col, char c,  uint32_t couleur_caractere, uint32_t couleur_fond, uint32_t clignotement){
    uint16_t *adresse_memoire = ptr_mem(lig, col); //adresse memoire du curseur
    uint16_t valeur = (uint16_t) c | couleur_caractere << 8 | couleur_fond << 12| clignotement  << 15; //valeur du caractère à afficher
    *adresse_memoire = valeur;
}


/*
 * Parcours les lignes er colonnes de l'ecran pour ecrire dans chaque case un espace blanc sur un fond noir
 * afin d'initialiser les formats dans la memoire
 */
void efface_ecran(void){
    for (uint32_t i = 0; i < LIG_MAX; i++)
    {
        for (uint32_t j = 0; j < COL_MAX; j++)
        {
            ecrit_car(i, j,' ', 0, 0, 0);
        }
    }
}

/*
 * Place le curseur a la position donnée 
 */

void place_curseur(uint32_t lig, uint32_t col){
    uint16_t position = col + lig * COL_MAX;
    // Envoie de la commande 0x0F sur la partie basse
    outb(0x0F, 0x3D4);
    outb(position, 0x3D5);
    // Envoie de la commande 0x0F sur la partie basse
    outb(0x0E, 0x3D4);
    outb(position >> 8, 0x3D5);
}

/*
 * Traite un caractere donné (affiche si c'est un caractere normal ou 
 * implemante l'effet voulu si c'est un caractere de controle) 
 */
void traite_car(char c){
    switch (c)
    {
        //Recule curseur
        case '\b':  // Backspace
            if (position_colonne != 0) position_colonne--;
            break;

        //Avance a la prochaine tabulation
        case '\t':  // Tabulation
            position_colonne = (position_colonne + 8) & ~(8 - 1);
            break;
        
        //Retour à la ligne et col=0
        case '\n':  // Nouvelle ligne
            position_ligne = 0;
            position_ligne++;
            break;

        //Efface ecran et place curseur en (0;0)
        case '\f':
            efface_ecran();
            position_colonne = 0;
            position_ligne = 0;
            break;

        //Deplace curseur sur la ligne actuelle et col=0
        case '\r':
            position_colonne = 0;
            break;

        //Par defaut
        default:
            if (c >= 32 && c <= 126) {
                ecrit_car(position_ligne, position_colonne, c, 15, 0, 5);
                position_colonne++;
            }
            break;
    }

    // Vérification des limites
    if (position_colonne >= COL_MAX) {
        position_colonne = 0;
        position_ligne++;
    }
    if (position_ligne >= LIG_MAX) {

        // Gestion du défilement
        memmove(ptr_mem(0, 0), ptr_mem(1, 0), COL_MAX * (LIG_MAX - 1) * 2);
        for (uint32_t x = 0; x < COL_MAX; x++) {
            ecrit_car(LIG_MAX - 1, x, ' ', 15, 0, 5);
        }
        position_ligne = LIG_MAX - 1;
    }

    place_curseur(position_ligne, position_colonne);


}

/*
 * Remonte d'une ligne l'affichage de l'ecran
 * (Judicieux d'tiliser memmove definie dans string.h)
 */
void defilement(void){
    // Copie chaque ligne sur la ligne précédente, en commençant par la deuxième ligne depuis le bas
    for (int lig = 1; lig < LIG_MAX; lig++) {
        for (int col = 0; col < COL_MAX; col++) {
            uint16_t* source = ptr_mem(lig, col);
            uint16_t* destination = ptr_mem(lig - 1, col);
            *destination = *source;
        }
    }

    // Efface la dernière ligne en la remplissant d'espaces
    for (int col = 0; col < 80; col++) {
        ecrit_car(24, col, ' ',15, 0, 5);
    }
}

/*
 * Solution finale
 * Utilise les fonctions precedentes
 */
void console_putbytes(const char *s, int len){
    /*CODE*/
}

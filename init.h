#ifndef __INIT_H__
#define __INIT_H__

#include <inttypes.h>  // Pour le type uint32_t
#include <stdbool.h>

void regle_frequence_PIT(uint32_t frequence);
void init_traitant_IT(uint32_t num_IT, void (*traitant)(void));
void masque_IRQ(uint32_t num_IRQ, bool masque);
void init_system(void);

#endif
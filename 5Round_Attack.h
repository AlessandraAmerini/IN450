#ifndef _5_ROUND_H_
#define _5_ROUND_H_

/* Prototipi delle funzioni */

int GrassiAttack(unsigned char *ciphertext);
void init_var();
void copia_vettore(unsigned char *v1, unsigned char *v2, size_t dim);
void stampa_vettore(unsigned char *v1,size_t dim);
int test(unsigned char a[], unsigned char b[]);

// Il numero di round in AES 
extern int Nr;

// Il numero di bit della chiave (32 bit)
extern int const Nk;

// in - contiene il plaintext da cifrare 
// out - contiene la chiave per cifrare 
// state - contiene i risultati intermedi durante la cifratura 
extern unsigned char in[16], out[16], state[4][4];

// Contiene i round di chiave 
extern unsigned char RoundKey[240];

// Chiave data in input  
extern unsigned char Key[32];

#endif

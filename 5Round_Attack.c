#include <stdio.h>
#include "5Round_Attack.h"
#include "AES_Encrypt.h"

int GrassiAttack(unsigned char *ciphertext)
{
    /* Diagonale della chiave da generare: provo tutte le possibili diagonali
     * di 4 byte, ovvero 2^32 possibilità. 
     * Key e' la variabile globale di riferimento che contiene la chiave. */

    size_t i,j,z,w; // le quattro componenti
    
    Nr=5; // Numero di round per l'attacco

    for(i=0;i<256;i++)
    {
        Key[0]=i;

        for(j=0;j<256;j++)
        {
            Key[5]=j;

            for(z=0;z<256;z++)
            {
                Key[10]=z;

                for(w=0;w<256;w++)
                {
                    Key[15]=w;

                    KeyExpansion();
                    Cipher();
                    
                    /* Se i due testi cifrati sono equivalenti per diagonale
                     * allora le due chiavi coincidono per diagonale. */
                    if(test(ciphertext,out))
                        return 1;

                    init_var(); 
                }
            }
        }
    }

    return 0;
}


/* Confronta la diagonale di lunghezza 4  dei due testi cifrati. */
int test(unsigned char a[], unsigned char b[])
{
    if(a[0] == b[0] && a[5] == b[5] && a[10] == b[10] && a[15] == b[15]) 
        return 1;

    return 0;
}

/* Inizializza le variabili globali di riferimento. */
void init_var()
{
    size_t i,j;

    for(i=0;i<240;i++)
        RoundKey[i] = 0;

    for(i=0;i<16;i++)
        out[i] = 0;

    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
            state[i][j] = 0;
    }
}

// Copia il v1 in v2 entrambi di dimensione dim
void copia_vettore(unsigned char *v1, unsigned char *v2, size_t dim)
{
    size_t i=0;

    for(i=0;i<dim;i++)
        v2[i] = v1[i];
}

void stampa_vettore(unsigned char *v1,size_t dim)
{
    size_t i=0;

    for(i=0;i<dim;i++)
        printf("|%x",v1[i]);

    printf("|\n");
}

/*******************
 *                 *
 * INIZIO DEL MAIN *
 *                 *
 *******************/
int main()
{
    // Input del problema Plaintext e Chipertext dato da AES-128
    
    unsigned char plaintext[16]= {0x54,0x68,0x61,0x74,0x73,0x20,0x6d,0x79,0x20,0x4b,0x75,0x6e,0x67,0x20,0x46,0x75};
    unsigned char ciphertext[16] = {0x28,0xfd,0xde,0xf8,0x6d,0xa4,0x24,0x4a,0xcc,0xc0,0xa4,0xfe,0x3b,0x31,0x6f,0x26};

    /* Ulteriori plaintext e ciphertext da provare: 

    unsigned char plaintext[16]= {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff};
    unsigned char ciphertext[16] = {0x69,0xc4,0xe0,0xd8,0x6a,0x7b,0x04,0x30,0xd8,0xcd,0xb7,0x80,0x70,0xb4,0xc5,0x5a};
    
    unsigned char plaintext[16]= {0x54,0x68,0x61,0x74,0x73,0x20,0x6d,0x79,0x20,0x4b,0x75,0x6e,0x67,0x20,0x46,0x75};
    unsigned char ciphertext[16] = {0x28,0xfd,0xde,0xf8,0x6d,0xa4,0x24,0x4a,0xcc,0xc0,0xa4,0xfe,0x3b,0x31,0x6f,0x26};

    unsigned char plaintext[16]= {0x54,0x77,0x6f,0x20,0x4f,0x6e,0x65,0x20,0x4e,0x69,0x6e,0x65,0x20,0x54,0x77,0x6f};
    unsigned char ciphertext[16] = {0x29,0xc3,0x50,0x5f,0x57,0x14,0x20,0xf6,0x40,0x22,0x99,0xb3,0x1a,0x02,0xd7,0x3a};
    
    */
    
    // Copia il plaintext nel vettore in di riferimento per AES-128
    copia_vettore(plaintext,in,16);
    
    // Menu di presentazione
    printf("GRASSI ATTACK\n\n");
    printf("Plaintext -->  ");
    stampa_vettore(plaintext,16);
    printf("Ciphertext --> "); 
    stampa_vettore(ciphertext,16);

    // Avvia Grassi Attack
    if(GrassiAttack(ciphertext))
    {
        printf("Attacco riuscito\n");
        printf("\nLa diagonale della chiave e': %x:%x:%x:%x\n",Key[0],Key[5],Key[10],Key[15]);
        return 0;
    }
    
    printf("Attacco non riuscito\n\n");

    return 0;
}



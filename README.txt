Implementazione del Grassi Attack per AES-128

Si vuole ottenere la diagonale della chiave partendo dal ciphertext e plaintext

Il comando per compilare l'intero progetto e' il seguente: 

gcc -Wall AES_Encrypt.c 5Round_Attack.c -O3 -o Attack

Per mostrare il tempo di esecuzione del programma provare con:

time ./Attack

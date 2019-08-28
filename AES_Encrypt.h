#ifndef _AES_ENCRYPT_H_
#define _AES_ENCRYPT_H_

/* Prototipi delle funzioni */

int getSBoxValue(int num);

void KeyExpansion();

void AddRoundKey(int round); 

void SubBytes();

void ShiftRows();

void MixColumns();

void Cipher();

#endif

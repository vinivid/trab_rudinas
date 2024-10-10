#ifndef SJ_H
#define SJ_H 

typedef struct scj_ scj;

scj* construir_scj(int n);
void push_scj(scj* scj, int val);
int tamanho_scj(scj* scj);
int ultimo_scj(scj* scj);
int sub_pos_scj(scj* scj, int index);
void destruir_scj(scj* scj);

#endif


#ifndef __FSA_H__ILRD__CR3_
#define __FSA_H__ILRD__CR3_

#include <stddef.h> /* size_t */

typedef struct fsa fsa_t;

/* Description: the function should calculate the overall size of memory needed to be allocated (including management struct and word-size alignment) */
size_t FsaSuggestedSize(size_t num_blocks, size_t block_size);

/* Description: the function creates the managment struct (and headers) ,and returns the pointer to that struct */
fsa_t *FsaInit(void *alloc_dest, size_t block_size, size_t suggested_size);

/* Description: the function should return a pointer to the next available block, and update the managment struct */
void *FsaAlloc(fsa_t *fsa);

/* Description: the function "frees" the block specified, and updates the managment struct accordingly */
void FsaFree(fsa_t *fsa, void *block);

/* Description: the function returns the number of available blocks */
size_t FsaCountFree(const fsa_t *fsa);

#endif /* __FSA_H__ILRD__CR3_ */

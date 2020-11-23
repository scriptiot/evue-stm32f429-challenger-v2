#ifndef EVM_MAIN_H
#define EVM_MAIN_H

void * vm_malloc(int size);
void vm_free(void * mem);

#ifdef __cplusplus
extern "C" {
#endif
int evm_main(char *file);
#ifdef __cplusplus
}
#endif

#endif

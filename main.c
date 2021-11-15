#include <stdio.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdint.h>

typedef int64_t address_t;

void encrypt_me(){
    puts("Sneaky function!");
}

int main()
{
    int retval = 0;

    puts("Main function");
    address_t page_aligned_addr = (address_t)encrypt_me & 0xFFF000;
    retval = mprotect((void *)page_aligned_addr, 4096, PROT_READ | PROT_WRITE | PROT_EXEC);
    if (retval < 0)
        return errno;

    void *addr = encrypt_me;

    address_t function_size = (address_t)main - (address_t)encrypt_me - 1;
    while (function_size > 0)
    {
        *(int *)addr = *(int *)addr ^ 0xFA;
        addr+=1;
        function_size -= 1;
    }
    
    encrypt_me();
}

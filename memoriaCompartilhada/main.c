#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

struct data {
    int a; char b[10]; long c;
};

    const int N = 4096*2;


int main() {
    int fd;
    struct data *addr;
    fd = shm_open("/xyz", O_RDWR | O_CREAT, 0600);
    ftruncate(fd, N);
    addr = mmap(NULL, N, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);
    addr->a = 5;
    addr->b[3] = 'C';
    addr->c = 0xffff;
    munmap(addr, N);
}

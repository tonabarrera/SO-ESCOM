#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int id_proc, x=10, y=15, z=5;
    if ((id_proc=fork())==0){
        y += z;
        printf("y: %i\n", y);
        if((id_proc=fork(1))==0){
            z *= x;
            if((id_proc=fork(1))==0){
                z *= x;
                z -= z;
                printf("x %i\n", x);
            }
            y+=x;
            printf("y %i\n", y);
            if((id_proc=fork(1))==0){
                z *= y;
                printf("z %i\n", z);
            }
            if((id_proc=fork())==0){
                x *= y;
                printf("x %i \n", x);
            }
            printf("x %i y %i z %i \n", x, y, z);
        }
        z -= x;
        if ((id.proc=fork(1))==0) {
            y -= z;
            printf("\n", );
        }
    }
}

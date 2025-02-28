#include <stdio.h>
#include <unistd.h>

#define FORALL_REGS(_)  _(X) _(Y) _(Z)
#define LOGIC           X1 = (!X&&Y)||(X&&!Y);  \
                        Y1 = !Y;
#define LOGIC3          X1 = (!X&&Y&&Z)||(X&&(!(Y&&Z)));  \
                        Y1 = (!Y&&Z)||(Y&&!Z);  \
                        Z1 = !Z;
#define DEFINE(X)       static int X, X##1;
#define UPDATE(X)       X = X##1;
#define PRINT(X)        printf(#X " = %d; ", X);
int main() {
    FORALL_REGS(DEFINE);
    while(1) {  // clock
        FORALL_REGS(PRINT);
        putchar('\n');
        sleep(1);
        LOGIC3;
        FORALL_REGS(UPDATE);
    }
}


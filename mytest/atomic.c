#include <pthread.h>
#include <stdatomic.h>
#include <stdio.h>
int a;
atomic_int b;

void* sum() {
    for (int i = 0; i < 10000000; i++) {
        a++;
        // b++;
        // b = b + 1;
        atomic_fetch_add(&b, 1);
    }
}

void test() {
    a = 0;
    b = ATOMIC_VAR_INIT(0);

    pthread_t t1, t2;
    pthread_create(&t1, NULL, sum, NULL);
    pthread_create(&t2, NULL, sum, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("a = %d  b = %d\n", a, b);
}

int main() {
    test();
    test();
    test();
}

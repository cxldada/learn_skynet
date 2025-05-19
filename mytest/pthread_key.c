#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_key_t key;
pthread_once_t init_done = PTHREAD_ONCE_INIT;

void test(void* keyAddr) {
    pthread_t tid = pthread_self();
    unsigned long* data = pthread_getspecific(key);
    if (data == NULL) {
        printf("tid: %lu -- keyAddr: %p -- data: %lu\n", tid, keyAddr, *((unsigned long*)keyAddr));
    } else {
        printf("tid: %lu -- keyAddr: %p\n", tid, keyAddr);
    }
    free(keyAddr);
}

void thread_init() {
    printf("thread_init init: %d\n", init_done);
    pthread_key_create(&key, test);
    printf("thread_init init: %d\n", init_done);
}

void* create_key(void* arg) {
    pthread_once(&init_done, thread_init);
    pthread_t tid = pthread_self();
    printf("tid: %lu -- work\n", tid);
    unsigned long* data = malloc(sizeof(int));
    *data = pthread_self();
    pthread_setspecific(key, data);
    return NULL;
}

int main() {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, create_key, NULL);
    pthread_create(&t2, NULL, create_key, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}

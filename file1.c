#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[], char *envp[]) {
    printf("PID = %d, PPID = %d\n", getpid(), getppid());
    printf("Аргументы командной строки:\n");
    for (int i = 0; i < argc; i++) {
        printf("Аргумент %d: %s\n", i, argv[i]);
        sleep(1);  
    }

    // Вывод переменных окружения
    if (envp != NULL && envp[0] != NULL) {
        printf("Переменные окружения:\n");
        for (int i = 0; envp[i] != NULL; i++) {
            printf("%s\n", envp[i]);
        }
    }
    exit(5);
}

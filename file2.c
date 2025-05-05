#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    printf("PID = %d, PPID = %d\n", getpid(), getppid());
    printf("Аргументы командной строки:\n");
    for (int i = 0; i < argc; i++) {
        printf("Аргумент %d: %s\n", i, argv[i]);
    }

    // Создание дочернего процесса
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }


    if (pid == 0) {  // Дочерний процесс
        char *new_path = getenv("PATH");
        if (new_path == NULL || strstr(new_path, ":.") == NULL) {
            // текущий каталог в PATH, если его там нет
            setenv("PATH", ".:/usr/local/bin:/usr/bin:/bin", 1);
        }
        argv[0] = "file1";
        char *envp[] = {"MY_ENV_VAR=123", NULL};

        // Запуск дочерней программы
        if (execvpe("file1", argv, envp) == -1) { 
            perror("execvpe");
            exit(EXIT_FAILURE);
        }
    } else {  // Родительский процесс
        // Ожидание завершения дочернего процесса
        int status;
        while (1) {
            pid_t result = waitpid(pid, &status, WNOHANG);
            if (result == -1) {
                perror("waitpid");
                exit(EXIT_FAILURE);
            } else if (result == 0) {
                // Дочерний процесс ещё не завершился
                usleep(500000);  // Задержка 0.5 секунды
            } else {
                // Дочерний процесс завершился
                if (WIFEXITED(status)) {
                    printf("Дочерний процесс завершился с кодом: %d\n", WEXITSTATUS(status));
                } else {
                    printf("Дочерний процесс завершился аварийно\n");
                }
                break;
            }
        }
    }

    return 0;
}

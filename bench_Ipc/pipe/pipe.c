#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include "benchmar.h"
#include <sys/wait.h>
#define size 8

benck heureDebut(){
   struct timespec ts;
   timespec_get(&ts, TIME_UTC);

	return ts.tv_sec * 1e9 + ts.tv_nsec;
}

void initialBench(Benchmar *bench){

    bench->maximum = 0;

    bench->minimum = heureDebut();

    bench->sum = 0;

    bench->start = heureDebut();
}

void BenchStar(Benchmar *bench){
    time_t time = heureDebut() - bench->start;
    printf("timer : %lu\n",time);
    
    if(time < bench->minimum){
        bench->minimum = time;
    }

    if(time > bench->maximum){
        bench->maximum = time;
    }

    bench->sum = bench->sum + time;
}


void client_communication(int fd[2]){

    FILE * stream;
    int reader = 2;

    char mode[1];
    mode[0] = 'r';

    char buffer[reader + 5];

    stream = fdopen(fd[0], mode);

    if(stream == NULL){
        printf("Fichier non accessible");
    }

     for (;;) {
        int count = fread(buffer, reader, 1, stream);
        
        if (count == 0) break;
        
        buffer[count] = '\0';

        printf("L'enfant a lu carateres : %s\n", buffer);

    }

    close(fd[0]);

    printf("Le parent attent l'enfant\n");
    printf("Parent exit\n");
    wait(NULL);
    exit(0);


}

void serveur_communication(int fd[2]){
    FILE *stream;
    struct Benchmar bench;
    char buffer[20];
    int writer = 2;
    
    strcpy(buffer, "carlos");
    char mode[1];
    mode[0] = 'w';

    stream = fdopen(fd[1], mode);

    if(stream == NULL){
        printf("Fichier non accessible");
    }

    initialBench(&bench);

    for(int message=0; message < strlen(buffer); message ++){

        bench.start = heureDebut();
        fwrite(buffer, writer, 1, stream);
          printf("Le parent a ecrire comme caractere : %c\n",buffer[message]);


       // write(fd[1], buffer, writer);
        BenchStar(&bench);
        printf("temps minimum pour chaque caractere %lu\n", bench.minimum);
        printf("temps ,maximum pour chaque caractere %lu\n", bench.maximum);
        printf("Somme total %lu\n", bench.sum);
    }



	printf("\n============ RESULTS ================\n");
	printf("Taille du Message :       %d\n", 1);
	printf("Nombre de Message :      %ld\n", strlen(buffer));
    printf("Duree Minimum :   %.3f\tus\n", bench.minimum / 1000.0);
	printf("Duree Maximum :   %.3f\tus\n", bench.maximum / 1000.0);
    printf("Duree Total :   %.3f\tus\n", bench.sum / 1000.0);

	printf("=====================================\n");

    close(fd[1]);


}

void communication(int fd[2]){
    pid_t pid = fork();

    if(pid == -1){
        fprintf(stderr, "impossible de creer le processus");
    }

    if(pid == 0){
        client_communication(fd);
    }

    else {
        serveur_communication(fd);
    }
}

int main(){

    int fd[2];

    if(pipe(fd) == -1){
        fprintf(stderr,"Impossible de creer le pipe");
        exit(0);
    }

    communication(fd);

    return 0;
}
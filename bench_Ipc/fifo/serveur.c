#include "benchmar.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>


benck heureDebut(){
   struct timespec ts;
   timespec_get(&ts, TIME_UTC);

	return ts.tv_sec * 1e9 + ts.tv_nsec;
}

void initialBench(Benchmar *bench){

    bench->maximum = 0;

    bench->minimum = heureDebut();;

    bench->sum = 0;

    bench->start = heureDebut();
}

void BenchStar(Benchmar *bench){
    time_t time = heureDebut() - bench->start;

    if(time < bench->minimum){
        bench->minimum = time;
    }

    if(time > bench->maximum){
        bench->maximum = time;
    }

    bench->sum = bench->sum + time;
}


void cleanup(FILE *stream, void *buffer) {
	free(buffer);
	fclose(stream);
}


FILE* open_fifo() {
	FILE* stream;
    int a = mkfifo("benh_fifo",0777);

	if (mkfifo("benh_fifo", 0777) > 0) {
		printf("Impossible de creer fifo");
	}

	if ((stream = fopen("bench_fifo", "w")) == NULL) {
		printf("Erreur d'ouverture ecriture");
	}

	return stream;
}

void communicate_serveur(FILE * stream){
     
    struct Benchmar bench;
    char buffer[20];
    int writer = 2;
    
    strcpy(buffer, "carlos");
    char mode[1];
    mode[0] = 'w';


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
        printf("duree total %lu\n", bench.sum);
    }




	printf("\n============ RESULTS ================\n");
	printf("Taille du Message :       %d\n", 1);
	printf("Nombre de Message :      %ld\n", strlen(buffer));
    printf("Duree Minimum :   %.3f\tus\n", bench.minimum / 1000.0);
	printf("Duree Maximum :   %.3f\tus\n", bench.maximum / 1000.0);
    printf("Duree total:   %.3f\tus\n",bench.sum / 1000.0);

	printf("=====================================\n");

  // cleanup(stream, buffer);
}

int main(int argc, char *argv[]) {

	FILE *stream;

    stream = open_fifo();

	communicate_serveur(stream);

	return EXIT_SUCCESS;

}

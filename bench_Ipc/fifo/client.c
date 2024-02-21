#include "benchmar.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <sys/wait.h>


#define FIFO_PATH "/tmp/ipc_bench_fifo"

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

	if ((stream = fopen("bench_fifo", "r")) == NULL) {
		printf("Erreur d'ouverture en mode lecture");
	}

	return stream;
}

void communicate_client(FILE *stream){
    
    int reader = 2;

    char mode[1];
    mode[0] = 'r';

    char buffer[reader + 5];

    if(stream == NULL){
        printf("Fichier non accessible");
    }

     for (;;) {
        int count = fread(buffer, reader, 1, stream);
        
        if (count == 0) break;
        
        buffer[count] = '\0';

        printf("L'enfant a lu carateres : %s\n", buffer);

    }


    printf("Le parent attent l'enfant\n");
    printf("Parent exit\n");
    wait(NULL);
    exit(0);

}


int main(int argc, char *argv[]) {

	FILE *stream;
    stream = open_fifo();

	communicate_client(stream);

	return EXIT_SUCCESS;


}

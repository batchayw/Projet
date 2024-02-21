#include "benchmar.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

benck heureDebut(){
   time_t now = time(NULL);
   return now;
}

void initialBench(Benchmar *bench){

    bench->maximum = 0;

    bench->minimum = 0;

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


void evaluate(Benchmar *bench){


}
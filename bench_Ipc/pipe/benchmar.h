#ifndef BENCHMAR_H_INCLUDED
#define BENCHMAR_H_INCLUDED

typedef unsigned long int benck;

typedef struct Benchmar{
    
    benck minimum;

    benck maximum;
    
    benck sum;

    benck start;

}  Benchmar;

void initialBench(Benchmar *bench);

benck heureDebut();

void BenchStar(Benchmar *bench);

void evaluate(Benchmar *bench);



#endif
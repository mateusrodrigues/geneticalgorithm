//
// Created by mateu on 3/15/2019.
//

#ifndef GENETICALGORITHM_DNA_H
#define GENETICALGORITHM_DNA_H

#include <random>

#define SEARCH_LOWER_BOUND -5.0f
#define SEARCH_UPPER_BOUND 5.0f

class dna {

private:
    float x1;
    float x2;
    float fitness;

    std::default_random_engine generator;

public:
    dna();
    dna(float x1, float x2);

    float getX1();
    float getX2();
    float getFitness();

    void evaluateFitness();
    dna crossover(dna *partner);
    void mutate(float mutationRate);

};


#endif //GENETICALGORITHM_DNA_H

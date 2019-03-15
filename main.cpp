#include <iostream>
#include <vector>

#include "dna.h"

#define MUTATION_RATE 0.01
#define TOTAL_POPULATION 5

using namespace std;

void populate(vector<dna> *population, std::default_random_engine& generator);

int main() {
    std::random_device rd;
    std::default_random_engine generator(rd());

    auto *population = new vector<dna>;
    populate(population, generator);

    for (unsigned int i = 0; i < TOTAL_POPULATION; i++) {
        cout << "(" << (population->at(i)).getX1() << ", " << (population->at(i)).getX2() << ")" << endl;
    }

    int generationCounter = 1;
    while (generationCounter < 1000) {
        cout << "---- Generation " << ++generationCounter << " ----" << endl;

        // 1. create mating pool for reproduction
        vector<dna> matingPool;
        for (unsigned int i = 0; i < TOTAL_POPULATION; i++) {
            int fitness = (int)(population->at(i)).getFitness();

            for (int j = 0; j < fitness; j++) {
                matingPool.push_back(population->at(i));
            }
        }

        // 2. crossover DNAs to generate a new population
        std::uniform_int_distribution<unsigned int> matingDistribution(0, population->size() + 1);
        for (unsigned int i = 0; i < TOTAL_POPULATION; i++) {
            unsigned int dadIndex = matingDistribution(generator);
            unsigned int momIndex = matingDistribution(generator);

            dna dad = matingPool.at(dadIndex);
            dna mom = matingPool.at(momIndex);

            dna child = dad.crossover(&mom);

            child.mutate(MUTATION_RATE, generator);
            child.evaluateFitness();

            population->at(i) = child;
        }

        // 3. Print out elements
        for (unsigned int i = 0; i < TOTAL_POPULATION; i++) {
            cout << "(" << (population->at(i)).getX1() << ", " << (population->at(i)).getX2() << ")" << endl;
        }
    }

    delete population;

    return 0;
}

void populate(vector<dna> *population, std::default_random_engine& generator) {
    for (int i = 0; i < TOTAL_POPULATION; i++) {
        population->push_back(dna(generator));
    }
}
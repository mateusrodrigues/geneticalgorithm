//
// Created by mateu on 3/15/2019.
//

#include "dna.h"
#include <random>

dna::dna(std::default_random_engine& generator) {
    std::uniform_real_distribution<float> distribution(SEARCH_LOWER_BOUND, SEARCH_UPPER_BOUND);
    this->x1 = distribution(generator);
    this->x2 = distribution(generator);

    evaluateFitness();
}

dna::dna(float x1, float x2) {
    this->x1 = x1;
    this->x2 = x2;

    evaluateFitness();
}

float dna::getX1() {
    return this->x1;
}

float dna::getX2() {
    return this->x2;
}

float dna::getFitness() {
    return this->fitness;
}

void dna::evaluateFitness() {
    fitness = fitnessFunction();
}

dna dna::crossover(dna *partner) {
    return dna(this->x1, partner->x2);
}

void dna::mutate(float mutationRate, std::default_random_engine& generator) {
    std::uniform_real_distribution<float> mutationDistribution(0.0, 1.0);
    std::uniform_int_distribution<int> chromosomeDistribution(0, 2); /* should be 0 or 1 */
    std::uniform_real_distribution<float> valueDistribution(SEARCH_LOWER_BOUND, SEARCH_UPPER_BOUND);

    if (mutationDistribution(generator) < mutationRate) {
        if (chromosomeDistribution(generator) == 0) {
            this->x1 = x1 + valueDistribution(generator);

            if (x1 > 5) x1 = 5;
            else if (x1 < -5) x1 = -5;
        } else {
            this->x2 = x2 + valueDistribution(generator);

            if (x2 > 5) x2 = 5;
            else if (x2 < -5) x2 = -5;
        }
    }
}

float dna::fitnessFunction() {
    return powf(powf((powf(x1, 2) + x2 - 11), 2) + powf((x1 + powf(x2, 2) - 7), 2) + 10, -1) * 10000;
}

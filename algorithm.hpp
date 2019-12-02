//
// Created by Alec on 2019-12-01.
//

#ifndef ASSINGMENT2_ALGORITHM_HPP
#define ASSINGMENT2_ALGORITHM_HPP

#include <random>
#include <iostream>
#include <vector>
#include "city.hpp"
#include "tour.hpp"
#include <algorithm>
#include <iterator>
using namespace std;
/**
 * algorithm class that uses the GeneticAlgorithm to find a better solution to the travelling salesman problem
 */
class algorithm {
public:
    int CITIES_IN_TOUR = 32;
    unsigned long POPULATION_SIZE = 32;
    int MAP_BOUNDARY = 1000;
    int NUMBER_OF_ELITES = 1;
    double MUTATION_RATE = 0.01;
    unsigned long PARENT_POOL_SIZE = 5;
    unsigned long NUMBER_OF_PARENTS = 5;
    double IMPROVEMENT_FACTOR = 0.999;
    int ITERATIONS = 1000;

    algorithm();
    void shuffle_cities(tour& t);
    int  find_best_fitness_in_pop(vector<tour> &p, int size);
    double get_tour_distance(tour&t);
    double get_distance_between_cities(city first, city second);
    void mutate(tour &t, double rate);
    void swap_cities(int first, int second, vector<city> &cities);
    tour crossover(vector<tour> &parents);
    bool contains_city(tour &candidate_tour, int length, city &candidate_city);
    vector<tour> select_parents(vector<tour> &p);
};


#endif //ASSINGMENT2_ALGORITHM_HPP

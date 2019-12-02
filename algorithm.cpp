//
// Created by Alec on 2019-12-01.
//

#include <chrono>
#include <iomanip>
#include <unistd.h>
#include "algorithm.hpp"

algorithm::algorithm() {
    tour masterList;
    vector<tour> population{POPULATION_SIZE};
    double best = 0.0;
    double base = 0.0;
    //add
    for (int i = 0; i < CITIES_IN_TOUR; i++) {
        city c = {i, rand() % (MAP_BOUNDARY + 1), rand() % (MAP_BOUNDARY + 1)};
        masterList.cities[i] = c;
    }
    for (int i = 0; i < POPULATION_SIZE; i++) {
        for (int j = 0; j < CITIES_IN_TOUR; j++) {
            population[i].cities[j] = masterList.cities[j];
        }
        shuffle_cities(population[i]);
        population[i].fitness = 0.0;
    }
    for (int i = 0; i < POPULATION_SIZE; ++i) {
        cout<< "========================================= " << i << " =========================================" <<endl;
        for (auto c : population[i].cities) {
            cout << c.name << " ";
        }
        cout<< endl;
    }
    cout<< endl;
    int best_tour_index = find_best_fitness_in_pop(population, static_cast<int>(POPULATION_SIZE));
    base =  population[best_tour_index].fitness;
    cout << "Base Distance: " << fixed << setprecision(3) << base << endl;

        mutate(population[0], MUTATION_RATE);

}

void algorithm::shuffle_cities(tour& t) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(t.cities.begin(), t.cities.end(),   std::default_random_engine (seed));
}

int algorithm:: find_best_fitness_in_pop (vector<tour> &t, int size){
    double cur_best = INFINITY;
    int i_best = 0;
    double candidate = 0.0;
    for (int i = 0; i < size; ++i) {
        candidate = get_tour_distance(t[i]);
        t[i].fitness = candidate;
        if (candidate <= cur_best) {
            i_best = i;
            cur_best = candidate;
        }
    }
    return i_best;
}
double algorithm::get_tour_distance(tour &t) {
    double distance = 0.0;
    for (int i = 0; i < CITIES_IN_TOUR; ++i) {
        distance += get_distance_between_cities(t.cities[i], t.cities[(i + 1) % CITIES_IN_TOUR]);
    }
    return distance;
}
double algorithm::get_distance_between_cities(city c1, city c2) {
    double pythagoras = sqrt(pow((double) (c1.x - c2.y), 2.0) + pow((double) (c1.y - c2.y), 2.0));
    return  pythagoras;
}

void algorithm::mutate(tour &t, double rate) {
    for (int i = 0 + NUMBER_OF_ELITES; i < POPULATION_SIZE; ++i) {
        for(int j = 0; j < CITIES_IN_TOUR; ++j){
            if((rand()%2) < rate){
                swap_cities(j, rand() % CITIES_IN_TOUR, t.cities);
            }
        }
    }
}

void algorithm::swap_cities(int first, int second, vector<city> &cities) {
    city c = cities[first];
    cities[first] = cities[second];
    cities[second] = c;
}


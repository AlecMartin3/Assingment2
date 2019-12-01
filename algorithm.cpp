//
// Created by Alec on 2019-12-01.
//

#include <chrono>
#include "algorithm.hpp"

algorithm::algorithm() {
    tour masterList;
    vector<tour> population{POPULATION_SIZE};

    for (int i = 0; i < CITIES_IN_TOUR; ++i) {
        city c = {i, rand() % (MAP_BOUNDARY + 1), rand() % (MAP_BOUNDARY + 1)};
        masterList.cities[i] = c;
    }
    for (int i = 0; i < POPULATION_SIZE; ++i) {
        for (int j = 0; j < CITIES_IN_TOUR; ++j) {
            population[i].cities[j] = masterList.cities[j];
        }
        shuffle_cities(population[i]);
    }
    for (int i = 0; i < POPULATION_SIZE; ++i) {
        for (auto c : population[i].cities) {
            cout << c.name << " ";
        }
        cout << endl;
    }

}

void algorithm::shuffle_cities(tour& t) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(t.cities.begin(), t.cities.end(),   std::default_random_engine (seed));
}
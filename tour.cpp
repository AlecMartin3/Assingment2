//
// Created by Alec on 2019-12-01.
//

#include "tour.hpp"

/**
 * Tour constructor
 * Makes a tour, which is a list of all the cities, and initializes them with 0s
 */
tour:: tour(){
    fitness = 0.0;
    city c = {0, 0, 0};
    for (int i = 0; i < CITIES_IN_TOUR; ++i) {
        cities.push_back(c);
    }
}
/**
 * Used for crossover.
 * Uses std::swap
 * @param t
 * @return tour
 */
tour &tour::operator=(tour t) {
    swap(cities, t.cities);
    swap(fitness, t.fitness);
    return *this;
}
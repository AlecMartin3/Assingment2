//
// Created by Alec on 2019-12-01.
//

#include <chrono>
#include <iomanip>
#include <unistd.h>
#include "algorithm.hpp"

/**
 * algorithm constructor
 * Makes the genetic algorithm for the travelling salesman problem
 * Uses crossover, mutate, tours, cities, selection, improvement factor, and reports it all
 */
algorithm::algorithm() {
    // Create a master list that will have all the cities
    tour masterList;
    vector<tour> population{POPULATION_SIZE};
    vector<tour> newPop{POPULATION_SIZE - NUMBER_OF_ELITES};
    double best = 0.0;
    double distance = 0.0;

    //Make all the cities in the master list have random values and have names from 0 to i
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

    cout << endl;
    int best_tour_index = find_best_fitness_in_pop(population, static_cast<int>(POPULATION_SIZE));
    tour temp_tour = population[best_tour_index];

    cout << "Base route: ";
    for(auto c : temp_tour.cities){
        cout << c.name << " ";
    }
    cout << endl;
    distance = population[best_tour_index].fitness;
    cout << "Base Distance: " << fixed << setprecision(3) << distance << endl;
    double base = distance;
    int iteration = 0;
    int successful_iterations = 1;
    double distance_diff;
    while (++iteration < ITERATIONS && base / best > IMPROVEMENT_FACTOR) {
        if (best_tour_index != 0) {
            const tour temp_tour = population[0];
            population[0] = population[best_tour_index];
            population[best_tour_index] = temp_tour;
        }

        for (int i = 0; i < (POPULATION_SIZE - NUMBER_OF_ELITES); ++i) {
            vector<tour> parents = select_parents(population);
            newPop[i] = crossover(parents);
        }
        for (int i = NUMBER_OF_ELITES; i < POPULATION_SIZE; ++i) {
            population[i] = newPop[i - NUMBER_OF_ELITES];
            population[i].fitness = 0.0;
        }
        mutate(population[0], MUTATION_RATE);
        best_tour_index = find_best_fitness_in_pop(population, static_cast<int>(POPULATION_SIZE));

        best = get_tour_distance(population[best_tour_index]);
        if (best < distance) {
            distance_diff += (distance - best);
            distance = best;
            cout << "Iteration: " << successful_iterations++ << endl;
                for (auto c : population[best_tour_index].cities) {
                    cout << c.name << " ";
                }
                cout << endl;
            cout << "Current smallest distance: " << fixed << setprecision(3) << best << endl;
            cout << distance_diff << " improvement from starting distance." << endl;
            cout << endl;
        }
    }
    print_report(iteration, base, best, temp_tour, population, best_tour_index);
}

/**
 * Shuffles all the cities in a tour with each other making them have a random order
 * @param t
 */
void algorithm::shuffle_cities(tour& t) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(t.cities.begin(), t.cities.end(),   std::default_random_engine (seed));
}
/**
 * Finds the best fitness in a population and returns its index
 * @param t
 * @param size
 * @return
 */
int algorithm:: find_best_fitness_in_pop (vector<tour> &t, int size){
    //Start with infinity so that it will always be replaced the first time
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
/**
 * Gets the total distance of a tour.
 * Uses a cumulative distance of all the distances between the cities that the tour takes
 * @param t
 * @return
 */
double algorithm::get_tour_distance(tour &t) {
    double distance = 0.0;
    for (int i = 0; i < CITIES_IN_TOUR; ++i) {
        distance += get_distance_between_cities(t.cities[i], t.cities[(i + 1) % CITIES_IN_TOUR]);
    }
    return distance;
}
/**
 * Gets the distance between two cities by using the pythagorean theorem
 * @param c1
 * @param c2
 * @return
 */
double algorithm::get_distance_between_cities(city c1, city c2) {
    double pythagoras = sqrt(pow((double) (c1.x - c2.y), 2.0) + pow((double) (c1.y - c2.y), 2.0));
    return  pythagoras;
}
/**
 * Mutates a tour, by a mutation rate, by swaping random cities
 * @param t
 * @param rate
 */
void algorithm::mutate(tour &t, double rate) {
    for (int i = 0 + NUMBER_OF_ELITES; i < POPULATION_SIZE; ++i) {
        for(int j = 0; j < CITIES_IN_TOUR; ++j){
            if((rand()%2) < rate){
                swap_cities(j, rand() % CITIES_IN_TOUR, t.cities);
            }
        }
    }
}
/**
 * Swaps two cities by using a temp city
 * @param first
 * @param second
 * @param cities
 */
void algorithm::swap_cities(int first, int second, vector<city> &cities) {
    city c = cities[first];
    cities[first] = cities[second];
    cities[second] = c;
}

/**
 * Takes the parent tours and combines them by first: making a random index, then filling in all the cities from
 * 0 to the random index, then filling in the rest of the cities from the next parent.
 * @param parents
 * @return the combined child
 */
tour algorithm::crossover(vector<tour> &parents) {
    tour child;
    //Random index
    int boundary_index = rand() % CITIES_IN_TOUR;
    //fill from first parent
    for (int i = 0; i < boundary_index; ++i) {
        child.cities[i] = parents[0].cities[i];
    }
    //from the boundary index fill the rest of the cities from the remaining parents
    while (boundary_index < CITIES_IN_TOUR) {
        for (int i = 0; i < CITIES_IN_TOUR; ++i) {
            for (int j = 1; j < NUMBER_OF_PARENTS; j++) {
                if (!contains_city(child, boundary_index, parents[j].cities[i])) {
                    child.cities[boundary_index] = parents[j].cities[i];
                    boundary_index++;
                }
            }
        }
    }
    return child;
}
/**
 * Checks for the crossover if the candidate tour contains a city that has already been filled
 * @param candidate_tour
 * @param length
 * @param candidate_city
 * @return
 */
bool algorithm::contains_city(tour &candidate_tour, int length, city &candidate_city) {
    for (int i = 0; i < length; ++i) {
        if (candidate_tour.cities[i].name == candidate_city.name &&
            candidate_tour.cities[i].x == candidate_city.x &&
            candidate_tour.cities[i].y == candidate_city.y) {
            return true;
        }
    }
    return false;
}
/**
 * Selects the fittest parents from the population of p.
 * @param p
 * @return
 */
vector<tour> algorithm::select_parents(vector<tour> &p) {
    int p_index = 0;
    vector<tour> parents{NUMBER_OF_PARENTS};
    vector<tour> parent_pool{PARENT_POOL_SIZE};

    for (int i = 0; i < NUMBER_OF_PARENTS; ++i) {
        for (int j = 0; j < PARENT_POOL_SIZE; ++j) {
            int k = static_cast<int>(rand() % POPULATION_SIZE);
            parent_pool[j] = p[k];
        }
        p_index = find_best_fitness_in_pop(parent_pool, static_cast<int>(PARENT_POOL_SIZE));
        parents[i] = parent_pool[p_index];
    }
    return parents;
}

void algorithm:: print_report(int iteration, double base, double best, tour base_tour, vector<tour> population, int best_tour_index){
    cout << "==========================================================================================" << endl;
    cout << "Total number of iterations: " << iteration << endl;
    cout << "Base distance: " << base << endl;
    cout << "Final distance: " << best << endl;
    cout << "Base route: ";
    for(auto c : base_tour.cities){
        cout << c.name << " ";
    }
    cout << endl;
    cout << "Optimal route: ";
    for (auto c : population[best_tour_index].cities) {
        cout << c.name << " ";
    }
    cout << endl;
    if( best / base < IMPROVEMENT_FACTOR){
        cout<< "Can no longer be improved easily (IMPROVEMENT_FACTOR)" <<endl;
    }
    else{
        cout<< "Can still be improved easily (IMPROVEMENT_FACTOR)" <<endl;
    }
}



import numpy as np
import threading
from threading import Thread

from . import ImageHandler
from ._Plotter import de_graph

class DifferentialEvolution:
    def __init__(self, func, original_image, maxiter, popsize, mut, crossp):
        self.func = func
        self.original_image = original_image
        self.maxiter = maxiter
        self.popsize = popsize
        self.mut = mut
        self.crossp = crossp
        self.dimensions = self.original_image.shape

    def initialise_population(self):
        pop = np.random.rand(self.popsize, *self.dimensions)
        pop = self.original_image + pop * 0.2
        return pop

    def evaluate_fitness(self, pop):
        print("DEBUG: STARING EVALUATION")
        fitness = np.zeros(self.popsize)
        for i in range(self.popsize):
            enhanced_image = np.clip(pop[i], 0, 1)
            fitness[i] = self.func(self.original_image, enhanced_image)

        print(f"DEBUG: EVALUATING FITNESS: {fitness}")
        return fitness

    def mutate(self, pop, ind):
        print("DEBUG: MUTATE CALLED")
        idxs = [idx for idx in range(self.popsize) if idx != ind]
        a, b, c = pop[np.random.choice(idxs, 3, replace=False)]
        mutant = a + self.mut * (b - c)

        mutant[:, :, 0] = np.clip(mutant[:, :, 0], 0, 360)
        mutant[:, :, 1:] = np.clip(mutant[:, :, 1:], 0, 1)

        return mutant

    def crossover(self, pop, ind, mutant):
        print("DEBUG: CROSSOVER CALLED")
        trial = np.zeros_like(pop[ind])
        for i in range(self.dimensions[0]):
            for j in range(self.dimensions[1]):
                for k in range(self.dimensions[2]):
                    r = np.random.rand(0, 1)
                    rd = np.random.randint(1, self.dimensions[2] + 1)

                    if r <= self.crossp or rd == k:
                        trial[i, j, k] = mutant[i, j, k]
                    else:
                        trial[i, j, k] = pop[ind, i, j, k]

        trial[:, :, 0] = np.clip(trial[:, :, 0], 0, 360)
        trial[:, :, 1:] = np.clip(trial[:, :, 1:], 0, 100)

        return trial

    def select(self, pop, fitness, ind, trial):
        print("DEBUG: SELECT CALLED")
        trial[:, :, 0] = np.clip(trial[:, :, 0], 0, 360)
        trial[:, :, 1:] = np.clip(trial[:, :, 1:], 0, 100)

        f_trial = self.func(self.original_image, trial)
        if f_trial >= fitness[ind]:
            fitness[ind] = f_trial
            pop[ind] = trial
        return pop, fitness

    def optimize(self):
        iterations = []
        fitnesses = []

        pop = self.initialise_population()
        fitness = self.evaluate_fitness(pop)

        best_idx = np.argmax(fitness)
        best = pop[best_idx].copy()

        for _ in range(self.maxiter):
            for ind in range(self.popsize):
                mutant = self.mutate(pop, ind)
                trial = self.crossover(pop, ind, mutant)
                pop, fitness = self.select(pop, fitness, ind, trial)

                best_idx = np.argmax(fitness)
                best = pop[best_idx].copy()

                iterations.append(_)
                fitnesses.append(fitness[np.argmax(fitness)])

            de_graph(iterations, fitnesses)
            print(f'Iteration: {_}, Best Fitness: {fitness[best_idx]}, Best Population: {best}')

            #ImageHandler.ImageHandler.de_iteration_test(_, best)

        return best

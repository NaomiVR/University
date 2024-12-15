import numpy as np

from ImageEnhance import ImageHandler
from ImageEnhance._Plotter import sa_graph


class SimulatedAnnealing:
    def __init__(self, func, initial_solution, maxiter, initial_temperature, cooling_rate, min_temperature):
        self.func = func
        self.initial_solution = initial_solution
        self.maxiter = maxiter
        self.initial_temperature = initial_temperature
        self.cooling_rate = cooling_rate
        self.min_temperature = min_temperature

    @staticmethod
    def perturb(solution):
        new_solution = solution.copy()
        idx = np.random.randint(len(new_solution))
        new_solution[idx] += np.random.uniform(-1, 1)

        new_solution[:, :, 0] = np.clip(new_solution[:, :, 0], 0, 360)
        new_solution[:, :, 1:] = np.clip(new_solution[:, :, 1:], 0, 100)

        return new_solution

    def evaluate(self, solution):
        return self.func(self.initial_solution, solution)

    @staticmethod
    def accept_solution(current_cost, new_cost, temperature):
        delta_cost = new_cost - current_cost
        return delta_cost < 0 or np.random.rand() < np.exp(-delta_cost / temperature)

    def cooling(self, temperature):
        return temperature * self.cooling_rate

    def optimize(self):
        iterations = []
        fitnesses = []

        current_solution = self.initial_solution
        current_cost = self.evaluate(current_solution)

        temp = self.initial_temperature

        for _ in range(self.maxiter):
            new_solution = self.perturb(current_solution)
            new_cost = self.evaluate(new_solution)

            if self.accept_solution(current_cost, new_cost, temp):
                current_solution = new_solution
                current_cost = new_cost

            temp = self.cooling(temp)

            iterations.append(_)
            fitnesses.append(current_cost)

            #ImageHandler.ImageHandler.sa_iteration_test(_, current_solution)

        sa_graph(iterations, fitnesses)
        return current_solution

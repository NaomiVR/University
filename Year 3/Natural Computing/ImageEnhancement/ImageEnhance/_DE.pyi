import numpy as np

from typing import Callable, Tuple


class DifferentialEvolution:
    func: Callable
    original_image: np.ndarray
    maxiter: int
    popsize: int
    mut: float
    crossp: float
    dimensions: np.ndarray

    def __init__(
            self,
            func: Callable,
            original_image: np.ndarray,
            maxiter: int = 100,
            popsize: int = 20,
            mut: float = 0.5,
            crossp: float = 0.5
    ) -> None: ...

    def initialise_population(self) -> np.ndarray: ...

    def evaluate_fitness(self, pop: np.ndarray) -> np.ndarray: ...

    def mutate(self, pop: np.ndarray, ind: int) -> np.ndarray: ...

    def crossover(self, pop: np.ndarray, ind: int, mutant: np.ndarray) -> np.ndarray: ...

    def select(self, pop: np.ndarray, fitness: np.ndarray, ind: int, trial: np.ndarray) -> Tuple[np.ndarray, np.ndarray]: ...

    def optimize(self) -> np.ndarray: ...
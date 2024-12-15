import numpy as np

from typing import Callable


class SimulatedAnnealing:
    func: Callable
    initial_solution: np.ndarray
    maxiter: int
    initial_temperature: float
    cooling_rate: float
    min_temperature: float

    def __init__(
            self,
            func: Callable,
            initial_solution: np.ndarray,
            maxiter: int = 100,
            initial_temperature: float = 100.0,
            cooling_rate: float = 0.95,
            min_temperature: float = 0.01
    ) -> None: ...

    @staticmethod
    def perturb(solution: np.ndarray) -> np.ndarray: ...

    def evaluate(self, solution: np.ndarray) -> float: ...

    @staticmethod
    def accept_solution(current_cost: float, new_cost: float, temperature: float) -> bool: ...

    def cooling(self, temperature: float) -> float: ...

    def optimize(self) -> np.ndarray: ...
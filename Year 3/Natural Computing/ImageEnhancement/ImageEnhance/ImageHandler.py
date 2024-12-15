from PIL import Image
import numpy as np

from ImageEnhance._Fitness import fitness_function
from ImageEnhance.OtherFitness import fitness_function_
from ImageEnhance._DE import DifferentialEvolution
from ImageEnhance._SA import SimulatedAnnealing


class ImageHandler:
    def __init__(self, filepath, func):
        self.filepath = filepath
        self.func = func
        self._hsv_image = []
        self._width = 0
        self._height = 0

    def read_image(self):
        inp_image = Image.open(self.filepath).convert('HSV')
        self._width, self._height = inp_image.size
        self._hsv_image = np.array(inp_image)

    def write_image(self, new_hsv_image):
        image = Image.fromarray(new_hsv_image.astype('uint8'), 'HSV')
        image = image.convert('RGB')
        if self.func == 1:
            image.save(f'my_fitness\\{self.filepath[:-4]}_enhanced{self.filepath[-4:]}')
        else:
            image.save(f'other_fitness\\{self.filepath[:-4]}_enhanced{self.filepath[-4:]}')

    @staticmethod
    def de_iteration_test(iteration, hsv_image):
        image = Image.fromarray(hsv_image.astype('uint8'), 'HSV')
        image = image.convert('RGB')
        image.save(f'other_fitness\\de_miter_5_psize_5_mut_05_crossp_05\\iteration_{iteration}.jpg')

    @staticmethod
    def sa_iteration_test(iteration, hsv_image):
        image = Image.fromarray(hsv_image.astype('uint8'), 'HSV')
        image = image.convert('RGB')
        image.save(f'other_fitness\\sa_cr_0_95_mt_0_01\\iteration_{iteration}.jpg')

    def point_processing(self):
        DE = DifferentialEvolution(
            func=fitness_function if self.func == 1 else fitness_function_,
            original_image=self._hsv_image,
            maxiter=5,
            popsize=5,
            mut=0.5,
            crossp=0.5
        )

        de_result = DE.optimize()

        SA = SimulatedAnnealing(
            func=fitness_function if self.func == 1 else fitness_function_,
            initial_solution=de_result,
            maxiter=100,
            initial_temperature=100,
            cooling_rate=0.95,
            min_temperature=0.01
        )

        sa_result = SA.optimize()

        self.write_image(sa_result)

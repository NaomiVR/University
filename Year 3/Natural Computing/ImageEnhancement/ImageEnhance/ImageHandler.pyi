import numpy as np


class ImageHandler:
    filepath: str
    func: int
    _hsv_image: np.array
    _width: int
    _height: int

    def __init__(
            self,
            filepath: str,
            func: int
    ) -> None: ...

    def read_image(self) -> None: ...

    def write_image(self, new_hsv_image: np.array) -> None: ...

    @staticmethod
    def de_iteration_test(iteration, hsv_image) -> None: ...

    @staticmethod
    def sa_iteration_test(iteration, hsv_image) -> None: ...

    def point_processing(self) -> None: ...
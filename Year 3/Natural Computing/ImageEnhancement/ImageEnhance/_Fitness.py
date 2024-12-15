import numpy as np
from skimage.metrics import peak_signal_noise_ratio, mean_squared_error


def fitness_function(original_image, enhanced_image):
    original_image = original_image.astype(np.uint8)
    enhanced_image = enhanced_image.astype(np.uint8)

    psnr = peak_signal_noise_ratio(original_image, enhanced_image)
    mse = mean_squared_error(original_image, enhanced_image)
    weights = [0.5, 0.5]

    ### SSIM isn't a valid condition here for fitness evaluation as it calculates the structural similarity, where here
    ### the structural similarity isn't changing at all as this is merely for enhancing an image, not changing it
    fitness_score = weights[0] * psnr + weights[1] * mse

    return fitness_score

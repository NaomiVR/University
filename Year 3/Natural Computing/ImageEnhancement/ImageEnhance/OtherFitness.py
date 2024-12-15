import numpy as np
import cv2

def calculate_entropy(img):
    hist, _ = np.histogramdd(img.flatten(), bins=256, density=True)
    hist = hist[hist > 0]
    entropy = -np.sum(hist * np.log2(hist))
    return entropy

def calculate_compactness(img):
    gray = cv2.cvtColor(img, cv2.COLOR_HSV2BGR)
    gray = cv2.cvtColor(gray, cv2.COLOR_BGR2GRAY)

    height, width = gray.shape
    avg_dist = 0
    for y in range(height):
        for x in range(width):
            for ny in range(height):
                for nx in range(width):
                    avg_dist += np.sqrt((x - nx) ** 2 + (y - ny) ** 2)
    avg_dist /= (height * width) ** 2

    diameter = np.sqrt(height ** 2 + width ** 2)
    compactness = avg_dist / diameter
    return compactness

def calculate_ioac(img):
    gray = cv2.cvtColor(img, cv2.COLOR_HSV2BGR)
    gray = cv2.cvtColor(gray, cv2.COLOR_BGR2GRAY)

    _, thresh = cv2.threshold(gray, 0, 255, cv2.THRESH_BINARY_INV + cv2.THRESH_OTSU)

    contours, _ = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    total_area = 0
    for cnt in contours:
        area = cv2.contourArea(cnt)
        if area > 100:
            total_area += area

    image_area = img.shape[0] * img.shape[1]
    ioac = total_area / image_area
    return ioac

def fitness_function_(original_image, enhanced_image):

    original_array = np.array(original_image)
    enhanced_array = np.array(enhanced_image)

    original_entropy = calculate_entropy(original_array)
    original_compactness = calculate_compactness(original_array)
    original_ioac = calculate_ioac(original_array)

    enhanced_entropy = calculate_entropy(enhanced_array)
    enhanced_compactness = calculate_compactness(enhanced_array)
    enhanced_ioac = calculate_ioac(enhanced_array)

    entropy_diff = abs(enhanced_entropy - original_entropy)
    compactness_diff = abs(enhanced_compactness - original_compactness)
    ioac_diff = abs(enhanced_ioac - original_ioac)

    weight_entropy_diff = 0.3
    weight_compactness_diff = 0.4
    weight_ioac_diff = 0.3

    weighted_diff = (weight_entropy_diff * entropy_diff) + (weight_compactness_diff * compactness_diff) + (weight_ioac_diff * ioac_diff)

    normalized_fitness = 1 - (weighted_diff / (weight_entropy_diff + weight_compactness_diff + weight_ioac_diff))

    return normalized_fitness

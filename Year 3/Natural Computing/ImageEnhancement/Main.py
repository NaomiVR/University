from ImageEnhance import ImageHandler


if __name__ == '__main__':
    ih = ImageHandler.ImageHandler('Images/test_image_2.jpg', 1)
    ih.read_image()
    ih.point_processing()

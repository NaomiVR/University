import numpy as np
import matplotlib.pyplot as plt


def timer(funcname: any, *args: any, **kwargs: any) -> tuple:
    """
    `timer` takes a function name and its arguments, runs the function, and returns the function's output, the size of the
    output, and the time it took to run the function.

    :param funcname: the function to be timed
    :type funcname: any
    :param : *args: the first argument
    :type : any
    :param : *kwargs: the second argument
    :type : any
    :return: the coordinates of the points, the size of the data, and the time taken to run the function.
    """
    import time

    start = time.perf_counter()
    coords, data_size = funcname(*args, **kwargs)
    end = time.perf_counter()
    time_taken = end-start

    return coords, data_size, time_taken


def double_line_graph(formula1: str, formula2: str, x_range: range, filename: str) -> tuple:
    """
    It takes in two formulas, a range of x values, and a filename, and it returns two lists of tuples, each of which
    contains the x and y values for each formula

    :param formula1: The formula for the first line
    :type formula1: str
    :param formula2: The formula for the second line
    :type formula2: str
    :param x_range: range
    :type x_range: range
    :param filename: The name of the file you want to save the graph as
    :type filename: str
    :return: A tuple of two lists of tuples.
    """
    plt.title(f"{filename}")
    x = np.array(x_range)
    f1_y = eval(formula1)
    plt.plot(x, f1_y)
    f2_y = eval(formula2)
    plt.plot(x, f2_y)
    plt.show()

    return list(zip(x, f1_y)), list(zip(x, f2_y))


def time_data_graph(time_taken: any, size_of_data: any) -> None:
    """
    It takes two lists as arguments and plots them against each other

    :param time_taken: A list of the time taken for each size of data
    :type time_taken: any
    :param size_of_data: The size of the data that you want to test
    :type size_of_data: any
    """

    plt.title("Time taken vs size of data")
    plt.xlabel("Size of data (Coordinates)")
    plt.ylabel("Time taken (Seconds)")
    plt.plot(size_of_data, time_taken)
    plt.legend(['Solution 1'], loc="upper left")
    plt.show()

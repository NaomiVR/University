from solution_utils import double_line_graph as dlg, timer as tm, time_data_graph as tdgraph
from solution_main import intersect_finder

plot_x = []
plot_y = []


def run_test(fil: str):
    """
    It takes in a file name, reads the first line of the file, and then runs the `dlg` and `tm` functions on the data
    from the file

    :param fil: str - the file to read from
    :type fil: str
    :return: a tuple of the intersecting coordinates, the number of coordinates, and the time taken to find the
    intersecting coordinates.
    """
    with open(fil, 'r') as f:
        data = f.readline().split(' ')
        line1, line2 = dlg(data[0], data[1], range(int(data[2]), int(data[3])), fil)
        results = tm(intersect_finder, line1, line2)

        plot_x.append(results[1])
        plot_y.append(results[2])

        return f'Intersecting coords: {results[0]}\nNum of coords: {len(results[0])}\nTime taken: {results[2]}'


# A list of files to run the `run_test` function on.
files = ['test_data/test1.txt', 'test_data/test2.txt', 'test_data/test3.txt',
         'test_data/test4.txt', 'test_data/test5.txt', 'test_data/test6.txt']

# Running the `run_test` function on each file in the `files` list and then printing the results to the
# console and writing the results to a file with the same name as the file it was run on but with a `.solution`
# extension.
for file in files:
    f_result = run_test(file)
    print(f"{file}\n{f_result}")
    with open(f'{file}.solution', 'a') as f:
        f.write(f_result)

# Plotting the time taken to find the intersecting coordinates against the number of coordinates.
tdgraph(sorted(plot_y), sorted(plot_x))

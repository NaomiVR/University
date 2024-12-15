def intersect_finder(coord_set_1: list, coord_set_2: list) -> tuple:
    """
    It takes two lists of coordinates, sorts them, and then iterates through them to find the intersection

    :param coord_set_1: list of tuples of coordinates
    :type coord_set_1: list
    :param coord_set_2: list of tuples of coordinates
    :type coord_set_2: list
    :return: A tuple of the intersecting coordinates and the total number of coordinates in both sets.
    """
    cache = []

    # It sorts the coordinates in ascending order.
    coord_set_1_sorted = sorted(coord_set_1)
    coord_set_2_sorted = sorted(coord_set_2)

    i, j = 0, 0
    # Iterating through the two lists of coordinates and comparing them.
    while i < len(coord_set_1_sorted) and j < len(coord_set_2_sorted):
        coord1 = coord_set_1_sorted[i]
        coord2 = coord_set_2_sorted[j]

        # Comparing the coordinates in the two lists and if they are the same, it adds them to the cache.
        if coord1[0] == coord2[0] and coord1[1] == coord2[1]:
            cache.append((coord1, coord2))
            i += 1
            j += 1
        elif coord1[0] < coord2[0]:
            i += 1
        else:
            j += 1

    return cache, len(coord_set_1_sorted)+len(coord_set_2_sorted)

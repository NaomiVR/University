import pandas as pd
from adjacency_list_graph import AdjacencyListGraph


def create_station_graph(data):
    # Function to create and return the station graph
    station_to_index = {station: idx for idx, station in enumerate(set(data['StartStation']).union(data['EndStation']))}
    graph = AdjacencyListGraph(card_V=len(station_to_index), directed=True, weighted=True)

    for row in data.itertuples():
        start_station = station_to_index[row.StartStation]
        end_station = station_to_index[row.EndStation]
        weight = 1  # You can replace this with the actual weight from your data if available

        if not graph.has_edge(start_station, end_station):
            graph.insert_edge(start_station, end_station, weight=weight)

    return graph


def is_feasible_closure(graph, start_station, end_station):
    # Function to check if closure is feasible and return the path
    visited = [False] * len(graph.adj_lists)
    queue = [(start_station, [start_station])]

    while queue:
        current_station, path = queue.pop(0)
        visited[current_station] = True

        if current_station == end_station:
            return path  # Return the path

        for edge in graph.get_adj_list(current_station):
            next_station = edge.get_v()
            if not visited[next_station]:
                new_path = path + [next_station]
                queue.append((next_station, new_path))

    return None


def get_station_index(station_name, station_to_index):
    # Function to get the station index from the station name
    return station_to_index.get(station_name)


def get_station_name(index, station_to_index):
    # Function to get the station name from the station index
    for station, idx in station_to_index.items():
        if idx == index:
            return station
    return None


def main():
    data = pd.read_excel('data/London Underground data.xlsx')
    graph = create_station_graph(data)

    # List the starting station and ending station without closure
    station_to_index = {station: idx for idx, station in
                        enumerate(set(data['StartStation']).union(data['EndStation']))}
    start_station_name = input("Enter the starting station: ")
    end_station_name = input("Enter the ending station: ")

    start_station_index = get_station_index(start_station_name, station_to_index)
    end_station_index = get_station_index(end_station_name, station_to_index)

    if start_station_index is None or end_station_index is None:
        print("Invalid station names. Exiting.")
        return

    path_without_closure = is_feasible_closure(graph, start_station_index, end_station_index)

    if path_without_closure:
        print("Route without closure is feasible.")
        print("Path:", " -> ".join([get_station_name(index, station_to_index) for index in path_without_closure]))
    else:
        print("Route without closure is not feasible. Please check your data for connectivity.")
        return

    # Allow the user to select one station to close
    station_to_close_name = input("Enter the station to close: ")
    station_to_close_index = get_station_index(station_to_close_name, station_to_index)

    if station_to_close_index is None:
        print("Invalid station name. Exiting.")
        return

    # Check if the route is still possible after closure
    path_with_closure = is_feasible_closure(graph, start_station_index, end_station_index)

    if path_with_closure:
        print(f"\nClosure at {station_to_close_name} is feasible.")
        print("Path:", " -> ".join([get_station_name(index, station_to_index) for index in path_with_closure]))

        # List affected routes
        affected_routes = [f"{get_station_name(path_with_closure[i], station_to_index)} -- {get_station_name(path_with_closure[i + 1], station_to_index)}"
                           for i in range(len(path_with_closure) - 1)]
        print("\nAffected Routes:")
        for route in affected_routes:
            print(route)
    else:
        print(f"\nClosure at {station_to_close_name} is not feasible.")
        print("Reason: Closure would disrupt the route between the starting and ending stations.")


if __name__ == '__main__':
    main()

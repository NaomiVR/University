try:
    from adjacency_list_graph import AdjacencyListGraph
    from dijkstra import dijkstra
    import pandas as pd
    import matplotlib.pyplot as plt
    import numpy as np
except ImportError as e:
    raise ImportError


class DataHandler:
    def __init__(self, doc_path, debug=False):
        self.doc_path = doc_path
        self.data = None
        self.station_to_index = None
        self.graph = None
        self.debug = debug

        self._reader()
        self._grapher()

    def _reader(self) -> None:
        self.data = pd.read_excel(self.doc_path)
        self.station_to_index = {station: idx for idx, station in
                                 enumerate(set(self.data['StartStation']).union(self.data['EndStation']))}

    def _grapher(self) -> None:
        self.graph = AdjacencyListGraph(card_V=len(self.data['StartStation'].unique()), directed=True, weighted=True)

        for row in self.data.itertuples():
            start_station = self.station_to_index[row.StartStation]
            end_station = self.station_to_index[row.EndStation]
            weight = row.Time

            if (start_station < 0 or start_station >= len(self.graph.adj_lists) or
                    end_station < 0 or end_station >= len(self.graph.adj_lists)):

                if self.debug is True:
                    print(f"Invalid vertex indices ({start_station}, {end_station}). Skipping.")
                continue

            if not self.graph.has_edge(start_station, end_station):
                self.graph.insert_edge(start_station, end_station, weight=weight)
                self.graph.insert_edge(end_station, start_station, weight=weight)
            elif self.graph.has_edge(start_station, end_station) and self.debug is True:
                print(f"Edge ({start_station}, {end_station}) already exists. Skipping.")

    def get_shortest_path(self, source, destination) -> (list, float):
        """
        Find the shortest path from a source vertex to a destination vertex in a weighted graph using
        Dijkstra's algorithm.

        Dijkstra calculates both the distances from the source to all other vertices and the predecessors for each
        vertex in the shortest path. The function then constructs the actual path by iteratively backtracking from the
        destination to the source, inserting each vertex at the beginning of the path list to maintain the correct
        order.

        :param source: The starting vertex for the shortest path.
        :param destination: The destination vertex for the shortest path.

        :return list: The vertices in the shortest path from the source to the destination.
        :return float: The total distance of the shortest path.
        """
        distances, predecessors = dijkstra(self.graph, source)

        path = []
        current_vertex = destination
        while current_vertex is not None:
            path.insert(0, current_vertex)
            current_vertex = predecessors[current_vertex]

        return path, distances[destination]

    def hist_plotter(self) -> None:
        """
        This iterates over every single possible journey a person can take on the tube, works out the journey duration
        and plots a histogram based on a list of values that is appended for each journey

        :return: None
        """
        durations = []

        for source_vertex in range(len(self.data) - 1):
            for destination_vertex in range(len(self.data) - 1):
                if source_vertex != destination_vertex:
                    try:
                        _, total_duration = self.get_shortest_path(source_vertex, destination_vertex)
                        if not np.isinf(total_duration) and not np.isnan(total_duration):
                            durations.append(total_duration)
                    except IndexError as e:
                        if self.debug is True:
                            print(f"Error for source_vertex={source_vertex}, "
                                  f"destination_vertex={destination_vertex}\nError: {e}")

        plt.title('Duration of all journeys in the tube')
        plt.xlabel('Total Duration (minutes)')
        plt.ylabel('Frequency')
        plt.hist(bins=range(0, int(max(durations))), x=durations)
        plt.show()

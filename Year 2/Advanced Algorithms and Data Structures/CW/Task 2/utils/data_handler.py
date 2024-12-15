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

    def get_station_count(self, source, destination) -> int:
        """
        Find the number of stations between a source and destination in a weighted graph using Dijkstra's algorithm.

        :param source: The starting vertex.
        :param destination: The destination vertex.

        :return: The count of stations between source and destination.
        """
        _, predecessors = dijkstra(self.graph, source)

        current_vertex = destination
        station_count = 0

        while current_vertex is not None:
            station_count += 1
            current_vertex = predecessors[current_vertex]

        return station_count - 1  # Subtract 1 to exclude the destination itself

    def hist_plotter(self) -> None:
        """
        This iterates over every single possible jurney a person can take on the tube, works out the journey duration
        and plots a histogram based on a list of values that is appended for each journey

        :return: None
        """
        durations = []

        for source_vertex in range(len(self.data) - 1):
            for destination_vertex in range(len(self.data) - 1):
                if source_vertex != destination_vertex:
                    try:
                        if (0 <= source_vertex < len(self.graph.adj_lists) and
                                0 <= destination_vertex < len(self.graph.adj_lists)):
                            count = self.get_station_count(source_vertex, destination_vertex)
                            durations.append(count)
                            print(f"Succes for source_vertex={source_vertex}, "
                                  f"destination_vertex={destination_vertex}")
                    except IndexError as e:
                        if self.debug is True:
                            print(f"Error for source_vertex={source_vertex}, "
                                  f"destination_vertex={destination_vertex}\nError: {e}")

        plt.title('Count of stations for all journeys in the tube')
        plt.xlabel('Stops (Stations)')
        plt.ylabel('Frequency')
        plt.hist(bins=range(0, int(max(durations))), x=durations)
        plt.show()

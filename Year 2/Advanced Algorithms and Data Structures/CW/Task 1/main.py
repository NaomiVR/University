from utils.data_handler import DataHandler


def main(debug):
    running = True
    data_handler = DataHandler(doc_path='data/London Underground data.xlsx', debug=debug)

    hist_choice = input("Do you want a histogram to be produced? (Y/N): ")
    if hist_choice == 'Y':
        data_handler.hist_plotter()
    else:
        pass

    # Start of user interaction
    while running:
        source_station_name = input("Enter the initial station: ")
        destination_station_name = input("Enter the final destination station: ")

        if (source_station_name not in data_handler.station_to_index or
                destination_station_name not in data_handler.station_to_index):
            print("Invalid station names. Exiting.")
            return

        source_vertex = data_handler.station_to_index[source_station_name]
        destination_vertex = data_handler.station_to_index[destination_station_name]

        path, total_duration = data_handler.get_shortest_path(source_vertex, destination_vertex)

        journey = []
        for vertex in path:
            station_name = next(key for key, value in data_handler.station_to_index.items() if value == vertex)
            journey.append(station_name)

        print(f"Journey from {journey[0]} to {journey[-1]}: {journey}")
        print(f"Total duration of the journey: {total_duration} minutes")

        loop_choice = input("Do you want to look at another journey? (Y/N): ")
        if loop_choice == 'Y':
            continue
        elif loop_choice == 'N':
            running = False


if __name__ == '__main__':
    dev = input("Enable debug? (Y/N): ")

    if dev == 'Y':
        main(debug=True)
    elif dev == 'N':
        main(debug=False)

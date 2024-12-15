from utils.data_handler import DataHandler


def main(debug):
    running = True
    data_handler = DataHandler(doc_path='data/London Underground data.xlsx', debug=debug)

    hist_choice = input("Do you want a histogram to be produced? (Y/N): ")
    if hist_choice == 'Y':
        data_handler.hist_plotter()

    while running:
        source_station_name = input("Enter the initial station: ")
        destination_station_name = input("Enter the final destination station: ")
    
        source_vertex = data_handler.station_to_index.get(source_station_name)
        destination_vertex = data_handler.station_to_index.get(destination_station_name)
    
        if source_vertex is None or destination_vertex is None:
            print("Invalid station names. Exiting.")
            return
    
        station_count = data_handler.get_station_count(source=source_vertex, destination=destination_vertex)
    
        if station_count == -1:
            print(f"No path found between {source_station_name} and {destination_station_name}")
        else:
            print(f"Number of stations between {source_station_name} and {destination_station_name}: {station_count}")

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

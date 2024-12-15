from utils.data_handler import DataHandler


def main(debug):
    running = True
    data_handler = DataHandler(doc_path="data/London Underground data.xlsx", debug=debug)

    hist_choice = input("Do you want a histogram to be produced? (Y/N): ")
    if hist_choice == 'Y':
        data_handler.hist_plotter()

    while running:
        source_station_name = input("Enter the initial station: ")
        destination_station_name = input("Enter the final destination station: ")

        if (source_station_name not in data_handler.station_to_index or
                destination_station_name not in data_handler.station_to_index):
            print("Invalid station names. Exiting.")
            return

        source_station_index = data_handler.station_to_index[source_station_name]
        destination_station_index = data_handler.station_to_index[destination_station_name]

        station_count = data_handler.get_station_count(source_station_index, destination_station_index)

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

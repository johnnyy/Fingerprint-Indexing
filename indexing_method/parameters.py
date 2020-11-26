from os import environ


def config():
    environ['FILE_INDEX_PATH'] = "/home/johnny/Downloads/TCC2/data-fingerprint/2002_DB1a_data/finger_index.txt"
    environ['FILE_SEARCH_PATH'] = "/home/johnny/Downloads/TCC2/data-fingerprint/2002_DB1a_data/finger_search.txt"
    environ['FILE_QUALITY_PATH'] = "/home/johnny/Downloads/TCC2/data-fingerprint/2002_DB1a_data/quality.csv"

    environ['INDEX_VECTOR_FOLDER_PATH'] = "/home/johnny/Downloads/TCC2/data-fingerprint/2002_DB1a_data/Vector_Index/"
    environ['SEARCH_VECTOR_FOLDER_PATH'] = "/home/johnny/Downloads/TCC2/data-fingerprint/2002_DB1a_data/Vector_Search/"
    environ['MCC_GENERATE_VECTOR'] = "./generate_mcc/generate_vector_python"
    environ['FOLDER_CSV_OUTPUT'] = "/home/johnny/Downloads/TCC2/out/out-csv/"


listNS = [18, 16, 12]
listND = [5, 5, 7]
list_quality_index = [100, 50, 25]
list_quality_search = [10, 25, 50, 100]

list_bits = [8, 12, 16]


class parameters:
    def __init__(self):
        self.listNS = listNS
        self.listND = listND
        self.list_quality_index = list_quality_index
        self.list_quality_search = list_quality_search
        self.list_bits = list_bits

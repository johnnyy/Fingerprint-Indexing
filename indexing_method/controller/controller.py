from os import system, environ
import multiprocessing
from service.es_service import Elasticsearch_service
from service.indexing_search import indexing, search


def __generate_vector_search__(ns, nd, quality):
    system(environ.get('MCC_GENERATE_VECTOR') + " " + environ.get('FILE_SEARCH_PATH') + " " + environ.get(
        'SEARCH_VECTOR_FOLDER_PATH') + " {} {} {}".format(ns, nd, quality))


def __generate_vector_index__(ns, nd, quality):
    system(environ.get('MCC_GENERATE_VECTOR') + " " + environ.get('FILE_INDEX_PATH') + " " + environ.get(
        'INDEX_VECTOR_FOLDER_PATH') + " {} {} {}".format(ns, nd, quality))


class Controller:

    def exec(self, params):
        es_service = Elasticsearch_service()
        pool_index = multiprocessing.Pool()
        for ns, nd in zip(params.listNS, params.listND):
            for quality_i in params.list_quality_index:
                print("Gerando dados do indice")
                __generate_vector_index__(ns, nd, quality_i)
                for bits in params.list_bits:
                    indexing(bits, es_service, pool_index)

                    for quality_s in params.list_quality_search:
                        print("Gerando dados da busca")

                        __generate_vector_search__(ns, nd, quality_s)
                        pool = multiprocessing.Pool()
                        search(bits, ns, nd, quality_s, quality_i, es_service, pool)

                    es_service.delete_index()

from elasticsearch import Elasticsearch, helpers
import multiprocessing
from service.requests_format import create_request_minutia, request_create_index, request_msearch


class Elasticsearch_service:

    def __init__(self, ip="localhost", timeout=1000, index_name='finger'):
        self.ip = ip
        self.es = Elasticsearch(hosts=ip)
        self.timeout = timeout
        self.index_name = index_name

    def create_index(self):
        request_body = request_create_index()
        try:
            ret = self.es.indices.create(index=self.index_name, body=request_body, request_timeout=self.timeout)
        except:
            return False
        return ret['acknowledged']

    def indexing(self, list_json_text):
        pool_index = multiprocessing.Pool()
        request_body = pool_index.map(create_request_minutia, list_json_text)
        try:

            res = helpers.bulk(self.es, request_body, request_timeout=self.timeout)
        except:
            return False
        return True

    def delete_index(self):
        self.es.indices.delete(index=self.index_name)

    def search(self, list_text):
        request_body = request_msearch(list_text)
        try:
            text_return = self.es.msearch(body=request_body, request_timeout=self.timeout)
            return text_return
        except:
            return False

def request_create_index():
    return {
        "settings": {
            "number_of_shards": 1,
            "number_of_replicas": 1,

            "similarity": {
                "scripted_tfidf": {
                    "type": "scripted",
                    "script": {
                        "source": "double t_idf = Math.ceil(Math.log((field.docCount+1.0)/(term.docFreq+1.0))); return doc.freq*t_idf;"
                    }
                }
            }
        },
        "mappings": {
            "properties": {
                "minutia": {"type": "nested",
                            "properties": {
                                "text": {"type": "text", "similarity": "scripted_tfidf"},
                                "min_id": {"type": "text"}
                            }},
                "id": {"type": "text"},
            }

        }
    }


def create_request_minutia(json_text):
    return {"_op_type": "create",
            "_index": "finger",
            "_source": {
                "id": json_text['id'],
                "minutia": [{"min_id": i, "text": text} for i, text in enumerate(json_text['minutia'])]
            }
            }


def request_msearch(list_text):
    for text in list_text:
        yield {"index": "finger"}
        yield {"_source": ["id"], "from": 0, "size": 100,
               "query": {
                   "nested": {
                       "path": "minutia",
                       "query": {
                           "bool": {
                               "should": [
                                   {"match": {"minutia.text": text}},

                               ]
                           }
                       },
                       "score_mode": "max"
                   }
               }
               }

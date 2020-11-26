import pandas as pd

def rerank(json_response):
    list_json_scores = []
    for request in json_response['responses']:
        max_score = int(request['hits']['max_score'])
        for element in request['hits']['hits']:
            score = int(element['_score'])
            if score == max_score:
                list_json_scores.append({'id': element['_source']['id'], 'score': score})

    df = pd.DataFrame(list_json_scores)
    return df.groupby('id', as_index=False).sum().sort_values('score', ascending=False).reset_index(drop=True)
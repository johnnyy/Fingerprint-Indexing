import pandas as pd
def rerank(json_response):
    list_json_scores = []
    for request in json_response['responses']:
        max_score = int(request['hits']['max_score'])
        for element in request['hits']['hits']:
            score = int(element['_score'])
            if score == max_score:
                list_json_scores.append({'id': element['_source']['id'], 'score': score})
            else:
                break
    df = pd.DataFrame(list_json_scores)
    return df.groupby('id', as_index=False).sum().sort_values('score', ascending=False).reset_index(drop=True)



def realize_rerank(df_response):
    list_json_scores = []
    max_score = int(df_response['hits']['max_score'])
    for element in df_response['hits']['hits']:
        score = int(element['_score'])
        if score == max_score:
            list_json_scores.append({'id': element['_source']['id'], 'score': score})
        else:
            break
    return list_json_scores

def rerank_erro(json_response):
    import pdb;
    pdb.set_trace()
    df_response = pd.DataFrame(json_response['responses'])
    list_score = df_response.apply(realize_rerank, axis=1)
    print(list_score.explode())
    df = pd.DataFrame(list_score.explode().reset_index(drop=True).values)
    print(df)
    return df.groupby('id', as_index=False).sum().sort_values('score', ascending=False).reset_index(drop=True)

from os import environ, walk
from service.gen_term import generate_term
from service.rerank import rerank
import datetime
import pandas as pd


def indexing(bits, es_service, pool_index):
    es_service.create_index()
    generate_t = generate_term(bits)
    list_json_id = []
    # Percorrer arquivos de indice
    print("Indexando")
    for x, i, files in walk(environ.get('INDEX_VECTOR_FOLDER_PATH')):
        for ind, file in enumerate(files):
            file_op = open(x + file)
            vector_data = file_op.readlines()
            file_op.close()
            list_text_min = pool_index.map(generate_t.create_terms,
                                           vector_data)
            id = int(file.split('_')[0])
            #print(ind + 1, file)

            list_json_id.append({"id": id, "minutia": list_text_min})

            if ind % 50 == 0 and ind != 0:
                es_service.indexing(list_json_id)
                list_json_id.clear()

        if len(list_json_id) > 0:
            es_service.indexing(list_json_id)
            list_json_id.clear()


def search(bits, ns, nd, quality_s,quality_i, es_service, pool_search):
    generate_t = generate_term(bits)

    pos_rank = []
    for x, i, files in walk(environ.get("SEARCH_VECTOR_FOLDER_PATH")):
        count = 0
        for file in files:

            if True:  # count >= 618):

                file_op = open(x + file)
                vector_data = file_op.readlines()
                file_op.close()
                id = int(file.split("_")[0])
                pos_ = -1
                time1 = datetime.datetime.now()
                list_text_min = pool_search.map(generate_t.create_terms,
                                                vector_data)
                data_response = es_service.search(list_text_min)
                if data_response != False:

                    df_ranking = rerank(data_response)
                    time2 = datetime.datetime.now()

                    for p in range(df_ranking.shape[0]):
                       # print(id,df_ranking['id'][p])
                        if id == df_ranking['id'][p]:
                            pos_ = p + 1
                            break
                else:
                    time2 = datetime.datetime.now()

                print("count:", count, "filename:", file, "pos_rank:", pos_, "time:", time2 - time1)
                pos_rank.append([pos_, file, time2 - time1])

            count += 1
    df = pd.DataFrame(pos_rank, columns=['pos_rank', 'file', 'time'])
    df.to_csv('{}result_query{}_{}_{}_{}.csv'.format(environ.get('FOLDER_CSV_OUTPUT'), ns*ns*(nd+1), quality_s, quality_i, bits), index=False)


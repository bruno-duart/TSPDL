# -*- coding: utf-8 -*-
"""
Created on Thu Dec 14 19:34:33 2023

@author: Bruno Duarte
"""

# import os
# import csv
# import statistics

# # Função para calcular estatísticas
# def calcular_estatisticas(data):
#     media = statistics.mean(data)
#     menor_valor = min(data)
#     desvio_padrao = statistics.stdev(data)
#     erro_med = statistics.StatisticsError()
#     return media, menor_valor, desvio_padrao

# # Pasta contendo os arquivos .csv
# pasta = 'results_end/'

# # Lista para armazenar os resultados
# resultados = []

# # Iterar sobre os arquivos na pasta
# for arquivo in os.listdir(pasta):
#     if arquivo.endswith('.csv'):
#         caminho_arquivo = os.path.join(pasta, arquivo)

#         # Leitura do arquivo .csv
#         with open(caminho_arquivo, 'r') as file:
#             reader = csv.DictReader(file)
#             best_ts = []
#             best_ini = []
#             time_ts = []

#             # Iterar sobre as linhas do arquivo
#             for row in reader:
#                 best_ts.append(float(row['best_ts']))
#                 best_ini.append(float(row['best_ini']))
#                 time_ts.append(float(row['time_ts']))

#             # Calcular estatísticas
#             mean_best_ts, low_best_ts, std_best_ts = calcular_estatisticas(best_ts)
#             mean_best_ini, low_best_ini, std_best_ini = calcular_estatisticas(best_ini)
#             media_time_ts, menor_time_ts, std_time_ts = calcular_estatisticas(time_ts)

#             # Adicionar resultados à lista
#             resultados.append({
#                 'nome_arquivo': arquivo,
#                 'média_best_ts': mean_best_ts,
#                 'média_best_ini': mean_best_ini,
#                 'média_ts': media_time_ts,
#                 'low_best_ts': low_best_ts,
#                 'low_best_ini': low_best_ini,
#                 'low_ts': menor_time_ts,
#                 'std_best_ts': std_best_ts,
#                 'std_best_ini': std_best_ini,
#                 'std_time_ts': std_time_ts
#             })

# # Escrever os resultados em um novo arquivo .csv
# output_file = pasta+'aggregated_results.csv'
# header = ['nome_arquivo', 'média_best_ts', 'média_best_ini', 'média_ts',
#           'low_best_ts', 'low_best_ini', 'low_ts',
#           'std_best_ts', 'std_best_ini', 'std_time_ts']

# with open(output_file, 'w', newline='') as out_file:
#     writer = csv.DictWriter(out_file, fieldnames=header)
#     writer.writeheader()
#     writer.writerows(resultados)

# print(f"Resultados salvos em {output_file}")


#%%
import os
import csv
import numpy as np

# Função para calcular o erro relativo
def erro_relativo(media, valor):
    return abs((media - valor) / valor) * 100

# Pasta contendo os arquivos CSV
pasta = 'results_end/'

# Lista para armazenar os resultados
resultados = []

# Loop através dos arquivos na pasta
for filename in os.listdir(pasta):
    if filename.endswith('.csv'):
        with open(os.path.join(pasta, filename), 'r') as file:
            # Lendo o arquivo CSV
            reader = csv.DictReader(file)
            
            # Listas para armazenar valores de cada coluna
            best_ts = []
            best_ini = []
            time_ts = []
            opt_val = []

            # Iterando sobre as linhas do arquivo
            for row in reader:
                best_ts.append(float(row['best_ts']))
                best_ini.append(float(row['best_ini']))
                time_ts.append(float(row['time_ts']))
                opt_val.append(float(row['opt_val']))

            # Calculando estatísticas
            mean_best_ts = np.mean(best_ts)
            mean_best_ini = np.mean(best_ini)
            mean_ts = np.mean(time_ts)

            low_best_ts = np.min(best_ts)
            low_best_ini = np.min(best_ini)
            low_ts = np.min(time_ts)

            std_best_ts = np.std(best_ts)
            std_best_ini = np.std(best_ini)
            std_time_ts = np.std(time_ts)

            mean_err_best_ts = erro_relativo(mean_best_ts, np.mean(opt_val))
            mean_err_best_ini = erro_relativo(mean_best_ini, np.mean(opt_val))
            low_err_best_ts = erro_relativo(low_best_ts, np.mean(opt_val))
            low_err_best_ini = erro_relativo(low_best_ini, np.mean(opt_val))

            # Adicionando resultados à lista
            resultados.append({
                'filename': filename.replace(".csv",""),
                'mean_best_ts': mean_best_ts,
                'mean_best_ini': mean_best_ini,
                'mean_ts': round(mean_ts,5),
                'low_best_ts': low_best_ts,
                'low_best_ini': low_best_ini,
                'opt_val': np.mean(opt_val),
                #'low_ts': low_ts,
                'std_best_ts': round(std_best_ts,5),
                'std_best_ini': std_best_ini,
                'std_time_ts': round(std_time_ts,5),
                'mean_err_best_ts': round(mean_err_best_ts,5),
                'mean_err_best_ini': round(mean_err_best_ini,5),
                'low_err_best_ts': round(low_err_best_ts,5),
                'low_err_best_ini': round(low_err_best_ini,5),
            })

# Escrevendo resultados em um novo arquivo CSV
cabecalho = [
    'filename', 'mean_best_ts', 'mean_best_ini', 'mean_ts',
    'low_best_ts', 'low_best_ini', 'opt_val', #'low_ts',
    'std_best_ts', 'std_best_ini', 'std_time_ts',
    'mean_err_best_ts', 'mean_err_best_ini', 'low_err_best_ts', 'low_err_best_ini'
]
output_file = pasta+'aggregated_results.csv'
with open(output_file, 'w', newline='') as file:
    writer = csv.DictWriter(file, fieldnames=cabecalho)
    writer.writeheader()
    writer.writerows(resultados)

print("Processo concluído. Resultados salvos em 'resultados.csv'.")


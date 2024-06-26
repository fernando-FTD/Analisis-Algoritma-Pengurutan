import pandas as pd
import matplotlib.pyplot as plt

# Membaca data dari CSV
df = pd.read_csv('sorting_results.csv')

def plot_data(df, data_type):
    data = df[df['Type'] == data_type]
    plt.figure(figsize=(10, 6))
    plt.plot(data['Size'], data['BubbleSort'], label='Bubble Sort')
    plt.plot(data['Size'], data['InsertionSort'], label='Insertion Sort')
    plt.plot(data['Size'], data['SelectionSort'], label='Selection Sort')
    plt.plot(data['Size'], data['MergeSort'], label='Merge Sort')
    plt.plot(data['Size'], data['QuickSort'], label='Quick Sort')
    plt.xlabel('Array Size')
    plt.ylabel('Time dalam mikrodetik')
    plt.title(f'{data_type} Data')
    plt.legend()
    plt.xlim(0, 10000)
    plt.ylim(0, 700000)
    plt.grid(True)
    plt.show()

plot_data(df, 'Random')
plot_data(df, 'Reverse')
plot_data(df, 'Sorted')

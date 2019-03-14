import matplotlib.pyplot as plt
import pandas as pd

X = pd.read_csv("saida.txt", header=-1, sep='\t')
plt.plot(X[0][10000:], X[1][10000:])
plt.show()

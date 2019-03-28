import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

X = pd.read_csv("saida.txt", header=-1, sep='\t')
#plt.plot(X[0][10000:], X[1][10000:])

plt.subplot(2,1,1)
plt.plot(X[0], X[1])
max_val = np.array(X)[-1, 0]
plt.xlim(0, max_val)

T = np.array(pd.read_csv("fire.txt", sep='\t', header=-1)[:][1:])
X = T.T[0]
T = T[:, 1:]
plt.subplot(2,1,2)
for i in range(len(T)-1):
    for j in range(0, len(T.T)):
        if T[i][j] > 0.5:
            plt.plot([X[i], X[i]], [j+0.25, j+0.75], color='black')
plt.ylim(0, len(T.T))
plt.xlim(0, max_val)
plt.show()

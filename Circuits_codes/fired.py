import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

T = pd.read_csv("fire.txt", sep='\t', header=-1)
T = np.array(T[:][1:])
#print(T)

X = T.T[0]
#print(X)

T = T[:, 1:]
#print(T)

for i in range(len(T)-1):
    for j in range(0, len(T.T)):
        if T[i][j] > 0.5:
            plt.plot([X[i], X[i]], [j+0.25, j+0.75], color='black')
plt.ylim(0, len(T.T))
plt.show()

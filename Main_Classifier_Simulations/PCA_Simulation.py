import numpy as np
from matplotlib.mlab import PCA

data = np.array(np.random.randint(100,size=(6 * 50,1)))
results = PCA(data, True)

print("RAW DATA:")
print(data)

print("Variance percentage for each component:")
print(results.fracs)

print("Projected Data:")
print(results.Y)

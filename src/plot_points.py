import matplotlib.pyplot as plt
import pandas as pd

# -------- CASE 1 --------
df1 = pd.read_csv("points_result_case1.csv")
poly1 = [(1.0, 1.0), (5.0, 1.0), (6.0, 4.0), (3.0, 6.0), (1.0, 4.0), (1.0, 1.0)]

# -------- CASE 2 --------
df2 = pd.read_csv("points_result_case2.csv")
poly2 = [(2.0, 2.0), (3.5, 2.0), (3.5, 3.5), (2.0, 3.5), (2.0, 2.0)]
poly3 = [(4.0, 4.0), (5.5, 4.0), (5.0, 5.5), (4.0, 5.0), (4.0, 4.0)]
poly4 = [(1.5, 5.5), (2.5, 5.5), (2.0, 6.5), (1.5, 5.5)]

# -------- figure --------
fig, axes = plt.subplots(1, 2, figsize=(14, 6))

# Case 1
inside1 = df1[df1['result'] == 1]
outside1 = df1[df1['result'] == 0]
axes[0].scatter(outside1['x'], outside1['y'], c='blue', marker='o', label='Outside')
axes[0].scatter(inside1['x'], inside1['y'], c='red', marker='*', label='Inside')
px1, py1 = zip(*poly1)
axes[0].plot(px1, py1, 'k-', linewidth=2)
axes[0].set_title("Case 1: Single Polygon")
axes[0].legend()
axes[0].axis("equal")
axes[0].grid(True)

# Case 2
inside2 = df2[df2['result'] == 1]
outside2 = df2[df2['result'] == 0]
axes[1].scatter(outside2['x'], outside2['y'], c='blue', marker='o', label='Outside')
axes[1].scatter(inside2['x'], inside2['y'], c='red', marker='*', label='Inside')

for poly in [poly2, poly3, poly4]:
    px, py = zip(*poly)
    axes[1].plot(px, py, 'k-', linewidth=2)

axes[1].set_title("Case 2: Three Polygons")
axes[1].legend()
axes[1].axis("equal")
axes[1].grid(True)

plt.tight_layout()
plt.show()

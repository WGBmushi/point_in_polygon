import matplotlib.pyplot as plt
import pandas as pd

polygon = [
    (1.0, 1.0),
    (5.0, 1.0),
    (6.0, 4.0),
    (3.0, 6.0),
    (1.0, 4.0)
]
polygon.append(polygon[0])  

df = pd.read_csv("points_result.csv")

inside_points = df[df['result'] == 1]
outside_points = df[df['result'] == 0]

plt.figure(figsize=(8, 8))

px, py = zip(*polygon)
plt.plot(px, py, 'k-', linewidth=2, label="Polygon")

plt.scatter(outside_points['x'], outside_points['y'], c='blue', marker='o', label='Outside')
plt.scatter(inside_points['x'], inside_points['y'], c='red', marker='*', label='Inside/Boundary')
plt.axis("equal")
plt.grid(True)
plt.title("Point-in-Polygon Test")
plt.legend()
plt.xlabel("X")
plt.ylabel("Y")
plt.tight_layout()
plt.show()

import matplotlib.pyplot as plt
import pandas as pd

# 定义多边形顶点
polygon = [
    (1.0, 1.0),
    (5.0, 1.0),
    (6.0, 4.0),
    (3.0, 6.0),
    (1.0, 4.0)
]
polygon.append(polygon[0])  # 闭合多边形

# 读取 CSV 文件
df = pd.read_csv("points_result.csv")

# 拆分点集
inside_points = df[df['result'] == 1]
outside_points = df[df['result'] == 0]

# 开始绘图
plt.figure(figsize=(8, 8))

# 绘制多边形边界
px, py = zip(*polygon)
plt.plot(px, py, 'k-', linewidth=2, label="Polygon")

# 绘制点
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

# point_in_polygon
This is a lightweight algorithm for quickly detecting whether a point is inside a polygon, primarily based on 'bounding box filtering' and the 'ray-casting method'.

## Build and Run
```bash
mkdir build && cd build
cmake ..
make
./demo
```

## Visualization
```python
python3 ../src/plot_points.py
```

## Result
![point-in-polygon test result](/result/Figure_1.png)

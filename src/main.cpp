#include <iostream>
#include <vector>
#include <utility>
#include <cstdlib> 
#include <ctime>   
#include <iomanip> 
#include <cmath>
#include <fstream>
#include <chrono>

bool point_in_polygon(
    double x, double y,
    const std::vector<std::pair<double, double>> &poly)
{
    size_t n = poly.size();
    if (n < 3)
        return false;

    double minx = poly[0].first, maxx = poly[0].first;
    double miny = poly[0].second, maxy = poly[0].second;
    for (size_t i = 1; i < n; ++i)
    {
        minx = std::min(minx, poly[i].first);
        maxx = std::max(maxx, poly[i].first);
        miny = std::min(miny, poly[i].second);
        maxy = std::max(maxy, poly[i].second);
    }
    if (x < minx || x > maxx || y < miny || y > maxy)
    {
        return false;
    }

    bool inside = false;
    const double eps = 1e-9;
    size_t j = n - 1;
    for (size_t i = 0; i < n; j = i++)
    {
        double xi = poly[i].first, yi = poly[i].second;
        double xj = poly[j].first, yj = poly[j].second;
        double dx = xj - xi, dy = yj - yi;
        double cross = (x - xi) * dy - (y - yi) * dx;
        if (std::fabs(cross) < eps)
        {
            double dot = (x - xi) * (x - xj) + (y - yi) * (y - yj);
            if (dot <= eps)
                return true;
        }
        bool intersect = ((yi > y) != (yj > y)) && (x < xi + dx * (y - yi) / (yj - yi));
        if (intersect)
        {
            inside = !inside;
        }
    }
    return inside;
}

int main()
{
    std::vector<std::pair<double, double>> polygon = {
        {1.0, 1.0}, {5.0, 1.0}, {6.0, 4.0}, {3.0, 6.0}, {1.0, 4.0}};

    double x_min = 0.0, x_max = 7.0;
    double y_min = 0.0, y_max = 7.0;

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    const int NUM_POINTS = 300;
    std::cout << "Randomly sampled " << NUM_POINTS << " points :\n ";
    std::cout << std::fixed << std::setprecision(2);

    std::ofstream fout("points_result.csv");
    fout << "x,y,result\n";

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < NUM_POINTS; ++i)
    {
        double x = x_min + (x_max - x_min) * (std::rand() / double(RAND_MAX));
        double y = y_min + (y_max - y_min) * (std::rand() / double(RAND_MAX));
        bool inside = point_in_polygon(x, y, polygon);
        std::cout << (inside ? '*' : 'o') << "  "
                  << "Point(" << std::setw(5) << x << ", " << std::setw(5) << y << ")"
                  << " => " << (inside ? "Inside/Boundary" : "Outside") << '\n';
        fout << x << "," << y << "," << (inside ? 1 : 0) << "\n";
    }

    fout.close();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "\nTested " << NUM_POINTS << " points in "
              << elapsed.count() * 1000 << " ms.\n";
    std::cout << "Results written to points_result.csv\n";

    return 0;
}

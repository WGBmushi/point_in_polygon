#include <iostream>
#include <vector>
#include <utility>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <chrono>

bool point_in_polygon(double x, double y, const std::vector<std::pair<double, double>> &poly)
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
        return false;

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
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Case 1
    std::vector<std::pair<double, double>> poly1 = {
        {1.0, 1.0}, {5.0, 1.0}, {6.0, 4.0}, {3.0, 6.0}, {1.0, 4.0}};

    // Case 2
    std::vector<std::pair<double, double>> poly2 = {
        {2.0, 2.0}, {3.5, 2.0}, {3.5, 3.5}, {2.0, 3.5}};
    std::vector<std::pair<double, double>> poly3 = {
        {4.0, 4.0}, {5.5, 4.0}, {5.0, 5.5}, {4.0, 5.0}};
    std::vector<std::pair<double, double>> poly4 = {
        {1.5, 5.5}, {2.5, 5.5}, {2.0, 6.5}};

    double x_min = 0.0, x_max = 7.0;
    double y_min = 0.0, y_max = 7.0;
    const int NUM_POINTS = 500;

    // Case 1
    std::ofstream fout1("points_result_case1.csv");
    fout1 << "x,y,result\n";

    auto start1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < NUM_POINTS; ++i)
    {
        double x = x_min + (x_max - x_min) * (std::rand() / double(RAND_MAX));
        double y = y_min + (y_max - y_min) * (std::rand() / double(RAND_MAX));
        bool inside = point_in_polygon(x, y, poly1);
        fout1 << x << "," << y << "," << (inside ? 1 : 0) << "\n";
    }
    fout1.close();
    auto end1 = std::chrono::high_resolution_clock::now();
    std::cout << "Case 1 finished in "
              << std::chrono::duration<double, std::milli>(end1 - start1).count() << " ms\n";

    // Case 2
    std::ofstream fout2("points_result_case2.csv");
    fout2 << "x,y,result\n";

    auto start2 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < NUM_POINTS; ++i)
    {
        double x = x_min + (x_max - x_min) * (std::rand() / double(RAND_MAX));
        double y = y_min + (y_max - y_min) * (std::rand() / double(RAND_MAX));

        bool inside = point_in_polygon(x, y, poly2) ||
                      point_in_polygon(x, y, poly3) ||
                      point_in_polygon(x, y, poly4);

        fout2 << x << "," << y << "," << (inside ? 1 : 0) << "\n";
    }
    fout2.close();
    auto end2 = std::chrono::high_resolution_clock::now();
    std::cout << "Case 2 finished in "
              << std::chrono::duration<double, std::milli>(end2 - start2).count() << " ms\n";

    std::cout << "Results written to points_result_case1.csv and case2.csv\n";

    return 0;
}

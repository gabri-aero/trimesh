#include <Delaunay.hpp>

int main() {
    Coord2D p1{0., 0.};
    Coord2D p2{-3., -1.};
    Coord2D p3{4., 3.};
    Coord2D p4{1., 4.};

    std::vector<Coord2D> points{p1, p2, p3, p4};

    Delaunay d{points};

    std::vector<Node> n{d.super_triangle()};

    return 0;
}
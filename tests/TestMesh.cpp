#include <gtest/gtest.h>

#include <Mesh.cpp>
#include <PlotUtils.hpp>


TEST(MeshTest, BoundaryGeneration) {
    Plot::close_gnuplot();

    double Lx{10};
    double Ly{5};
    double h{0.5};
    auto wall1 = Boundary::line(Coord2D{-Lx/2, -Ly/2}, Coord2D{Lx/2, -Ly/2}, h);
    auto wall2 = Boundary::line(Coord2D{-Lx/2, Ly/2}, Coord2D{Lx/2, Ly/2}, h);
    auto inlet = Boundary::line(Coord2D{-Lx/2, -Ly/2}, Coord2D{-Lx/2, Ly/2}, h);
    auto outlet = Boundary::line(Coord2D{Lx/2, -Ly/2}, Coord2D{Lx/2, Ly/2}, h);
    auto cylinder = Boundary::circle(Coord2D{0, 0}, 1, 0.2);

    auto b = Boundary::combine(inlet, wall1, outlet, wall2, cylinder);
    //Plot::plot_mesh(b.get_edges());

    Mesh msh{b, h};
    Delaunay d = msh.get_triangulation();
    Plot::plot_mesh(d.get_edges());
}
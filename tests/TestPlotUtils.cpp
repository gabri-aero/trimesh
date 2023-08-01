#include <gtest/gtest.h>
#include <Delaunay.hpp>
#include <PlotUtils.hpp>

#include <random>
#include <ctime>

TEST(PlotUtilsTest, PlotNodes) {
  Plot::close_gnuplot();
  
  std::vector<double> x;
  std::vector<double> y;
  
  std::srand(0);
  const int n = 10;

    std::random_device rd;
    // std::mt19937 gen(rd());
    std::mt19937 gen(0);
    std::uniform_real_distribution<double> dis(0.0, 10.0);

    for (int i = 0; i < n; ++i) {
        x.push_back(dis(gen));
        y.push_back(dis(gen));
    }

  std::vector<Coord2D> points;

	for(size_t i{0}; i<x.size(); i++) {
		points.push_back(Coord2D{x[i], y[i]});
	}

   Delaunay d{points};

   d.compute();

   // Plot::plot_nodes(nodes);
   Plot::plot_mesh(d.get_edges(), d.get_nodes());

   d.add_point(5, 5);
   
   Plot::plot_mesh(d.get_edges(), d.get_nodes());


}
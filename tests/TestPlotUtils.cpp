#include <gtest/gtest.h>
#include <Delaunay.hpp>
#include <PlotUtils.hpp>

#include <random>
#include <ctime>

TEST(PlotUtilsTest, PlotNodes) {
  std::vector<double> x;
  std::vector<double> y;
  
  // Seed the random number generator
  std::srand(static_cast<unsigned>(std::time(nullptr)));

  // Generate an array of 100 random double numbers between 0 and 10
  const int arraySize = 100;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 10.0);

    for (int i = 0; i < arraySize; ++i) {
        x.push_back(dis(gen));
        y.push_back(dis(gen));
    }

  std::vector<Coord2D> points;

	for(size_t i{0}; i<x.size(); i++) {
		points.push_back(Coord2D{x[i], y[i]});
	}

   Delaunay d{points};

   d.compute();

   std::vector<Edge> edges{d.get_edges()};
   std::vector<Node> nodes{d.get_nodes()};

   Plot::plot_nodes(nodes);
   Plot::plot_mesh(edges);
   Plot::plot_mesh(edges, nodes);


}
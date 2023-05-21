#include <gtest/gtest.h>
#include <Delaunay.hpp>

// Delaunay test
TEST(DelaunayTest, GeometryUtils) {
  Coord2D p1{-1, 3};
  Coord2D p2{4, 5};
  Coord2D p3{4, -7};

  ASSERT_NEAR(5.38516480713, dist(p1, p2), 1e-10);
  ASSERT_EQ(12, dist(p2, p3));


  Triangle triangle{Node{p1}, Node{p2}, Node{p3}};
  Coord2D true_circumcenter{3.5, -1};
  Coord2D calc_circumcenter = triangle.circumcenter();
  ASSERT_EQ(true_circumcenter, calc_circumcenter);

  double true_circum_radius{6.02};
  double calc_circum_radius = dist(triangle.circumcenter(), p1);
  ASSERT_NEAR(true_circum_radius, calc_circum_radius, 0.01);

  Node a1{1, 5}; 
  Node a2{1, 4}; 
  Node b1{-2, 2};
  Node b2{-1.5, 2};
  Node c1{8, -6};
  Node c2{6, -6}; 

  ASSERT_EQ(false, triangle.circumscribe(a1));
  ASSERT_EQ(false, triangle.circumscribe(b1));
  ASSERT_EQ(false, triangle.circumscribe(c1));
  
  ASSERT_EQ(true, triangle.circumscribe(a2));
  ASSERT_EQ(true, triangle.circumscribe(b2));
  ASSERT_EQ(true, triangle.circumscribe(c2));
}

TEST(DelaunayTest, TriangulationTest1) {
  std::vector<double> x{1, 3, 5};
  std::vector<double> y{4, 2, 8};

  std::vector<Coord2D> points;

	for(size_t i{0}; i<x.size(); i++) {
		points.push_back(Coord2D{x[i], y[i]});
	}

  Delaunay d{points};

  d.compute();

  std::vector<std::array<int, 2>> calc_edges{d.get_edges_index()};

  std::vector<std::array<int,2>>  true_edges{
    {0, 1},
    {0, 2},
    {1, 2}
  };

  ASSERT_EQ(true_edges, calc_edges);
}


TEST(DelaunayTest, TriangulationTest2) {
  std::vector<double> x{-1.01, -1.01, 1.01, 3.04, 5.05, 8.21, 8.22};
  std::vector<double> y{0, 5, 2.01, 3.02, 2.003, 0, 5.03};

  std::vector<Coord2D> points;

	for(size_t i{0}; i<x.size(); i++) {
		points.push_back(Coord2D{x[i], y[i]});
	}

  Delaunay d{points};

  d.compute();

  std::vector<std::array<int, 2>> calc_edges{d.get_edges_index()};

  std::vector<std::array<int,2>>  true_edges{
    {0, 1},
    {0, 2},
    {0, 4},
    {0, 5},
    {1, 2},
    {1, 3},
    {1, 6},
    {2, 3},
    {2, 4},
    {3, 4},
    {3, 6},
    {4, 5},
    {4, 6},
    {5, 6}
  };

  ASSERT_EQ(true_edges, calc_edges);
}


TEST(DelaunayTest, TriangulationTest3) {
  std::vector<double> x{1, 2, 4, 5, 7};
  std::vector<double> y{3, 6, 2, 8, 4};

  std::vector<Coord2D> points;

	for(size_t i{0}; i<x.size(); i++) {
		points.push_back(Coord2D{x[i], y[i]});
	}

  Delaunay d{points};

  d.compute();

  std::vector<std::array<int, 2>> calc_edges{d.get_edges_index()};

  std::vector<std::array<int,2>>  true_edges{
    {0, 1}, {0, 2}, {1, 2}, {1, 3}, {1, 4}, {2, 4}, {3, 4}
  };

  ASSERT_EQ(true_edges, calc_edges);
}
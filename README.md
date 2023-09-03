# Trimesh

Implementation of an algorithm for meshing 2D domains using triangular elements.

1. Delaunay Triangulation.

It is performed using Bowyer-Watson algorithm. [1, 2]

<p align="center">
  <img src="img/delaunay/nodes.png" alt="Nodes" width="30%" />
  <img src="img/delaunay/mesh.png" alt="Mesh" width="30%" />
  <img src="img/delaunay/mesh_nodes.png" alt="Mesh with Nodes" width="30%" />
</p>

2. Ruppert's mesh refinement

The refinement algorithm aims to improve mesh quality and detail. [3] 
<p align="center">
  <img src="img/cylinder/boundary.png" alt="Nodes" width="30%" />
  <img src="img/cylinder/initial_mesh.png" alt="Mesh" width="30%" />
  <img src="img/cylinder/refined_mesh.png" alt="Mesh" width="30%" />
</p>
Refinement iteration selects worse quality triangle as the triangle with the more acute angle and a new point is added to the Delaunay triangulation at the circumcenter of the triangle at hand. Iteration stops once all triangles have overcome a certain quality criteria. Following that, a similar refinement of big triangles is carried out.
<p align="center">
<img src="img/cylinder/mesh.gif" alt="Mesh GIF" width="60%">
</p>

# Example use cases

## NACA airfoil 2412

<p align="center">
<img src="img/airfoil/airfoil.png">
</p>

**_NOTE:_** The objective of this project was to develop a triangular meshing tool. The provided code has still a lot of room for improvement since the program struggles with some domains and meshing conditions. However, I did this project just for fun. As you might notice there are two main differences w.r.t. Ruppert's algorith: 1. no encroached segments in the boundary are considered 2. a refinement of so-called big triangles are included. Basically Ruppert's algorithm only includes the first one. I included the latter to come closer to typical ANSYS,gmsh,etc. mesh looking. Ideas of other algorithms that account for "big triangles" keeping the conformity of the boundary are welcome.

# References

[1] A. Bowyer, ‘Computing Dirichlet tessellations’, The Computer Journal, vol. 24, no. 2, pp. 162–166, Feb. 1981.

[2] D. F. Watson, ‘Computing the n-dimensional Delaunay tessellation with application to Voronoi polytopes’, The Computer Journal, vol. 24, no. 2, pp. 167–172, Feb. 1981.

[3] J. Ruppert, ‘A Delaunay Refinement Algorithm for Quality 2-Dimensional Mesh Generation’, Journal of Algorithms, vol. 18, no. 3, pp. 548–585, May 1995.

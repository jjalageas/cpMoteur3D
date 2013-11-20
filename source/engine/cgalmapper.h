#ifndef CGALMAPPER_H
#define CGALMAPPER_H

#include <CGAL/Delaunay_triangulation_3.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_3.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

typedef CGAL::Triangulation_3<K>      Triangulation;

typedef Triangulation::Cell_handle    Cell_handle;
typedef Triangulation::Vertex_handle  Vertex_handle;
typedef Triangulation::Locate_type    Locate_type;
typedef Triangulation::Point          Point;


class CGALMapper
{
public:
    CGALMapper();


    void MarchingCube3DSurfaceConstruction();
    void Poisson3DSurfaceConstruction();
    void Delaunay3DSurfaceConstruction();
    void BPA3DSurfaceConstruction();


};

#endif // CGALMAPPER_H

#include "Voronoi.hpp"
#include <vector>
#include<iostream>
int main()
{
    Vor vor;
    std::vector<boost::polygon::point_data<double>> verts;
    verts.push_back( { 40.0f, 40.0f } );
    verts.push_back( { 40.0f, 50.0f } );
    verts.push_back( { 50.0f, 0.0f } );
    verts.push_back( { 50.0f, 40.0f } );

    for ( const auto &vert : verts )
    {
        vor.addVertex( vert );
    }
    vor.compute();
    const auto &cells=vor.getCells();
    std::cout<<"Num Cells"<<cells.size();

}

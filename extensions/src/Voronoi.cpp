#include "Voronoi.hpp"
#include <boost/polygon/voronoi.hpp>
#include <godot_cpp/classes/polygon2d.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/array.hpp>
#include <godot_cpp/variant/packed_vector2_array.hpp>
#include <godot_cpp/variant/typed_array.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/variant/variant.hpp>
#include <godot_cpp/variant/vector2.hpp>

void Vor::addVertex( const boost::polygon::point_data<double> &vertex )
{
    vertices_.emplace_back( vertex.x(), vertex.y() );
    // godot::UtilityFunctions::print( "adding Vertex", vec.x, " ", vec.y );
}
void Vor::compute()
{
    // godot::PackedVector2Array poly_vertices;
    // godot::Array arr;
    //  godot::TypedArray<godot::Polygon2D> polygons;
    boost::polygon::voronoi_diagram<double> vd;
    boost::polygon::construct_voronoi( vertices_.begin(), vertices_.end(), &vd );
    for ( boost::polygon::voronoi_diagram<double>::const_cell_iterator it = vd.cells().begin();
          it != vd.cells().end(); ++it )
    {
        const boost::polygon::voronoi_diagram<double>::cell_type &cell = *it;
        const boost::polygon::voronoi_diagram<double>::edge_type *edge = cell.incident_edge();
        // This is convenient way to iterate edges around Voronoi cell.
        do
        {
            // godot::Vector2 vertex;
            // vertex.x = edge->vertex0()->x();
            // vertex.y = edge->vertex0()->y();
            //  poly_vertices.push_back( vertex );
            if ( edge->is_primary() )
            {
                edge = edge->next();
            }
        } while ( edge != cell.incident_edge() );
        // godot::Polygon2D poly;
        //  poly.set_polygon(
        //    poly2.instantiate();
        //    poly2->set_polygon( poly_vertices );
        //    polygons.push_back( poly2 );
        //  polygons_.push_back( poly_vertices );
    }
}
// godot::Array ::getPolygons()
// {
//     return polygons_;
// }

// void Voronoi::_bind_methods()
// {
//     godot::ClassDB::bind_method( godot::D_METHOD( "addVertex" ), &Vor::addVertex );
//     godot::ClassDB::bind_method( godot::D_METHOD( "compute" ), &Vor::compute );
//     godot::ClassDB::bind_method( godot::D_METHOD( "getPolygons" ), &Voronoi::getPolygons );
// }

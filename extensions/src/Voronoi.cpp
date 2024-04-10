#include "Voronoi.hpp"
#include "boost/polygon/voronoi_diagram.hpp"
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
    boost::polygon::construct_voronoi( vertices_.begin(), vertices_.end(), &vd_ );
    for ( boost::polygon::voronoi_diagram<double>::const_cell_iterator it = vd_.cells().begin();
          it != vd_.cells().end(); ++it )
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

std::vector<boost::polygon::voronoi_cell<double>> Vor::getCells()
{
    return std::vector<boost::polygon::voronoi_cell<double>>( vd_.cells().begin(),
                                                              vd_.cells().end() );
}

void Voronoi::addVertex( const godot::Vector2 &vertex )
{
    vor.addVertex( { vertex.x, vertex.y } );
}

void Voronoi::compute()
{
    vor.compute();
}

godot::Array Voronoi::getPolygons()
{
    godot::UtilityFunctions::print( "Starting get polygons" );
    godot::Array polygons;

    for ( boost::polygon::voronoi_diagram<double>::const_cell_iterator it = vor.vd_.cells().begin();
          it != vor.vd_.cells().end(); ++it )
    {
        const boost::polygon::voronoi_diagram<double>::cell_type &cell = *it;
        const boost::polygon::voronoi_diagram<double>::edge_type *edge = cell.incident_edge();
        godot::PackedVector2Array vertices;
        // This is convenient way to iterate edges around Voronoi cell.
        do
        {
            if ( edge->is_primary() )
            {

                if ( edge->is_finite() )
                {
                    godot::UtilityFunctions::print( edge->vertex0()->x() );
                    godot::UtilityFunctions::print( edge->vertex0()->y() );
                     godot::Vector2 vertex;
                     vertex.x=edge->vertex0()->x();
                     vertex.y=edge->vertex0()->y();
                     vertices.push_back( vertex );
                }
            edge = edge->next();
            }
        } while ( edge != cell.incident_edge() );
        polygons.push_back( vertices );
        vertices.clear();
    }
    godot::UtilityFunctions::print( "End before return of get polygons" );
    return polygons;
}

void Voronoi::_bind_methods()
{
    godot::ClassDB::bind_method( godot::D_METHOD( "addVertex" ), &Voronoi::addVertex );
    godot::ClassDB::bind_method( godot::D_METHOD( "compute" ), &Voronoi::compute );
    godot::ClassDB::bind_method( godot::D_METHOD( "getPolygons" ), &Voronoi::getPolygons );
}

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

// segment_type retrieve_segment(const cell_type& cell) {
//     source_index_type index = cell.source_index() - point_data_.size();
//     return segment_data_[index];
//   }
// point_type retrieve_point(const cell_type& cell) {
//     source_index_type index = cell.source_index();
//     source_category_type category = cell.source_category();
//     if (category == SOURCE_CATEGORY_SINGLE_POINT) {
//       return point_data_[index];
//     }
//     index -= point_data_.size();
//     if (category == SOURCE_CATEGORY_SEGMENT_START_POINT) {
//       return low(segment_data_[index]);
//     } else {
//       return high(segment_data_[index]);
//     }
//   }
//
// void clip_infinite_edge(
//       const vorType::edge_type& edge, std::vector<point_type>* clipped_edge) {
//     const vorType::cell_type& cell1 = *edge.cell();
//     const vorType::cell_type& cell2 = *edge.twin()->cell();
//     point_type origin, direction;
//     // Infinite edges could not be created by two segment sites.
//     if (cell1.contains_point() && cell2.contains_point()) {
//       point_type p1 = retrieve_point(cell1);
//       point_type p2 = retrieve_point(cell2);
//       origin.x((p1.x() + p2.x()) * 0.5);
//       origin.y((p1.y() + p2.y()) * 0.5);
//       direction.x(p1.y() - p2.y());
//       direction.y(p2.x() - p1.x());
//     } else {
//       origin = cell1.contains_segment() ?
//           retrieve_point(cell2) :
//           retrieve_point(cell1);
//       segment_type segment = cell1.contains_segment() ?
//           retrieve_segment(cell1) :
//           retrieve_segment(cell2);
//       coordinate_type dx = high(segment).x() - low(segment).x();
//       coordinate_type dy = high(segment).y() - low(segment).y();
//       if ((low(segment) == origin) ^ cell1.contains_point()) {
//         direction.x(dy);
//         direction.y(-dx);
//       } else {
//         direction.x(-dy);
//         direction.y(dx);
//       }
//     }
//     coordinate_type side = xh(brect_) - xl(brect_);
//     coordinate_type koef =
//         side / (std::max)(fabs(direction.x()), fabs(direction.y()));
//     if (edge.vertex0() == NULL) {
//       clipped_edge->push_back(point_type(
//           origin.x() - direction.x() * koef,
//           origin.y() - direction.y() * koef));
//     } else {
//       clipped_edge->push_back(
//           point_type(edge.vertex0()->x(), edge.vertex0()->y()));
//     }
//     if (edge.vertex1() == NULL) {
//       clipped_edge->push_back(point_type(
//           origin.x() + direction.x() * koef,
//           origin.y() + direction.y() * koef));
//     } else {
//       clipped_edge->push_back(
//           point_type(edge.vertex1()->x(), edge.vertex1()->y()));
//     }
//   }
void Vor::addVertex( const boost::polygon::point_data<double> &vertex )
{
    point_data_.emplace_back( vertex.x(), vertex.y() );
}
void Vor::compute()
{
    boost::polygon::construct_voronoi( point_data_.begin(), point_data_.end(),
                                       segment_data_.begin(), segment_data_.end(), &vd_ );
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

        if ( it->incident_edge()->twin() )
        {
            godot::UtilityFunctions::print( "degen cell found" );
        }
        // This is convenient way to iterate edges around Voronoi cell.
        do
        {

            edge->is_secondary();
            it->incident_edge();
            if ( edge->is_primary() )
            {

                if ( edge->is_finite() )
                {
                    godot::Vector2 vertex;
                    vertex.x = edge->vertex0()->x();
                    vertex.y = edge->vertex0()->y();
                    vertices.push_back( vertex );
                }
                else
                {
                    godot::UtilityFunctions::print( "Infinite edge found" );
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

godot::Array Voronoi::getCellCenters()
{
    godot::Array arr;
    for ( boost::polygon::voronoi_diagram<double>::const_cell_iterator it = vor.vd_.cells().begin();
          it != vor.vd_.cells().end(); ++it )
    {
        // godot::Vector2 vec;
        // vec.x=it->;
        // arr.push_back();
    }
    return {};
}

void Voronoi::_bind_methods()
{
    godot::ClassDB::bind_method( godot::D_METHOD( "addVertex" ), &Voronoi::addVertex );
    godot::ClassDB::bind_method( godot::D_METHOD( "compute" ), &Voronoi::compute );
    godot::ClassDB::bind_method( godot::D_METHOD( "getPolygons" ), &Voronoi::getPolygons );
}

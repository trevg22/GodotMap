#include "Voronoi.hpp"
#include <boost/polygon/voronoi.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/vector2.hpp>

void Voronoi::addVertex( const godot::Vector2 &vec )
{
    vertices_.emplace_back( vec.x, vec.y );
}
void Voronoi::compute()
{
}
godot::TypedArray<godot::Polygon2D> Voronoi::getPolygons()
{
    return godot::TypedArray<godot::Polygon2D>{};
}

void Voronoi::_bind_methods()
{
    godot::ClassDB::bind_method( godot::D_METHOD( "addVertex" ), &Voronoi::addVertex );
    godot::ClassDB::bind_method( godot::D_METHOD( "compute" ), &Voronoi::compute );
    godot::ClassDB::bind_method( godot::D_METHOD( "getPolygons" ), &Voronoi::getPolygons );
}

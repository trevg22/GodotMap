extends Node2D


# Called when the node enters the scene tree for the first time.
func _ready():
	var points=[Vector2(40, 40),
								  Vector2(40, 50),
								  Vector2(50, 50),
								  Vector2(50, 40)
								]
	var vor=Voronoi.new()
	
	for coord in points:
		vor.addVertex(coord)
		
	
	
	#vor.compute();
	
	#var polys=vor.getPolygons()
	
	#or poly in polys:
		#poly.set_color(Color(1,0,0))		
		#add_child(poly)


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass

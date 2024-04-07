extends Node2D


# Called when the node enters the scene tree for the first time.
func _ready():
	var poly = Polygon2D.new()
	var points=[]
	poly.set_polygon([Vector2(40, 40),
								  Vector2(40, 50),
								  Vector2(50, 50),
								  Vector2(50, 40)
								])
	poly.set_color(Color(1,0,0))
	
	var something="whatever";
	var ex=Example.new()
	var vor=Voronoi.new()
	vor.compute();
	
	#vor.addVertex(Vector2(50,50))
	
	add_child(poly)


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass

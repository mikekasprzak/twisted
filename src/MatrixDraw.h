// - ------------------------------------------------------------------------------------------ - //
#ifndef __MATRIXDRAW_H__
#define __MATRIXDRAW_H__
// - ------------------------------------------------------------------------------------------ - //
extern Matrix3x3 ViewMatrix;
// - ------------------------------------------------------------------------------------------ - //
void MatrixRect( BITMAP* Target, const Matrix3x3& Matrix, const Rect2D& Rect, int Color ) {
	// Get our points //
	Vector2D Point[4];
	Point[0] = Rect.P1();
	Point[1] = Vector2D( Rect.P2().x, Rect.P1().y );
	Point[2] = Rect.P2();
	Point[3] = Vector2D( Rect.P1().x, Rect.P2().y );
	
	// Transform them by the matrix //
	Point[0] = Point[0].ToVector3D().ApplyMatrix( Matrix ).ToVector2D();
	Point[1] = Point[1].ToVector3D().ApplyMatrix( Matrix ).ToVector2D();
	Point[2] = Point[2].ToVector3D().ApplyMatrix( Matrix ).ToVector2D();
	Point[3] = Point[3].ToVector3D().ApplyMatrix( Matrix ).ToVector2D();
	
	// Draw our 4 lines to make the rectangle //
	rect( Target, (int)(Point[0].x), (int)(Point[0].y), (int)(Point[1].x), (int)(Point[1].y), Color );
	rect( Target, (int)(Point[1].x), (int)(Point[1].y), (int)(Point[2].x), (int)(Point[2].y), Color );
	rect( Target, (int)(Point[2].x), (int)(Point[2].y), (int)(Point[3].x), (int)(Point[3].y), Color );
	rect( Target, (int)(Point[3].x), (int)(Point[3].y), (int)(Point[0].x), (int)(Point[0].y), Color );
}
// - ------------------------------------------------------------------------------------------ - //
void MatrixCircle( BITMAP* Target, const Matrix3x3& Matrix, const Vector2D& Pos, const Real& Radius, int Color ) {
	// Transform our point by the matrix //
	Vector2D Point = Pos.ToVector3D().ApplyMatrix( Matrix ).ToVector2D();
	
	// Draw our circle //
	circle( Target, (int)Point.x, (int)Point.y, (int)Radius, Color );
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __MATRIXDRAW_H__ //
// - ------------------------------------------------------------------------------------------ - //

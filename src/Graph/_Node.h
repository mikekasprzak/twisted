// - ------------------------------------------------------------------------------------------ - //
#ifndef __Graph_Node_H__
#define __Graph_Node_H__
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
// Nodes are merely the positions for Branches. This way, each node can branch to multiple //
//   other Nodes, and the 2 way Travel graph can be maintained. //
// - ------------------------------------------------------------------------------------------ - //
template
class cNode {
public:
	// Position on this map //
	Vector2D Pos;
	
	// Indices of Links connected to me //
	std::vector< int > PathLinkIndex;
	
public:
	cNode() 
	{
	}
	
	cNode( const Vector2D& _Pos ) :
		Pos( _Pos )
	{
	}

public:
	
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Graph_Node_H__ //
// - ------------------------------------------------------------------------------------------ - //

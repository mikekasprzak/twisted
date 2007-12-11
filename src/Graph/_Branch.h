// - ------------------------------------------------------------------------------------------ - //
#ifndef __Graph_Branch_H__
#define __Graph_Branch_H__
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
// Branches are connections between nodes.  
// - ------------------------------------------------------------------------------------------ - //
template< class InfoType >
class cBranch {
public:
	// The nodes I'm connected to //
	int a, b;
	
	// Additional information for this branch //
	InfoType Info;
public:
	cBranch() :
		a( 0 ),
		b( 0 )
	{
	}
	
	cBranch( const int& _a, const int& _b, const InfoType& _Info = InfoType() ) :
		a( _a ),
		b( _b ),
		Info( _Info )
	{
	}

public:
	
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Graph_Branch_H__ //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#ifndef __Graph_Graph_H__
#define __Graph_Graph_H__
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
template< class tNodeData >
class cGraph {
public:
	typedef int IndexType;
	
	// Arc's are connections to Nodes //
	class cArc {
	public:
		// Index of a node //
		IndexType Index;
		
		//tArcData Data;
		
	public:
		cArc( const IndexType _Index ) :
			Index( _Index )
		{
		}
	};
	
	// Nodes of our Graph //
	class cNode {
	public:
		// Indices of branches I follow //
		std::vector< cArc > Arc;
		
		// Information contained by this Node //
		tNodeData Data;
		
	public:
		inline cNode()
		{
		}
		
		inline cNode( const tNodeData& _Data ) :
			Data( _Data )
		{
		}
		
		inline const IndexType AddArc( const IndexType _Index ) {
			Arc.push_back( cArc( _Index ) );
			
			return Arc.size() - 1;
		}
		
		inline void DeleteArc( const IndexType _Index ) {
			// TODO: Assert, error if index greater than size, less than zero //

			Arc.erase( Arc.begin() + _Index );
		}
	};

public:
	// Vector of nodes //
	std::vector< cNode > Node;
	
public:
	cGraph() 
	{
	}
	
	inline cNode& operator [] ( const IndexType _Index ) {
		return Node[ _Index ];
	}

public:
	inline const IndexType AddNode( const tNodeData& _Info = tNodeData() ) {
		// Add the node //
		Node.push_back( cNode( _Info ) );
		
		// Return what the index is //
		return Node.size() - 1;
	}
	
	inline void DeleteNode( const IndexType _Index ) {
		// TODO: Assert, error if index greater than size, less than zero //
		
		// Remove all arc's that reference this node //
		for ( size_t idx = 0; idx < Node.size(); idx++ ) {
			for ( size_t idx2 = 0; idx2 < Node[idx].Arc.size(); idx2++ ) {
				if ( Node[idx].Arc[idx2].Index == _Index ) {
					// Remove the Arc //
					Node[idx].DeleteArc( idx2 );
					
					// go back an index, since we deleted an arc //
					idx2--;
				}
			}
		}
		
		// Delete the Node //
		Node.erase( Node.begin() + _Index );
	}
	
	
public:
//	inline std::vector<PositionType> FindPath( const PositionType& _Vs ) {
//		// Start with an empty vector of position types, in case we find what we're looking for //
//		std::vector<PositionType> Path;
//			
//		// Recursively search //
//		
//		
//		// Return the vector (an empty one, if needed) //
//		return Path;
//	}
//	
//	void FindPath_Recursive( std::vector<PositionType>& Path ) {
//		// TODO: some method for populating the path vector with nodes from a continuous path //
//		
//		// Note: it's probably doable to track/know the number of nodes in the path.  So when //
//		//   a match is found, resize the path vector to the correct size, instead of push-backing//
//		
//		// Call "test" function of branch, to see if path is ok //
//		// This being the only difference between the conditional and non conditional //
//		// It might be possible to have the condition test evaluate out to nothing, meaning this //
//		//   class might be usable for both conditional, and normal use.  It's a heavy class //
//		//   either way.  You might be able to use a template on a passed in class to add the //
//		//   extra elements needed to perform "dead" tests, instead of having to add the dummy //
//		//   test function to the class, or deriving from some base info class //
//	}
	
	
	
	inline std::vector<Index> FindPath( const IndexType a, const IndexType b ) {
		// NOTE: Perhaps start with a static array large enough to hold every node, and if ok //
		//   return a path ... ? //
		
		
		// Start with an empty vector of position types, in case we find what we're looking for //
		std::vector<PositionType> Path; // Every node on the path //
	
			
		// Bredth First Search //
		
		
		// Return the vector (an empty one, if needed) //
		return Path;
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Graph_Graph_H__ //
// - ------------------------------------------------------------------------------------------ - //

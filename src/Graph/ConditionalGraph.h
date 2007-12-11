// - ------------------------------------------------------------------------------------------ - //
#ifndef __Graph_ConditionalGraph_H__
#define __Graph_ConditionalGraph_H__
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
template< class PositionType, class BranchInfoType, class TestVersusType >
class cConditionalGraph {
public:
	typedef int IndexType;
	
	class cNode {
	public:
		// Position of this Node //
		PositionType Pos;
		
		// Indices of branches I follow //
		std::vector< IndexType > BranchIndex;
			
		// Algorithm Variables //
		
	public:
		inline cNode()
		{
		}
		
		inline cNode( const PositionType& _Pos ) :
			Pos( _Pos )
		{
		}
	};
	
	
	class cBranch {
	public:
		// The nodes I'm connected to //
		IndexType a, b;
		
		// Additional information for this branch //
		BranchInfoType Info;
		
		// Algorithm Variables //
		bool Followed;
		
	public:
		inline cBranch() :
			a( 0 ),
			b( 0 ),
			Followed( false )
		{
		}
		
		inline cBranch( const IndexType _a, const IndexType _b, const BranchInfoType& _Info = BranchInfoType() ) :
			a( _a ),
			b( _b ),
			Info( _Info ),
			Followed( false )
		{
		}
		
	public:
		// Return the next node Index //
		inline const IndexType NextIndex( const IndexType Node ) {
			// TODO: Assert, error if Prev not A or B //
			if ( Node == a )
				return b;
			else
				return a;
		}
		
		// Info types must have a test function //
		inline const bool Test( const TestVersusType& Vs ) const {
			return Info.Test( Vs );
		}
	};
	
	std::vector< cNode > Node;
	std::vector< cBranch > Branch;

	
public:
	cConditionalGraph() 
	{
	}
	
public:
	inline const IndexType AddNode( const PositionType& _Pos ) {
		// Add the position to the node list //
		Node.push_back( cNode( _Pos ) );
		// Return what the index is //
		return Node.size() - 1;
	}
	
	inline void DeleteNode( const IndexType _Index ) {
		// TODO: Assert, error if index greater than size, less than zero //
		
		// Remove all branches that reference this node //
//		bool References = true;
//		while ( References ) {
//			References = false;
//			for ( size_t idx = 0; idx < Branch.size(); idx++ ) {
//				if ( Branch[idx].a >= Index ) {
//					
//				}
//			}
//		}
		
		// Delete the Node //
		Node.erase( Node.begin() + _Index );
	}
	
	inline const IndexType AddBranch( 
		const IndexType _a,
		const IndexType _b,
		const BranchInfoType& _Info = BranchInfoType()
		)
	{
		// TODO: Assert, valid node Id ranges //
		
		// Add the branch to the branch list //
		Branch.push_back( cBranch( _a, _b, _Info ) );
		// Return what index the branch is //
		return Branch.size() - 1;
	}
	
	inline void DeleteBranch( const IndexType _Index ) {
		// TODO: Assert, error if index greater than size, less than zero //
		// I don't need to worry about corrupting any linkage, so I can merely detele the branch //
		Branch.erase( Branch.begin() + _Index );
	}

public:
	inline const PositionType FindNearestPoint( const PositionType& _Vs ) const {
//		for ( size_t idx = 0; idx < Branch.size(); idx++ ) {
//		}
		return PositionType::Zero;
	}
	
	// TODO: ??? //
	cBranch DummyBranch;
	inline const cBranch& FindNearestBranch( const PositionType& _Vs ) const {
		if ( Branch.empty() ) {
			// TODO: Assert, dummy branch //
			return DummyBranch;
		}
		
		Real ShortestLength = 555555;
		IndexType BestIndex = 0;
		
//		for ( size_t idx = 1; idx < Branch.size(); idx++ ) {
//		}

		return Branch[ BestIndex ];
	}
	
	// TODO: ??? //
	BranchInfoType DummyBranchInfoType;
	inline const BranchInfoType& FindNearestBranchInfo( const PositionType& _Vs ) const {
		if ( Branch.empty() ) {
			// TODO: Assert, dummy branch //
			return DummyBranchInfoType;
		}
		
		Real ShortestLength = 555555;
		IndexType BestIndex = 0;
		
//		for ( size_t idx = 1; idx < Branch.size(); idx++ ) {
//		}

		return Branch[ BestIndex ].Info;
	}
	
	// TODO: ??? //
	cNode DummyNode;
	inline const cNode& FindNearestNode( const PositionType& _Vs ) const {
		if ( Node.empty() ) {
			// TODO: Assert, dummy node //
			return DummyNode;
		}
		
		Real ShortestLength = 555555;
		IndexType BestIndex = 0;
		
//		for ( size_t idx = 1; idx < Node.size(); idx++ ) {
//		}

		return Node[ BestIndex ];
	}
	
public:
	inline std::vector<PositionType> FindPath( const PositionType& _Vs ) {
		// Start with an empty vector of position types, in case we find what we're looking for //
		std::vector<PositionType> Path;
			
		// Recursively search //
		
		
		// Return the vector (an empty one, if needed) //
		return Path;
	}
	
	void FindPath_Recursive( std::vector<PositionType>& Path ) {
		// TODO: some method for populating the path vector with nodes from a continuous path //
		
		// Note: it's probably doable to track/know the number of nodes in the path.  So when //
		//   a match is found, resize the path vector to the correct size, instead of push-backing//
		
		// Call "test" function of branch, to see if path is ok //
		// This being the only difference between the conditional and non conditional //
		// It might be possible to have the condition test evaluate out to nothing, meaning this //
		//   class might be usable for both conditional, and normal use.  It's a heavy class //
		//   either way.  You might be able to use a template on a passed in class to add the //
		//   extra elements needed to perform "dead" tests, instead of having to add the dummy //
		//   test function to the class, or deriving from some base info class //
	}
	
	
	
	inline std::vector<PositionType> FindBestPath( const PositionType& _Vs ) {
		// Start with an empty vector of position types, in case we find what we're looking for //
		std::vector<PositionType> Path;
		// The length of the current path //
		Real PathLength = 55555;
			
		// Recursively search //
		
		
		// Return the vector (an empty one, if needed) //
		return Path;
	}
	
	inline bool FindAnyPath( const PositionType& _Vs ) {
		bool PathFound = false;
		
		// Recursively search //
		
		// Return if a path was found //
		return PathFound;
	}
	
	
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Graph_ConditionalGraph_H__ //
// - ------------------------------------------------------------------------------------------ - //

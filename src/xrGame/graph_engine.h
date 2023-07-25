////////////////////////////////////////////////////////////////////////////
//	Module 		: graph_engine.h
//	Created 	: 21.03.2002
//  Modified 	: 26.11.2003
//	Author		: Dmitriy Iassenev
//	Description : Graph engine
////////////////////////////////////////////////////////////////////////////

#pragma once

#include "a_star.h"
#include "edge_path.h"
#include "vertex_manager_fixed.h"
#include "vertex_manager_hash_fixed.h"
#include "vertex_allocator_fixed.h"
#include "data_storage_bucket_list.h"
#include "data_storage_binary_heap.h"
#include "path_manager.h"
#include "graph_engine_space.h"
#include "profiler.h"

#include "operator_condition.h"
#include "condition_state.h"
#include "operator_abstract.h"

namespace hash_fixed_vertex_manager
{
IC u32 to_u32(GraphEngineSpace::CWorldState const& other) { return (other.hash_value()); }
IC u32 to_u32(shared_str const& string)
{
	const str_value* get = string._get();
	return (*(u32 const*)&get);
}
} // namespace hash_fixed_vertex_manager

using namespace GraphEngineSpace;

class CGraphEngine
{
public:
    typedef CDataStorageBinaryHeap CSolverPriorityQueue;
    typedef CDataStorageBinaryHeap CStringPriorityQueue;
    typedef CDataStorageBucketList<u32, u32, 8 * 1024, false> CPriorityQueue;
    typedef CVertexManagerFixed<u32, u32, 8> CVertexManager;
    typedef CVertexManagerHashFixed<u32, _solver_index_type, 256, 8 * 1024> CSolverVertexManager;
    typedef CVertexManagerHashFixed<u32, shared_str, 128, 1024> CStringVertexManager;
    typedef CVertexAllocatorFixed<64 * 1024> CVertexAllocator;
    typedef CVertexAllocatorFixed<8 * 1024> CSolverVertexAllocator;
    typedef CVertexAllocatorFixed<1024> CStringVertexAllocator;

    typedef CAStar<_dist_type, CPriorityQueue, CVertexManager, CVertexAllocator> CAlgorithm;

    typedef CAStar<_solver_dist_type, CSolverPriorityQueue, CSolverVertexManager, CSolverVertexAllocator, true,
        CEdgePath<_solver_edge_type, true>>
        CSolverAlgorithm;

    typedef CAStar<float, CStringPriorityQueue, CStringVertexManager, CStringVertexAllocator> CStringAlgorithm;

    CAlgorithm* m_algorithm;

    CSolverAlgorithm* m_solver_algorithm;
    CStringAlgorithm* m_string_algorithm;

public:
    IC CGraphEngine(u32 max_vertex_count);
    virtual ~CGraphEngine();
    IC const CSolverAlgorithm& solver_algorithm() const;

    template <typename _Graph, typename _Parameters>
    IC bool search(const _Graph& graph, const shared_str& start_node, const shared_str& dest_node,
        xr_vector<shared_str>* node_path, _Parameters& parameters);

    template <typename _Graph, typename _Parameters>
    IC bool search(const _Graph& graph, const _index_type& start_node, const _index_type& dest_node,
        xr_vector<_index_type>* node_path, const _Parameters& parameters);

    template <typename _Graph, typename _Parameters>
    IC bool search(const _Graph& graph, const _index_type& start_node, const _index_type& dest_node,
        xr_vector<_index_type>* node_path, _Parameters& parameters);

    template <typename _Graph, typename _Parameters, typename _PathManager>
    IC bool search(const _Graph& graph, const _index_type& start_node, const _index_type& dest_node,
        xr_vector<_index_type>* node_path, const _Parameters& parameters, _PathManager& path_manager);

    template <typename T1, typename T2, typename T3, typename T4, typename T5, bool T6, typename T7, typename T8,
        typename _Parameters>
    IC bool search(const CProblemSolver<T1, T2, T3, T4, T5, T6, T7, T8>& graph, const _solver_index_type& start_node,
        const _solver_index_type& dest_node, xr_vector<_solver_edge_type>* node_path, const _Parameters& parameters);
};

#include "graph_engine_inline.h"

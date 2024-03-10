# CDijkstraPathrouter Markdown File

## Code Segment
```
class CDijkstraPathRouter : public CPathRouter{
    private:
        struct SImplementation;
        std::unique_ptr<SImplementation> DImplementation;
    public:
        CDijkstraPathRouter();
        ~CDijkstraPathRouter();

        std::size_t VertexCount() const noexcept;
        TVertexID AddVertex(std::any tag) noexcept;
        std::any GetVertexTag(TVertexID id) const noexcept;
        bool AddEdge(TVertexID src, TVertexID dest, double weight, bool bidir = false) noexcept;
        bool Precompute(std::chrono::steady_clock::time_point deadline) noexcept;
        double FindShortestPath(TVertexID src, TVertexID dest, std::vector<TVertexID> &path) noexcept;
};
```

## Features
Dijkstra Path Router use the path route code segement to execute the Dijkstra method in order to find the shortest path with the given inputs from the user.
- CDijkstraPathRouter: Constructor all of the implementations
- ~CDijkstraPathRouter: Deconstructor of the code
- Vertex Count: Returns the amount of vertex
- Add Vertex: Adds a vertex to the ID the user inputs
- Get Vertex Tag: Gets the tag of the vertex specified by id if id is in the path router.
- Add Edge: Adds the edge between two node IDs and it's weight
- Precompute: Has time flow within the map
- Find Shortest Path: Computes which path is the shortest when it comes to going from one node to another, based on the input the user gives.

## Example
CDijkstraPathRouter PathRouter: Constructs a DijkstraPathRouter to the variable PathRouter

Vertices.push_back(PathRouter.AddVertex(_)): Adds a vertex to the route while also keeping track of it in a container, most likely a vector

PathRouter.AddEdge(Vertices[_], Vertices[_], x): Adds an edge between the two vertices, while the third input would be the weight amount

EXPECT_EQ(12.0, PathRouter.FindShortestPath(Vertices[_], Vertices[_], Route)): Executes the code to find the shortest path within the given graph and then returns the weight it is. First input would be the expected weight while the second is the code.

## Issues
No issues within these function and code. All code can be executed correctly.
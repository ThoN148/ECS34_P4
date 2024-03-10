# CPathrouter MarkDown File

## Code Segment
```
class CPathRouter{
    public:
        using TVertexID = std::size_t;

        static constexpr TVertexID InvalidVertexID = std::numeric_limits<TVertexID>::max();
        static constexpr double NoPathExists = std::numeric_limits<double>::max();

        virtual ~CPathRouter(){};

        virtual std::size_t VertexCount() const noexcept = 0;
        virtual TVertexID AddVertex(std::any tag) noexcept = 0;
        virtual std::any GetVertexTag(TVertexID id) const noexcept = 0;
        virtual bool AddEdge(TVertexID src, TVertexID dest, double weight, bool bidir = false) noexcept = 0;
        virtual bool Precompute(std::chrono::steady_clock::time_point deadline) noexcept = 0;
        virtual double FindShortestPath(TVertexID src, TVertexID dest, std::vector<TVertexID> &path) noexcept = 0;
};
```

## Features
Path Router is a code file that support the DijkstraPathRouter.cpp File that has the functions. 
- Vertex Count: Returns the amount of vertex
- Add Vertex: Adds a vertex to the ID the user inputs
- Get Vertex Tag: Gets the tag of the vertex specified by id if id is in the path router.
- Add Edge: Adds the edge between two node IDs and it's weight
- Precompute: Has time flow within the map
- Find Shortest Path: Computes which path is the shortest when it comes to going from one node to another, based on the input the user gives.
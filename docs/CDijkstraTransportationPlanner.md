# CDijkstraTransportationPlanner MarkDown File

## Code Segment
```
class CDijkstraTransportationPlanner : public CTransportationPlanner{
    private:
        struct SImplementation;
        std::unique_ptr<SImplementation> DImplementation;
    public:
        CDijkstraTransportationPlanner(std::shared_ptr<SConfiguration> config);
        ~CDijkstraTransportationPlanner();

        std::size_t NodeCount() const noexcept override;
        std::shared_ptr<CStreetMap::SNode> SortedNodeByIndex(std::size_t index) const noexcept override;

        double FindShortestPath(TNodeID src, TNodeID dest, std::vector< TNodeID > &path) override;
        double FindFastestPath(TNodeID src, TNodeID dest, std::vector< TTripStep > &path) override;
        bool GetPathDescription(const std::vector< TTripStep > &path, std::vector< std::string > &desc) const override;
};
```

## Features
Dijkstra Transportation Planner heavily uses other code structors and functions such as Path Router and Dijkstra Path Router. It a struct that finds the fastest and shortest path within a given graph (street map) and returns the user the information.
- CDijkstraTransportationPlanner: Constructs the implementation needed for the functions
- ~CDjikstraTransportationPlanner: Deconstructs the implemetations
- Node Count: Returns the amount of nodes are in the street map
- Sorted Node by Index: Returns the node specified by a given index, the node is sorted either numerically 0 -> Infinity
- Find Shortest Path: Returns the distances of the shortest path between the source node, and the desired node. Also Keeps track of the nodes visit in order to know the path taken
- Find Fastest Path: Returns the time in hours for the fastest path between the src and dest nodes
- Get Path Description: Takes the trip steps path and converts it into a human readable set of steps. Returns a boolean

## Examples
CDijkstraTransportationPlanner Planner: This constructs the implementations to the variable Planner

Planner.NodeCount(): Would return the amount of nodes if there are any within the street map

Planner.SortedNodeByIndex(index): If you want to specifically look for a node and you know its location on the vector by index, you can input this code to retrieve it

Planner.FindShortestPath(src node, dest node, path): The same as the one from DijkstraPathRouter. Returns the distances from the source node to the desired, this would keep the path it took and store it in the third input variable

Planner.FindFastestPath(src node, dest node, path): This gives you the fastest time, either biking bussing or walking, from your source node to your desired node and stores the path.

## Issues
Currently Fastest path and Path description isn't programmed yet.

Shortest Path is having issues storing the path it takes and keeping it.


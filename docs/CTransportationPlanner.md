# CTransportationPlanner Markdown File

## Code Segment
```
class CTransportationPlanner{
    public:
        using TNodeID = CStreetMap::TNodeID;
        enum class ETransportationMode {Walk, Bike, Bus};
        using TTripStep = std::pair<ETransportationMode, TNodeID>;

        struct SConfiguration{
            virtual ~SConfiguration(){};
            virtual std::shared_ptr<CStreetMap> StreetMap() const noexcept = 0;
            virtual std::shared_ptr<CBusSystem> BusSystem() const noexcept = 0;
            virtual double WalkSpeed() const noexcept = 0;
            virtual double BikeSpeed() const noexcept = 0;
            virtual double DefaultSpeedLimit() const noexcept = 0;
            virtual double BusStopTime() const noexcept = 0;
            virtual int PrecomputeTime() const noexcept = 0;
        };

        virtual ~CTransportationPlanner(){};

        virtual std::size_t NodeCount() const noexcept = 0;
        virtual std::shared_ptr<CStreetMap::SNode> SortedNodeByIndex(std::size_t index) const noexcept = 0;

        virtual double FindShortestPath(TNodeID src, TNodeID dest, std::vector< TNodeID > &path) = 0;
        virtual double FindFastestPath(TNodeID src, TNodeID dest, std::vector< TTripStep > &path) = 0;
        virtual bool GetPathDescription(const std::vector< TTripStep > &path, std::vector< std::string > &desc) const = 0;
};
```

## Features
The transpotation planner funnels all of the information needed for the street maps within the nodes/vertices. Such as bus, walk, bike information and speed.
- CTransportationPlanner: constructor for the implementation
- ~CTransportationPlanner: Deconstructor for the implementation
- FindShortestPath: Returns the distances between two nodes that is the best aka shortest/smallest
- FindFastestPath: returns the time it takes between the two nodes at a fast rate, based on the speed
- GetPathDescription: EXTRA CREDIT, This returns the user the information of the path such as if its bikable, bus, or only walk, etc.

## Example
CTransportationPlanner Planner: Construct a variable named Planner to execute the functions

~CTransportationPlanner: Destroy/Deconstruct the variable

FindShortestPath: After you constructed a planner, you can use planner.findshortestpath(src, dest, path) with the variable inputs in order to get the information

FindFastestPath: Same as the shortest path, itll return the speed intsead of the distance however

GetPathDescription: This is just incase you want to see the information and have it looked upon
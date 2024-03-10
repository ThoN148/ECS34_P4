#include "DijkstraTransportationPlanner.h"
#include "DijkstraPathRouter.h"
#include "GeographicUtils.h"
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <iostream>

struct CDijkstraTransportationPlanner::SImplementation{
    // Setting Variables for the Maps / Systems
    std::shared_ptr< CStreetMap > DStreetMap;
    std::shared_ptr< CBusSystem > DBusSystem;

    // Setting Variables up for the path ways
    CDijkstraPathRouter DShortestPathRouter;
    CDijkstraPathRouter DFastestPathRouterBike;
    CDijkstraPathRouter DFastestPathRouteWalkBus;

    //Setting Variables for the Vertex / Nodes
    std::unordered_map< CStreetMap::TNodeID, CPathRouter::TVertexID > DNodeToVertexID;
    std::vector< std::shared_ptr< CStreetMap::SNode > > DSortedNodes;

    // Setting up the condition to sort
	static bool NodeIDCompare(std::shared_ptr< CStreetMap::SNode > left, std::shared_ptr< CStreetMap::SNode > right){
        return left->ID() < right->ID();
    }

    SImplementation(std::shared_ptr< SConfiguration > config){
        DStreetMap = config->StreetMap();
        DBusSystem = config->BusSystem();

        // Goes through the Nodes within the Street map and adds the ids of the node to the path routes.
        for(size_t i = 0; i < DStreetMap->NodeCount(); i++){
            auto Node = DStreetMap->NodeByIndex(i);
            auto VertexID = DShortestPathRouter.AddVertex(Node->ID());
            DFastestPathRouterBike.AddVertex(Node->ID());
            DFastestPathRouteWalkBus.AddVertex(Node->ID());
            DNodeToVertexID[(Node->ID())] = VertexID;


        }

        // Goes through the Ways within the street map and adds the way attributes to the descriptions of the way
        for(size_t i = 0; i < DStreetMap->WayCount(); i++){
            auto Way = DStreetMap->WayByIndex(i);

            // Creating boolean values
            bool Bikable = Way->GetAttribute("Bicycle") != "no"; // Or do != "no" either or not really sure what he wants
            bool Bidirectional = Way->GetAttribute("oneway") != "yes"; //same as above do either == or !=

            //
            auto PreviousNodeID = Way->GetNodeID(0);
            for(size_t j = 1; j < Way->NodeCount(); j++){
                auto NextNodeID = Way->GetNodeID(j);
            }
        }

        // Adds the nodes to the vector
        for(size_t i = 0; i < DStreetMap->NodeCount(); i++){
            auto currNode = DStreetMap->NodeByIndex(i);
            DSortedNodes.push_back(currNode);
        }
        
        // Sort out the nodes
        std::sort(DSortedNodes.begin(), DSortedNodes.end(), NodeIDCompare);
    }


    // Returns the number of nodes in the street map
    std::size_t NodeCount() const noexcept{
        return DStreetMap->NodeCount();
    }

    // Returns the street map node specified by index if index is less than the NodeCount().
    // Nullptr is returned if index is greater than or equal to NodeCount().
    // The nodes are sorted by Node ID.
    std::shared_ptr<CStreetMap::SNode> SortedNodeByIndex(std::size_t index) const noexcept{
        if(index < NodeCount()){
            return DSortedNodes[index];
        }

        return nullptr;
    }

    // Returns the distance in miles between the src and dest nodes of the shortest path if one exists.
    // NoPathExists is returned if no path exists.
    // The nodes of the shortest path are filled in the path parameter.
    double FindShortestPath(TNodeID src, TNodeID dest, std::vector< TNodeID > &path){
        std::vector< CPathRouter::TVertexID > ShortestPath;
        auto SourceVertexID = DNodeToVertexID[src];
        auto DestinationVertexID = DNodeToVertexID[dest];

        if(!DShortestPathRouter.VertexCount()){
            return CPathRouter::NoPathExists;
        }

        auto Distance = DShortestPathRouter.FindShortestPath(SourceVertexID, DestinationVertexID, ShortestPath);
        path.clear(); // Empty out anything in the path

        // After executing command shortest path should not be empty
        /*if(!ShortestPath.empty()){
            std::cout << "NOT EMPTY\n";
        }
        else{
            std::cout << "EMPTY\n";
        }*/

        // Pushes the nodes into the path vector
        for(auto VertexID :  ShortestPath){
            path.push_back(DShortestPathRouter.AddVertex(VertexID));
        }

        return Distance;
    }

    // Returns the time in hours for the fastest path between the src and dest nodes of the if one exists.
    // NoPathExists is returned if no path exists.
    // The transportation mode and nodes of the fastest path are filled in the path parameter.
    double FindFastestPath(TNodeID src, TNodeID dest, std::vector< TTripStep > &path){
        std::vector< CTransportationPlanner::TTripStep > FastestPath;

        
        return CPathRouter::NoPathExists;
    }

    // Returns true if the path description is created.
    // Takes the trip steps path and converts it into a human readable set of steps.
    bool GetPathDescription(const std::vector< TTripStep > &path, std::vector< std::string > &desc) const{
        // This is extra credit :) (Do when finished, if possible)
        return true;
    }
};

CDijkstraTransportationPlanner::CDijkstraTransportationPlanner(std::shared_ptr<SConfiguration> config){
    DImplementation = std::make_unique< SImplementation > (config);
}
CDijkstraTransportationPlanner::~CDijkstraTransportationPlanner(){

}

std::size_t CDijkstraTransportationPlanner::NodeCount() const noexcept{
    return DImplementation->NodeCount();
}

std::shared_ptr<CStreetMap::SNode> CDijkstraTransportationPlanner::SortedNodeByIndex(std::size_t index) const noexcept{
    return DImplementation->SortedNodeByIndex(index);
}

double CDijkstraTransportationPlanner::FindShortestPath(TNodeID src, TNodeID dest, std::vector< TNodeID > &path){
    return DImplementation->FindShortestPath(src, dest, path);
}

double CDijkstraTransportationPlanner::FindFastestPath(TNodeID src, TNodeID dest, std::vector< TTripStep > &path){
    return DImplementation->FindFastestPath(src, dest, path);
}

bool CDijkstraTransportationPlanner::GetPathDescription(const std::vector< TTripStep > &path, std::vector< std::string > &desc) const{
    return DImplementation->GetPathDescription(path, desc);
}
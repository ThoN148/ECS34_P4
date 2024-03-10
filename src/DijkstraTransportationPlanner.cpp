#include "DijkstraTransportationPlanner.h"
#include "DijkstraPathRouter.h"
#include <unordered_map>
#include <vector>

struct CDijkstraTransportationPlanner::SImplementation{
    std::shared_ptr< CStreetMap > DStreetMap;
    std::shared_ptr< CBusSystem > DBusSystem;
    std::unordered_map< CStreetMap::TNodeID, CPathRouter::TVertexID > DNodeToVertexID; 
    CDijkstraPathRouter DShortestPathRouter;
    CDijkstraPathRouter DFastestPathRouterBike;
    CDijkstraPathRouter DFastestPathRouteWalkBus;

	static bool StopIDCompare(std::shared_ptr< CStreetMap::SNode > left, std::shared_ptr< CStreetMap::SNode > right){
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
            bool Bikable = Way->GetAttribute("Bicycle") == "no"; // Or do != "no" either or not really sure what he wants
            bool Bidirectional = Way->GetAttribute("oneway") == "yes"; //same as above do either == or !=
            auto PreviousNodeID = Way->GetNodeID(0);

            for(size_t j = 1; j < Way->NodeCount(); j++){
                auto NextNodeID = Way->GetNodeID(j);
            }
        }
    }

    std::size_t NodeCount() const noexcept{
        return DStreetMap->NodeCount();
    }

    std::shared_ptr<CStreetMap::SNode> SortedNodeByIndex(std::size_t index) const noexcept{
	    std::vector < std::shared_ptr< CStreetMap::SNode > > DSortedStops;

		for (size_t i = 0; i < DStreetMap->NodeCount(); i++){
            auto CurrentStop = DStreetMap->NodeByIndex(i);
			DSortedStops.push_back(CurrentStop);            
        }
        std::sort(DSortedStops.begin(),DSortedStops.end(), StopIDCompare);

        return DSortedStops[index];
    }

    double FindShortestPath(TNodeID src, TNodeID dest, std::vector< TNodeID > &path){
        std::vector< CPathRouter::TVertexID > ShortestPath;
        auto SourceVertexID = DNodeToVertexID[src];
        auto DestinationVertexID = DNodeToVertexID[dest];
        auto Distance = DShortestPathRouter.FindShortestPath(SourceVertexID, DestinationVertexID, ShortestPath);
        path.clear();

        for(auto VertexID :  ShortestPath){
            path.push_back(VertexID);
        }
    }

    double FindFastestPath(TNodeID src, TNodeID dest, std::vector< TTripStep > &path){
        std::vector< CPathRouter::TVertexID > FastestPath;
        auto SourceVertexID = DNodeToVertexID[src];
        auto DestinationVertexID = DNodeToVertexID[dest];
        auto Distance = DShortestPathRouter.FindShortestPath(SourceVertexID, DestinationVertexID, FastestPath);
        path.clear();
    }

    bool GetPathDescription(const std::vector< TTripStep > &path, std::vector< std::string > &desc) const{

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
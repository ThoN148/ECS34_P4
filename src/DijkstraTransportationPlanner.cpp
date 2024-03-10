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

    SImplementation(std::shared_ptr<SConfiguration> config){
        DStreetMap = config->StreetMap();
        DBusSystem = config->BusSystem();

        for(size_t i = 0; i < DStreetMap->NodeCount(); i++){
            auto Node = DStreetMap->NodeByIndex(i);
            auto VertexID = DShortestPathRouter.AddVertex(Node->ID());
            DFastestPathRouterBike.AddVertex(Node->ID());
            DFastestPathRouteWalkBus.AddVertex(Node->ID());
            DNodeToVertexID[(Node->ID())] = VertexID;
        }

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
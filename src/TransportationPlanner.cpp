#include "TransportationPlanner.h"

struct CTransportationPlanner::SConfiguration{

    using TNodeID = CStreetMap::TNodeID;

    enum class ETransportationMode {Walk, Bike, Bus};

    using TTripStep = std::pair<ETransportationMode, TNodeID>;


    std::shared_ptr<CStreetMap> StreetMap() const noexcept{
        
    }
    std::shared_ptr<CBusSystem> BusSystem() const noexcept{
        
    }

    double WalkSpeed() const noexcept{
        
    }

    double BikeSpeed() const noexcept{
        
    }

    double DefaultSpeedLimit() const noexcept{
        
    }

    double BusStopTime() const noexcept{
        
    }
    
    int PrecomputeTime() const noexcept{
        
    }

    std::size_t NodeCount() const noexcept{
        
    }
    std::shared_ptr<CStreetMap::SNode> SortedNodeByIndex(std::size_t index) const noexcept{
        
    }

    double FindShortestPath(TNodeID src, TNodeID dest, std::vector< TNodeID > &path){
        
    }
    double FindFastestPath(TNodeID src, TNodeID dest, std::vector< TTripStep > &path){
        
    }
    bool GetPathDescription(const std::vector< TTripStep > &path, std::vector< std::string > &desc) const{
        
    }
};

CTransportationPlanner::~CTransportationPlanner(){
    
};

std::size_t  CTransportationPlanner::NodeCount() const noexcept{
    
}

std::shared_ptr<CStreetMap::SNode> CTransportationPlanner::SortedNodeByIndex(std::size_t index) const noexcept{
    
}

double CTransportationPlanner::FindShortestPath(TNodeID src, TNodeID dest, std::vector< TNodeID > &path){
    
}

double CTransportationPlanner::FindFastestPath(TNodeID src, TNodeID dest, std::vector< TTripStep > &path){
    
}

bool CTransportationPlanner::GetPathDescription(const std::vector< TTripStep > &path, std::vector< std::string > &desc) const{
    
}
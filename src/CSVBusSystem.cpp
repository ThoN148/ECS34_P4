#include "CSVBusSystem.h"
#include "StringUtils.h"
#include <vector>
#include <unordered_map>
#include <iostream>
#include <algorithm>

struct CCSVBusSystem::SImplementation{

    struct SStop : public CBusSystem::SStop{
        TStopID DStopID;
        CStreetMap::TNodeID DNodeID;

        SStop(TStopID Sid, CStreetMap::TNodeID Nid){
            DStopID = Sid;
            DNodeID = Nid;
        }

        ~SStop(){};

        TStopID ID() const noexcept{
            return DStopID;
        }

        CStreetMap::TNodeID NodeID() const noexcept{
            return DNodeID;
        }
    };

    struct SRoute : public CBusSystem::SRoute{
        TStopID DStopID;
        std::string DName;
        std::vector< TStopID > DRouteStop;

        SRoute(TStopID Sid, std::string name){
            DStopID = Sid;
            DName = name;

            AddStopID(Sid);
        }

        ~SRoute(){};

        std::string Name() const noexcept{
            return DName;
        }

        std::size_t StopCount() const noexcept{
            return DRouteStop.size();
        }

        TStopID GetStopID(std::size_t index) const noexcept{
            if(index < DRouteStop.size()){
                return DRouteStop[index];
            }

            return TStopID();
        }

        void AddStopID(TStopID id){
            DRouteStop.push_back(id);
        }
    };


    std::unordered_map< TStopID , std::shared_ptr< SStop > > DNodeIDToStop;
    std::vector< std::shared_ptr< CBusSystem::SStop > > DStopByIndex;
    std::unordered_map< std::string, std::shared_ptr< SRoute > > DNodeIDToRoute;
    std::vector< std::shared_ptr< CBusSystem::SRoute > > DRouteByIndex;


    SImplementation(std::shared_ptr< CDSVReader > stopsrc, std::shared_ptr< CDSVReader > routesrc){
        std::vector< std::string > VStopsrc;
        std::vector< std::string > VRoutesrc;

        size_t i = 0;

        bool FirstLine = true;

        while(stopsrc->ReadRow(VStopsrc)){

            if(FirstLine == true){
                FirstLine = false;
                continue;
            }

            TStopID NewStopID = std::stoull(VStopsrc[0]);
            CStreetMap::TNodeID NewNodeID = std::stoull(VStopsrc[1]);

            auto NewNode = std::make_shared< SStop >(NewStopID, NewNodeID);
            DStopByIndex.push_back(NewNode);
            DNodeIDToStop[NewNode->ID()] = NewNode;
            i += 2;
        }

        FirstLine = true;

        i = 0;

        while(routesrc->ReadRow(VRoutesrc)){

            if(FirstLine == true){
                FirstLine = false;
                continue;
            }           

            std::string NewName = VRoutesrc[0];
            TStopID NewStopID = std::stoull(VRoutesrc[1]);

            auto Search = DNodeIDToRoute.find(NewName);
            if(DNodeIDToRoute.end() != Search){
                auto route = Search->second;
                route->AddStopID(NewStopID);
            }
            else{
                auto NewNode = std::make_shared< SRoute >(NewStopID, NewName);
                DRouteByIndex.push_back(NewNode);
                DNodeIDToRoute[NewNode->Name()] = NewNode; 
            }
            i += 2;
        }

    }

    std::size_t StopCount() const{
        return DStopByIndex.size();
    }

    std::size_t RouteCount() const{

        if(DRouteByIndex.size() > 0){
            std::vector< std::string > RouteNames;
            int count = 0;
            std::string NewName = DRouteByIndex[0]->Name();
            RouteNames.push_back(NewName);

            for(size_t i = 0; i < DRouteByIndex.size(); i++){
                if(NewName != DRouteByIndex[i]->Name())
                {
                    NewName = DRouteByIndex[i]->Name();
                    RouteNames.push_back(NewName);
                }
            }

            return RouteNames.size();
        }

        return 0;
    }
    
    // Returns the SStop specified by the index, nullptr is returned if index is greater than equal to StopCount()
    std::shared_ptr< CBusSystem::SStop > StopByIndex(std::size_t index) const{
        if(index < StopCount()){
            return DStopByIndex[index];
        }

        return nullptr;
    }
    // Returns the SStop specified by the stop id, nullptr is returned if id is not in the stops
    std::shared_ptr< CBusSystem::SStop > StopByID(TStopID id) const{
        auto Search = DNodeIDToStop.find(id);

        if(DNodeIDToStop.end() != Search){
            return Search->second;
        }

        return nullptr;
    }
    // Returns the SRoute specified by the index, nullptr is returned if index is greater than equal to RouteCount()
    std::shared_ptr< CBusSystem::SRoute > RouteByIndex(std::size_t index) const{
        if(index < RouteCount()){
            return DRouteByIndex[index];
        }

        return nullptr;
    }

    // Returns the SRoute specified by the name, nullptr is returned if name is not in the routes
    std::shared_ptr< CBusSystem::SRoute > RouteByName(const std::string &name) const{
        auto Search = DNodeIDToRoute.find(name);
        if(DNodeIDToRoute.end() != Search){
            return Search->second;
        }

        return nullptr;
    }
};

CCSVBusSystem::CCSVBusSystem(std::shared_ptr< CDSVReader > stopsrc, std::shared_ptr< CDSVReader > routesrc){
    DImplementation = std::make_unique< SImplementation >(stopsrc, routesrc);
}

CCSVBusSystem::~CCSVBusSystem() {};


std::size_t CCSVBusSystem::StopCount() const noexcept{
    return DImplementation->StopCount();
}

std::size_t CCSVBusSystem::RouteCount() const noexcept{
    return DImplementation->RouteCount();
}

std::shared_ptr< CBusSystem::SStop > CCSVBusSystem::StopByIndex(std::size_t index) const noexcept{
    return DImplementation->StopByIndex(index);
}

std::shared_ptr< CBusSystem::SStop > CCSVBusSystem::StopByID(TStopID id) const noexcept{
    return DImplementation->StopByID(id);
}

std::shared_ptr< CBusSystem::SRoute > CCSVBusSystem::RouteByIndex(std::size_t index) const noexcept{
    return DImplementation->RouteByIndex(index);
}

std::shared_ptr< CBusSystem::SRoute > CCSVBusSystem::RouteByName(const std::string &name) const noexcept{
    return DImplementation->RouteByName(name);
}
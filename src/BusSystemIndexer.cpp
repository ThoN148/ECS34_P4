#include "BusSystemIndexer.h"
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <iostream>

struct CBusSystemIndexer::SImplementation{

    struct pair_hash {
        template <class T1, class T2>
        std::size_t operator () (const std::pair<T1,T2> &p) const {
            auto h1 = std::hash<T1>{}(p.first);
            auto h2 = std::hash<T2>{}(p.second);

            return h1 ^ h2;  
        }
    };

	std::shared_ptr< CBusSystem > DBusSystem;
    std::vector < std::shared_ptr< SStop > > DSortedStops;
	std::vector < std::shared_ptr< SRoute > > DSortedRoutes; 
	std::unordered_map < TNodeID, std::shared_ptr< SStop > > DNodeIDToStop;
	std::unordered_map< std::pair< TNodeID, TNodeID >, std::unordered_set< std::shared_ptr< SRoute > >, pair_hash > DSrcDestToRoutes;
	
	// A Compare statement so that we can sort out the stop ids and the route names correctly
	static bool StopIDCompare(std::shared_ptr< SStop > left, std::shared_ptr< SStop > right){
        return left->ID() < right->ID();
    }
	static bool RouteNameCompare(std::shared_ptr< SRoute > left, std::shared_ptr< SRoute > right){
		return left->Name() < right->Name();
	}
	

	SImplementation(std::shared_ptr< CBusSystem > bussystem){
		DBusSystem = bussystem;
		
		// Adds the stops to our vector so that we can then sort them
		for (size_t i = 0; i < DBusSystem->StopCount(); i++){
            auto CurrentStop = DBusSystem->StopByIndex(i);
			DSortedStops.push_back(CurrentStop);
			DNodeIDToStop[CurrentStop->NodeID()] = CurrentStop;
            
        }
        std::sort(DSortedStops.begin(),DSortedStops.end(), StopIDCompare);

		// Adds the routes names to our vector so that we can sort them
    	for (size_t i = 0; i < DBusSystem->RouteCount(); i++){
            auto CurrentRoute = DBusSystem->RouteByIndex(i);
			DSortedRoutes.push_back(CurrentRoute);
            
			// For every current route we get the source its from, the destination then we pair them up
			// Once we get the pair, we search if its in our system already, if not we add it else we just add the current route
     	    for (size_t j = 1; j < CurrentRoute->StopCount(); j++){

				auto SourceNodeID = DBusSystem->StopByID(CurrentRoute->GetStopID(j-1))->NodeID();
                auto DestinationNodeID = DBusSystem->StopByID(CurrentRoute->GetStopID(j))->NodeID();
				auto SearchKey = std::make_pair(SourceNodeID, DestinationNodeID);
				auto Search = DSrcDestToRoutes.find(SearchKey);

				if (Search != DSrcDestToRoutes.end()){
					Search->second.insert(CurrentRoute);
				}
				else{
					DSrcDestToRoutes[SearchKey] = {CurrentRoute};
				}
            }
        }

		// sort out the route names
		std::sort(DSortedRoutes.begin(), DSortedRoutes.end(), RouteNameCompare);
	};
	
	// Returns the number of stops in the CBusSystem being indexed
    std::size_t StopCount() const noexcept{
        return DBusSystem->StopCount();
    }
	// Returns the number of routes in the CBusSystem being indexed
	std::size_t RouteCount() const noexcept{
		return DBusSystem->RouteCount();
	}

	// Returns the SStop specified by the index where the stops are sorted by their ID
	// nullptr is returned if index is greater than equal to StopCount()
	std::shared_ptr<SStop> SortedStopByIndex(std::size_t index) const noexcept{
		if (index < DSortedStops.size()){
			return DSortedStops[index];
		}
		return nullptr;
	}


	// Returns the SRoute specified by the index where the routes are sorted by their Name
	// nullptr is returned if index is greater than equal to RouteCount()
	std::shared_ptr<SRoute> SortedRouteByIndex(std::size_t index) const noexcept{
		if (index < DSortedRoutes.size()){
			return DSortedRoutes[index];
		}
		return nullptr;
	}

	// Returns the SStop associated with the specified node ID
	// nullptr is returned if no SStop associated with the node ID exists
	std::shared_ptr<SStop> StopByNodeID(TNodeID id) const noexcept{
        auto Search = DNodeIDToStop.find(id);
		if (Search != DNodeIDToStop.end()){
			return Search->second;
		}
		return nullptr;
	}

	// Returns true if at least one route exists between the stops at the src and dest node IDs.
	// All routes that have a route segment between the stops at the src and dest nodes will be placed in routes unordered set.
	bool RoutesByNodeIDs(TNodeID src, TNodeID dest, std::unordered_set<std::shared_ptr<SRoute> > &routes) const noexcept{
		auto SearchKey = std::make_pair(src, dest);
		auto Search = DSrcDestToRoutes.find(SearchKey);
		if (Search != DSrcDestToRoutes.end()){
			routes = Search->second;
			return true;
		}
		return false;
	}

	// Returns true if at least one route exists between the stops at the src and dest node IDs.
	bool RouteBetweenNodeIDs(TNodeID src, TNodeID dest) const noexcept{
		auto SearchKey = std::make_pair(src, dest);
		auto Search = DSrcDestToRoutes.find(SearchKey);
		return Search != DSrcDestToRoutes.end();
	}
};



CBusSystemIndexer::CBusSystemIndexer(std::shared_ptr<CBusSystem> bussystem){
    DImplementation = std::make_unique< SImplementation >(bussystem);
}
CBusSystemIndexer::~CBusSystemIndexer(){

}

std::size_t CBusSystemIndexer::StopCount() const noexcept{
	return DImplementation->StopCount();
}
std::size_t CBusSystemIndexer::RouteCount() const noexcept{
    return DImplementation->RouteCount();
}
std::shared_ptr<CBusSystem::SStop> CBusSystemIndexer::SortedStopByIndex(std::size_t index) const noexcept{
	return DImplementation->SortedStopByIndex(index);
}
std::shared_ptr<CBusSystem::SRoute> CBusSystemIndexer::SortedRouteByIndex(std::size_t index) const noexcept{
	return DImplementation->SortedRouteByIndex(index);
}
std::shared_ptr<CBusSystem::SStop> CBusSystemIndexer::StopByNodeID(TNodeID id) const noexcept{
	return DImplementation->StopByNodeID(id);
}
bool CBusSystemIndexer::RoutesByNodeIDs(TNodeID src, TNodeID dest, std::unordered_set<std::shared_ptr<SRoute> > &routes) const noexcept{
	return DImplementation->RoutesByNodeIDs(src, dest, routes);
}
bool CBusSystemIndexer::RouteBetweenNodeIDs(TNodeID src, TNodeID dest) const noexcept{
	return DImplementation->RouteBetweenNodeIDs(src,dest);
}

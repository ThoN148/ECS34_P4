#include "DijkstraPathRouter.h"
#include <vector>
#include <algorithm>
#include <iostream>

struct CDijkstraPathRouter::SImplementation{
    using TEdge = std::pair< double , TVertexID >;

    struct SVertex{
        std::any DTag;
        std::vector< TEdge > DEdges;
    };
    
    std::vector< SVertex > DVerticies;

    // Returns the number of vertices in the path router
    std::size_t VertexCount() const noexcept{
        return DVerticies.size();
    };

    // Adds a vertex with the tag provided. The tag can be of any type.
    TVertexID AddVertex(std::any tag) noexcept{
        TVertexID NewVertexID = DVerticies.size();
        DVerticies.push_back({tag,{}});
        return NewVertexID;
    };

    // Gets the tag of the vertex specified by id if id is in the path router.
    // A std::any() is returned if id is not a valid vertex ID.
    std::any GetVertexTag(TVertexID id) const noexcept{
        if(id < DVerticies.size()){
            return DVerticies[id].DTag;
        }

        return std::any();
    }

    // Adds an edge between src and dest vertices with a weight of weight.
    // If bidir is set to true an additional edge between dest and src is added.
    // If src or dest nodes do not exist, or if the weight is negative the AddEdge will return false, otherwise it returns true.
    bool AddEdge(TVertexID src, TVertexID dest, double weight, bool bidir = false) noexcept{
        if((src < DVerticies.size()) && (dest < DVerticies.size()) && (0.0 <= weight)){
            DVerticies[src].DEdges.push_back(std::make_pair(weight,dest));

            if(bidir){
                DVerticies[dest].DEdges.push_back(std::make_pair(weight, src));
            }
            return true;

        }
        return false;
    }

    // Extra Credit?
    // Allows the path router to do any desired precomputation up to the deadline
    bool Precompute(std::chrono::steady_clock::time_point deadline) noexcept{
        return true;
    }

    // Returns the path distance of the path from src to dest, and fills out path with vertices.
    // If no path exists NoPathExists is returned.
    double FindShortestPath(TVertexID src, TVertexID dest, std::vector<TVertexID>& path) noexcept {
        std::vector< TVertexID > PendingVertices;
        std::vector< double > Distances(DVerticies.size(), CPathRouter::NoPathExists);
        std::vector< double > Previous(DVerticies.size(), CPathRouter::InvalidVertexID);
        auto VertexCompare = [&Distances] (TVertexID left, TVertexID right) {return Distances[left] < Distances[right];};

        Distances[src] = 0.0;
        PendingVertices.push_back(src);

        // While the vertices that are waiting is full
        while (!PendingVertices.empty()){
            auto CurrentID = PendingVertices.front(); 
            std::pop_heap(PendingVertices.begin(), PendingVertices.end());
            PendingVertices.pop_back();

            // For all of the edges within that current vertices' ID
            // We get the weight of the edge, the destination ID, then the total distance
            for (auto edge: DVerticies[CurrentID].DEdges){
                auto EdgeWeight = edge.first;
                auto DestID = edge.second;
                auto TotalDistance = Distances[CurrentID] + EdgeWeight;

                // If the totial distance is less than the distances of the destination ID
                // Check if the the Distance has no path, if not push it
                // Updates the informations for distances, and previous node
                if (TotalDistance < Distances[DestID]){
                    if(CPathRouter::NoPathExists == Distances[DestID]){
                        PendingVertices.push_back(DestID);
                    }
                    Distances[DestID] = TotalDistance;
                    Previous[DestID] = CurrentID;
                }
            }

            // Creates a heap with the pending vertices
            std::make_heap(PendingVertices.begin(), PendingVertices.end(), VertexCompare);
        }

        // if the distance doesnt have a path then return no path exists
        if(CPathRouter::NoPathExists == Distances[dest]){
            return CPathRouter::NoPathExists;
        }

        // Creates the distance that we'll return
        double PathDistance = Distances[dest];

        // Clean Slate / Reset
        path.clear();
        path.push_back(dest);

        // While the dest isnt the same as src, then we would push the dest to path and update it to the previous node
        // So like taeks whatever is at the end of the vector, adds to path then we'd reverse it
        do{
            dest = Previous[dest];
            path.push_back(dest);
        }while (dest != src);
        std::reverse(path.begin(), path.end());

        return PathDistance;       
    }

};

CDijkstraPathRouter::CDijkstraPathRouter(){
    DImplementation = std::make_unique< SImplementation >();
}

CDijkstraPathRouter::~CDijkstraPathRouter(){

}

std::size_t CDijkstraPathRouter::VertexCount() const noexcept{
    return DImplementation->VertexCount();
}

CPathRouter::TVertexID CDijkstraPathRouter::AddVertex(std::any tag) noexcept{
    return DImplementation->AddVertex(tag);
}

std::any CDijkstraPathRouter::GetVertexTag(TVertexID id) const noexcept{
    return DImplementation->GetVertexTag(id);
}

bool CDijkstraPathRouter::AddEdge(TVertexID src, TVertexID dest, double weight, bool bidir) noexcept{
    return DImplementation->AddEdge(src, dest, weight, bidir);
}

bool CDijkstraPathRouter::Precompute(std::chrono::steady_clock::time_point deadline) noexcept{
    return DImplementation->Precompute(deadline);
}

double CDijkstraPathRouter::FindShortestPath(TVertexID src, TVertexID dest, std::vector<TVertexID> &path) noexcept{
    return DImplementation->FindShortestPath(src, dest, path);
}
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

    std::size_t VertexCount() const noexcept{
        return DVerticies.size();
    };

    TVertexID AddVertex(std::any tag) noexcept{
        TVertexID NewVertexID = DVerticies.size();
        DVerticies.push_back({tag,{}});
        return NewVertexID;
    };

    std::any GetVertexTag(TVertexID id) const noexcept{
        if(id < DVerticies.size()){
            return DVerticies[id].DTag;
        }

        return std::any();
    }

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

    bool Precompute(std::chrono::steady_clock::time_point deadline) noexcept{
        return true;
    }

    double FindShortestPath(TVertexID src, TVertexID dest, std::vector<TVertexID>& path) noexcept {
        std::vector<TVertexID> PendingVertices;
        std::vector<double> Distances(DVerticies.size(), CPathRouter::NoPathExists);
        std::vector<double> Previous(DVerticies.size(), CPathRouter::InvalidVertexID);
        auto VertexCompare = [&Distances] (TVertexID left, TVertexID right) {return Distances[left] < Distances[right];};

        Distances[src] = 0.0;
        PendingVertices.push_back(src);

        while (!PendingVertices.empty()){
            auto CurrentID = PendingVertices.front(); 
            std::pop_heap(PendingVertices.begin(), PendingVertices.end());
            PendingVertices.pop_back();
            // make faster if currentID is == to dest
            // add if and break here
            for (auto edge: DVerticies[CurrentID].DEdges){
                auto EdgeWeight = edge.first;
                auto DestID = edge.second;
                auto TotalDistance = Distances[CurrentID] + EdgeWeight;
                if (TotalDistance < Distances[DestID]){
                    if(CPathRouter::NoPathExists == Distances[DestID]){
                        PendingVertices.push_back(DestID);
                    }
                    Distances[DestID] = TotalDistance;
                    Previous[DestID] = CurrentID;
                }
            }
            std::make_heap(PendingVertices.begin(), PendingVertices.end(), VertexCompare);
        }
        if(CPathRouter::NoPathExists == Distances[dest]){
            return CPathRouter::NoPathExists;
        }

        double PathDistance = Distances[dest];
        path.clear();
        path.push_back(dest);
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
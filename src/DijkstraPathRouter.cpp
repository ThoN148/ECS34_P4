#include "DijkstraPathRouter.h"
#include <vector>
#include <algorithm>

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
            return true;
        }
        return false;
    }

    bool Precompute(std::chrono::steady_clock::time_point deadline) noexcept{
        return true;
    }

    double FindShortestPath(TVertexID src, TVertexID dest, std::vector<TVertexID> &path) noexcept{
        std::vector< TVertexID > PendingVerticies;
        std::vector< TVertexID > Previous(DVerticies.size(), CPathRouter::InvalidVertexID);
        std::vector< double > Distances(DVerticies.size(), CPathRouter::NoPathExists);
        auto VertexCompare = [&Distances](TVertexID left, TVertexID right){return Distances[left] < Distances[right];};

        Distances[src] = 0.0;
        PendingVerticies.push_back(src);
        while(!PendingVerticies.empty()){
            auto CurrentID = PendingVerticies.front();
            std::pop_heap(PendingVerticies.begin(), PendingVerticies.end());
            PendingVerticies.pop_back();

            for(auto Edge : DVerticies[CurrentID].DEdges){
                auto EdgeWeight = Edge.first;
                auto DestID = Edge.second;
                auto TotalDistance = Distances[CurrentID] + EdgeWeight;
                if(TotalDistance < Distances[DestID]){
                    if(CPathRouter::NoPathExists == Distances[DestID]){
                        PendingVerticies.push_back(DestID);
                    }

                    Distances[DestID] = TotalDistance;
                    Previous[DestID] = CurrentID;

                }
            }
            std::make_heap(PendingVerticies.begin(), PendingVerticies.end(), VertexCompare);
        }
        if(CPathRouter::NoPathExists == Distances[dest]){
            return CPathRouter::NoPathExists;
        }
        double PathDistance = 0.0;
        path.clear();
        do{
            path.push_back(dest);
            dest = Previous[dest];
        }while(dest != src);

        std::reverse(path.begin(), path.end());
        return PathDistance;
    }
};

CDijkstraPathRouter::CDijkstraPathRouter(){

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
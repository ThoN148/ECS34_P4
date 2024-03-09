#include "OpenStreetMap.h"
#include <unordered_map>
#include <vector>
#include <iostream>

struct COpenStreetMap::SImplementation{

    struct SNode : public CStreetMap::SNode{
        TNodeID DID;
        TLocation DLoc;
        
        std::unordered_map< std::string, std::string > DAttributes;
        std::vector< std::string > DAttributeKeys;

        SNode(TNodeID id, TLocation loc){
            DID = id;
            DLoc = loc;
        }

        ~SNode(){}
        
        TNodeID ID() const noexcept override{
            return DID;
        }
        
        TLocation Location() const noexcept override{
            return DLoc;
        }
        
        std::size_t AttributeCount() const noexcept override{
            return DAttributeKeys.size();
        }
        
        std::string GetAttributeKey(std::size_t index) const noexcept override{
            if(index < DAttributeKeys.size()){
                return DAttributeKeys[index];
            }

            return std::string();
        }
        
        bool HasAttribute(const std::string &key) const noexcept override{
            auto Search = DAttributes.find(key);
            return DAttributes.end() != Search;
        }
        
        std::string GetAttribute(const std::string &key) const noexcept override{
            auto Search = DAttributes.find(key);
            if (DAttributes.end() != Search){
                return Search -> second;
            }
            return std::string();
        }

        void SetAttributes(const std::string &key, const std::string &value){
            DAttributeKeys.push_back(key);
            DAttributes[key] = value;
        }
    };

    struct SWay : public CStreetMap::SWay{
        TWayID DID;
        std::vector< TNodeID > DNodeID;
        std::unordered_map< std::string, std::string > DAttributes;
        std::vector< std::string > DAttributeKeys;

        SWay(TWayID id){
            DID = id;
        }
        
        ~SWay(){}

        TWayID ID() const noexcept override{
            return DID;
        }

        std::size_t NodeCount() const noexcept override{
            return DNodeID.size();
        }

        TNodeID GetNodeID(std::size_t index) const noexcept override{
            if(index < DNodeID.size()){
                return DNodeID[index];
            }
            return TNodeID();
        }

        std::size_t AttributeCount() const noexcept override{
            return DAttributeKeys.size();
        }

        std::string GetAttributeKey(std::size_t index) const noexcept override{
            if(index < DAttributeKeys.size()){
                return DAttributeKeys[index];
            }

            return std::string();
        }

        bool HasAttribute(const std::string &key) const noexcept override{
            auto Search = DAttributes.find(key);
            return DAttributes.end() != Search;          
        }

        std::string GetAttribute(const std::string &key) const noexcept override{
            auto Search = DAttributes.find(key);
            if (DAttributes.end() != Search){
                return Search -> second;
            }
            return std::string();
        }

        void SetAttributes(const std::string &key, const std::string &value){
            DAttributeKeys.push_back(key);
            DAttributes[key] = value;
        }

        void AddNodeID(const TNodeID id){
            DNodeID.push_back(id);
        }
    };

    std::unordered_map< TNodeID, std::shared_ptr< SNode > > DNodeIDToNode;
    std::vector< std::shared_ptr < SNode > > DNodesByIndex;

    std::unordered_map< TNodeID, std::shared_ptr< SNode > > DWayIDToNode;
    std::vector< std::shared_ptr < SNode > > DWayByIndex;

    std::unordered_map< TNodeID, std::shared_ptr< SWay > > DNodeIDToWay;
    std::vector< std::shared_ptr < SWay > > DNodesByIndexW;

    SImplementation(std::shared_ptr<CXMLReader> src){

        SXMLEntity TemptEntity;

        while(src->ReadEntity(TemptEntity, true)){
            if((TemptEntity.DNameData == "osm") && (SXMLEntity::EType::EndElement == TemptEntity.DType)){
                // Reaches end
                break;
            }
            else if ((TemptEntity.DNameData == "node") && (SXMLEntity::EType::StartElement == TemptEntity.DType)){
                // Parse node
                TNodeID NewNodeID = std::stoull(TemptEntity.AttributeValue("id"));
                double Lat = std::stod(TemptEntity.AttributeValue("lat"));
                double Lon = std::stod(TemptEntity.AttributeValue("lon"));

                TLocation NewNodeLocation = std::make_pair(Lat,Lon);

                // Creates new node that gets pushed into the map
                auto NewNode = std::make_shared<SNode>(NewNodeID, NewNodeLocation);
                DNodesByIndex.push_back(NewNode);
                DNodeIDToNode[NewNodeID] = NewNode;

                while(src->ReadEntity(TemptEntity, true)){
                    if((TemptEntity.DNameData == "node") && (SXMLEntity::EType::EndElement == TemptEntity.DType)){
                        break;
                    }
                    else if((TemptEntity.DNameData == "tag") && (SXMLEntity::EType::StartElement == TemptEntity.DType)){
                        NewNode->SetAttributes(TemptEntity.AttributeValue("k"), TemptEntity.AttributeValue("v"));
                    }
                }

            }
            else if ((TemptEntity.DNameData == "way") && (SXMLEntity::EType::StartElement == TemptEntity.DType)){
                // Parse node
                TWayID NewWayID = std::stoull(TemptEntity.AttributeValue("id"));

                // Creates a new node that gets pushed into the Way map
                auto NewNode = std::make_shared< SWay >(NewWayID);
                DNodesByIndexW.push_back(NewNode);
                DNodeIDToWay[NewWayID] = NewNode;


                while(src->ReadEntity(TemptEntity, true)){
                    if((TemptEntity.DNameData == "way") && (SXMLEntity::EType::EndElement == TemptEntity.DType)){
                        break;
                    }
                    else if((TemptEntity.DNameData == "nd") && (SXMLEntity::EType::StartElement == TemptEntity.DType)){
                        TNodeID NewWayNodeID = std::stoull(TemptEntity.AttributeValue("ref"));
                        NewNode->AddNodeID(NewWayNodeID);                       
                    }
                    else if((TemptEntity.DNameData == "tag") && (SXMLEntity::EType::StartElement == TemptEntity.DType)){
                        NewNode->SetAttributes(TemptEntity.AttributeValue("k"), TemptEntity.AttributeValue("v"));
                    }
                }

            }

        }
    }

    std::size_t NodeCount() const{
        return DNodesByIndex.size();
    }

    std::size_t WayCount() const{
        return DNodeIDToWay.size();
    }

    std::shared_ptr<CStreetMap::SNode> NodeByIndex(std::size_t index) const{
        if(index < DNodesByIndex.size()){
            return DNodesByIndex[index];
        }

        return nullptr;
    }

    std::shared_ptr<CStreetMap::SNode> NodeByID(TNodeID id) const{
        auto Search = DNodeIDToNode.find(id);
        if(DNodeIDToNode.end() != Search){
            return Search->second;
        }

        return nullptr;
    }

    std::shared_ptr<CStreetMap::SWay> WayByIndex(std::size_t index) const{
        if(index < DNodesByIndexW.size()){
            return DNodesByIndexW[index];
        }

        return nullptr;
    }

    std::shared_ptr<CStreetMap::SWay> WayByID(TWayID id) const{
        auto Search = DNodeIDToWay.find(id);
        if(DNodeIDToWay.end() != Search){
            return Search->second;
        }

        return nullptr;
    }
};

COpenStreetMap::COpenStreetMap(std::shared_ptr<CXMLReader> src){
DImplementation = std::make_unique<SImplementation>(src);
}

COpenStreetMap::~COpenStreetMap(){
}

std::size_t COpenStreetMap::NodeCount() const noexcept{
return DImplementation->NodeCount();
}

std::size_t COpenStreetMap::WayCount() const noexcept{
return DImplementation->WayCount();
}

std::shared_ptr<CStreetMap::SNode> COpenStreetMap::NodeByIndex(std::size_t index) const noexcept{
return DImplementation->NodeByIndex(index);
}

std::shared_ptr<CStreetMap::SNode> COpenStreetMap::NodeByID(TNodeID id) const noexcept{
return DImplementation->NodeByID(id);
}

std::shared_ptr<CStreetMap::SWay> COpenStreetMap::WayByIndex(std::size_t index) const noexcept{
return DImplementation->WayByIndex(index);
}

std::shared_ptr<CStreetMap::SWay> COpenStreetMap::WayByID(TWayID id) const noexcept{
return DImplementation->WayByID(id);
}
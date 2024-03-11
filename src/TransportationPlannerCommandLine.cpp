#include "TransportationPlannerCommandLine.h"
#include "StringUtils.h"
#include "GeographicUtils.h"
#include "DSVReader.h"
#include <algorithm>
#include <iostream>

struct CTransportationPlannerCommandLine::SImplementation{

    // Setting up variables
    std::shared_ptr<CDataSource> DCmdSrc; // Command source
    std::shared_ptr<CDataSink> DOutSink;  // Output sink
    std::shared_ptr<CDataSink> DErrSink;  // Error sink
    std::shared_ptr<CDataFactory> DResults; // Data factory for results
    std::shared_ptr<CTransportationPlanner> DPlanner; // Transportation planner

    SImplementation(std::shared_ptr<CDataSource> cmdsrc, std::shared_ptr<CDataSink> outsink, std::shared_ptr<CDataSink> errsink, std::shared_ptr<CDataFactory> results, std::shared_ptr<CTransportationPlanner> planner){
        DCmdSrc = cmdsrc;
        DOutSink = outsink;
        DErrSink = errsink;
        DResults = results;
        DPlanner = planner;
    }
    
    bool ProcessCommands(){
        std::string Read_Command;
        std::string Command_Output;
        std::string Error_Output;
        while(true){

            CDSVReader Command(DCmdSrc, '\n');
            std::vector<std::string> StringVector;

            Command.ReadRow(StringVector);

            for(int i = 0;i < StringVector.size(); i++){
                std::cout << StringVector[i] << "\n";

                if(StringVector[i] == "help"){
                    //
                    Command_Output += "> ";

                    Command_Output += "------------------------------------------------------------------------\n"
                                    "help     Display this help menu\n"
                                    "exit     Exit the program\n"
                                    "count    Output the number of nodes in the map\n"
                                    "node     Syntax \"node [0, count)\" \n"
                                    "         Will output node ID and Lat/Lon for node\n"
                                    "fastest  Syntax \"fastest start end\" \n"
                                    "         Calculates the time for fastest path from start to end\n"
                                    "shortest Syntax \"shortest start end\" \n"
                                    "         Calculates the distance for the shortest path from start to end\n"
                                    "save     Saves the last calculated path to file\n"
                                    "print    Prints the steps for the last calculated path\n";
                }
                if(StringVector[i] == "count"){
                    //
                    Command_Output += "> ";

                    int NodeCount = DPlanner->NodeCount();
                    std::string NCString = std::to_string(NodeCount);
                    Command_Output += NCString + " nodes\n";
                }
                if(StringVector[i].substr(0,4) == "node"){
                    Command_Output += "> ";
                    // check if there nodes and if they exist
                    if(StringVector[i].size() == 4){
                        break;
                    }

                    // If node exists
                    auto TempString = StringVector[i].substr(4);
                    //std::cout << "TempString:" << TempString << "\n";
                    auto NodeID = StringUtils::Split(StringUtils::Strip(TempString));
                    
                    auto Node = DPlanner->SortedNodeByIndex(std::stoi(NodeID[0]));
                    auto Location = Node->Location();

                    // "Node 0: id = 1234 is at 38d 36' 0\" N, 121d 46' 48\" W\n"
                    // Degree, Minutes, Seconds
                    // Degree is the Locations
                    // Minutes is distance

                    // Converts the locations properly - ASSISTED
                    int Lat_Deg = Location.first;
                    int Lat_Min = static_cast< int > ((Location.first - Lat_Deg) * 60);
                    int Lat_Sec = static_cast< int > (((Location.first - Lat_Deg) * 60 - Lat_Min) * 60);

                    int Lon_Deg = static_cast< int > (std::abs(Location.second));
                    int Lon_Min = static_cast< int > ((std::abs(Location.second) - Lon_Deg) * 60);
                    int Lon_Sec = static_cast< int > (((std::abs(Location.second) - Lon_Deg) * 60 - Lon_Min) * 60);
                    
                    std::string lat_str = std::to_string(Lat_Deg) + "d " + std::to_string(Lat_Min) + "' " + std::to_string(Lat_Sec) + "\" N";
                    std::string lon_str = std::to_string(Lon_Deg) + "d " + std::to_string(Lon_Min) + "' " + std::to_string(Lon_Sec) + "\" " + (Location.second < 0 ? "W" : "E"); // Use "W" for negative longitudes and "E" for positive

                    Command_Output += "Node " + NodeID[0] + ": id = " + std::to_string(Node->ID()) + " is at " + lat_str + ", " + lon_str + "\n";
                }
                if(StringVector[i].substr(0,8) == "shortest"){
                    //Checks for inputs
                    if(StringVector[i].size() == 8){
                        break;
                    }
                    Command_Output += "> ";
                    


                }
                if(StringVector[i] == "exit"){
                    Command_Output += "> ";
                    break;
                }
            }

            if(StringVector[0] == "exit"){
                break;
            }
        }

        DOutSink->Write(std::vector<char>(Command_Output.begin(), Command_Output.end()));
        DErrSink->Write(std::vector<char>(Error_Output.begin(), Error_Output.end()));
        return true;
    }
};

CTransportationPlannerCommandLine::CTransportationPlannerCommandLine(std::shared_ptr<CDataSource> cmdsrc, std::shared_ptr<CDataSink> outsink, std::shared_ptr<CDataSink> errsink, std::shared_ptr<CDataFactory> results, std::shared_ptr<CTransportationPlanner> planner){
    DImplementation = std::make_unique< SImplementation > (cmdsrc, outsink, errsink, results, planner);
}

CTransportationPlannerCommandLine::~CTransportationPlannerCommandLine(){

}

bool CTransportationPlannerCommandLine::ProcessCommands(){
    return DImplementation->ProcessCommands();
}
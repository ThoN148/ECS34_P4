#include "TransportationPlannerCommandLine.h"
#include "StringUtils.h"
#include "GeographicUtils.h"
#include "DijkstraPathRouter.h"
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
    
    // AI Generated!!!
    // Prompt 1 - How can I calculate the minutes and second with a given location of latitude and longitude? 
    void decimalToDMS(double decimal, int& degrees, int& minutes, int& seconds) {
        // Extract the degrees
        degrees = static_cast<int>(decimal);

        // Calculate the remaining fractional part
        double fractionalPart = std::abs(decimal - degrees);

        // Convert the fractional part to minutes (60 minutes in a degree)
        double minutesDecimal = fractionalPart * 60;

        // Extract the minutes
        minutes = static_cast<int>(minutesDecimal);

        // Calculate the remaining fractional part for seconds
        double secondsDecimal = (minutesDecimal - minutes) * 60;

        // Round to the nearest integer for seconds
        seconds = static_cast<int>(secondsDecimal + 0.5); // Adding 0.5 for proper rounding
    }

    bool ProcessCommands(){
        std::string Read_Command;
        std::string Command_Output;
        std::string Error_Output;
        bool Numeric = true;
        while(true){

            CDSVReader Command(DCmdSrc, '\n');
            std::vector<std::string> StringVector;

            Command.ReadRow(StringVector);

            for(int i = 0;i < StringVector.size(); i++){
                std::vector < std::string > WordList = {"help", "exit", "count", "node", "fastest", "shortest", "save", "print"};
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
                else if(StringVector[i] == "count"){
                    //
                    Command_Output += "> ";

                    int NodeCount = DPlanner->NodeCount();
                    std::string NCString = std::to_string(NodeCount);
                    Command_Output += NCString + " nodes\n";
                }
                else if(StringVector[i].substr(0,4) == "node"){
                    Command_Output += "> ";
                    // check if there nodes and if they exist
                    if(StringVector[i].size() == 4){
                        Error_Output += "Invalid node command, see help.\n";
                        break;
                    }

                    // If node exists
                    auto TempString = StringVector[i].substr(4);
                    auto NodeID = StringUtils::Split(StringUtils::Strip(TempString));

                    // Checks if the input are all numbers, is not then it breaks off the code
                    for(int i = 0; i < NodeID.size(); i++){
                        for(char c : NodeID[i]){
                            if (!std::isdigit(c)) {
                                //std::cout << c << "\n";
                                Numeric = false;
                            }
                        }
                    }

                    if(Numeric == false){
                        Numeric = true;
                        Error_Output += "Invalid node parameter, see help.\n";
                        break;
                    }

                    auto Node = DPlanner->SortedNodeByIndex(std::stoi(NodeID[0]));
                    auto Location = Node->Location();

                    // "Node 0: id = 1234 is at 38d 36' 0\" N, 121d 46' 48\" W\n"
                    // Degree, Minutes, Seconds
                    // Degree is the Locations
                    // Minutes is distance

                    // AI Generated!!!
                    // Prompt 1 - How can I calculate the minutes and second with a given location of latitude and longitude?  
                    int LatDeg, LatMin, LatSec;
                    int LonDeg, LonMin, LonSec;
                    std::string LatDirection, LonDirection;

                    decimalToDMS(Location.first, LatDeg, LatMin, LatSec);
                    decimalToDMS(Location.second, LonDeg, LonMin, LonSec);

                    if(LatDeg < 0){
                        LatDirection = "S";
                    }
                    else{
                        LatDirection = "N";
                    }

                    if(LonDeg < 0){
                        LonDirection = "W";
                    }
                    else{
                        LonDirection = "E";
                    }

                    LatDeg = std::abs(LatDeg);
                    LonDeg = std::abs(LonDeg);

                    std::string lat_str = std::to_string(LatDeg) + "d " + std::to_string(LatMin) + "' " + std::to_string(LatSec) + "\" " + LatDirection;
                    std::string lon_str = std::to_string(LonDeg) + "d " + std::to_string(LonMin) + "' " + std::to_string(LonSec) + "\" " + LonDirection;

                    Command_Output += "Node " + NodeID[0] + ": id = " + std::to_string(Node->ID()) + " is at " + lat_str + ", " + lon_str + "\n";
                }
                else if(StringVector[i].substr(0,8) == "shortest"){
                    //Checks for inputs
                    Command_Output += "> ";

                    if(StringVector[i].size() == 8){
                        Error_Output += "Invalid shortest command, see help.\n";
                        break;
                    }

                    auto TempString = StringVector[i].substr(8);
                    auto InputVector = StringUtils::Split(StringUtils::Strip(TempString));
                    auto SrcNode = InputVector[0];
                    auto DestNode = InputVector[1];


                    // Checks if the input are all numbers, is not then it breaks off the code
                    for(int i = 0; i < InputVector.size(); i++){
                        for(char c : InputVector[i]){
                            if (!std::isdigit(c)) {
                                //std::cout << c << "\n";
                                Numeric = false;
                            }

                        }
                    }

                    if(Numeric == false){
                        Numeric = true;
                        Error_Output += "Invalid shortest parameter, see help.\n";
                        break;
                    }

                    std::vector< CTransportationPlanner::TNodeID > Route;

                    auto Time = DPlanner->FindShortestPath(std::stoi(SrcNode), std::stoi(DestNode), Route);
                    std::string TimeString = std::to_string(Time).substr(0,3);

                    Command_Output += "Shortest path is " + TimeString + " mi.\n";
                }
                else if(StringVector[i].substr(0,7) == "fastest"){
                    //Checks for inputs
                    Command_Output += "> ";

                    if(StringVector[i].size() == 7){
                        Error_Output += "Invalid fastest command, see help.\n";
                        break;
                    }
                    
                    auto TempString = StringVector[i].substr(7);
                    auto InputVector = StringUtils::Split(StringUtils::Strip(TempString));
                    //auto SrcNode = InputVector[0];
                    //auto DestNode = InputVector[1];

                    // Checks if the input are all numbers, is not then it breaks off the code
                    for(int i = 0; i < InputVector.size(); i++){
                        for(char c : InputVector[i]){
                            if (!std::isdigit(c)) {
                                //std::cout << c << "\n";
                                Numeric = false;
                            }

                        }
                    }

                    if(Numeric == false){
                        Numeric = true;
                        Error_Output += "Invalid fastest parameter, see help.\n";
                        break;
                    }
                }
                else if(StringVector[i] == "save"){
                    //Checks for inputs
                    Command_Output += "> ";
                    Error_Output += "No valid path to save, see help.\n";
                }
                else if(StringVector[i] == "print"){
                    //Checks for inputs
                    Command_Output += "> ";
                    Error_Output += "No valid path to print, see help.\n";
                }
                else if(StringVector[i] == "exit"){
                    Command_Output += "> ";
                    break;
                }
                else{
                    auto word = std::find(WordList.begin(), WordList.end(), StringVector[0]);
                    if(word == WordList.end()){
                        std::cout << "WorldList Error: "+ StringVector[0] + "\n";
                        Command_Output += "> ";
                        Error_Output += "Unknown command \"" + StringVector[0] + "\" type help for help.\n";
                        break;
                    }
                }
            }

            if(StringVector[0] == "exit"){
                break;
            }
        }
        std::cout << Command_Output + "\n";
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
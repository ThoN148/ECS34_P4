#include "TransportationPlannerCommandLine.h"
#include <algorithm>

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
        std::vector< char > CharBuffer(2560);
        std::size_t CharBufferSize = CharBuffer.size();
        bool ExitFlag = false;
        bool ErrorFlag = false;


        while (!ExitFlag && DCmdSrc->Read(CharBuffer, CharBufferSize)) {
            //
            std::size_t NewLine = std::find(CharBuffer.begin(), CharBuffer.end(), '\n') - CharBuffer.begin();
            if (NewLine > CharBuffer.size()) {
                NewLine = std::find(CharBuffer.begin(), CharBuffer.end(), '\0') - CharBuffer.begin();
            }
            std::string command(CharBuffer.begin(), CharBuffer.begin() + NewLine);

            std::string Command_Output;
            std::string Error_Output;

            // Write the prompt to the output sink
            if (!ExitFlag) {
                std::string prompt = "> ";
                DOutSink->Write(std::vector<char>(prompt.begin(), prompt.end()));
            }

            if (command == "help") {
                Command_Output = "------------------------------------------------------------------------\n"
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
            else if(command == "count"){

            }
            else if(command == "node 0"){

            }
            else if(command == "fastest"){

            }
            else if(command == "shortest"){

            }
            else if(command == "save"){

            }
            else if(command == "print"){

            }
            else if(command == "exit"){
                ExitFlag = true;
            }


            // Checks if there is an exit flag, is so close/exit properly
            /*if(ExitFlag){
                std::string EndLine = "> ";
                DOutSink->Write(std::vector< char >(EndLine.begin(), EndLine.end()));
            }*/

            // Gets the command output through the if statements and then prints it out to the output sink
            // Write the output to the output sink
            DOutSink->Write(std::vector<char>(Command_Output.begin(), Command_Output.end()));
            DErrSink->Write(std::vector<char>(Error_Output.begin(), Error_Output.end()));

            if (!ExitFlag) {
                std::string prompt = "> ";
                DOutSink->Write(std::vector<char>(prompt.begin(), prompt.end()));
            }

        }
    
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
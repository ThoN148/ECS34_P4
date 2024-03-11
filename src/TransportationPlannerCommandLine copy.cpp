#include "TransportationPlannerCommandLine.h"
#include "StringUtils.h"
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
        std::vector< char > CharBuffer(2560);
        bool FirstExit = true;
        bool Finished = false;

        std::string currRow;
		char c = 'x';
	    bool emptyRow = false;

		while (!DCmdSrc->End()) {

			if (!DCmdSrc->Get(c)){
				return false;
			}

			if (c == '\n') {
				char temp;
				if (!DCmdSrc->Peek(temp)) 
					emptyRow = true;
				
				break;
			}

			currRow += c;
		}

        for(int i = 0; i < currRow.size(); i++){
            std::cout << currRow[i];
        }
        std::cout << currRow[1] << currRow[0] << "\n";

        while (DCmdSrc->Read(CharBuffer, CharBuffer.size())) {
            // checks the for New Lines or at the end of the sentence
            std::size_t NewLine = std::find(CharBuffer.begin(), CharBuffer.end(), '\n') - CharBuffer.begin();
            if (NewLine > CharBuffer.size()) {
                NewLine = std::find(CharBuffer.begin(), CharBuffer.end(), '\0') - CharBuffer.begin();
            }

            std::string command(CharBuffer.begin(), CharBuffer.begin() + NewLine);
            std::string Command_Output;
            std::string Error_Output;

            std::cout << command << "\n";

            // Write the First line which is always "> " to the output sink
            Command_Output += "> ";

            // Searches what the command type is then execute that specific code
            if(command == "help") {
                FirstExit = false;
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
                Finished = true;
            }
            else if(command == "count"){
                FirstExit = false;
                int NodeCount = DPlanner->NodeCount();
                std::string NCString = std::to_string(NodeCount);
                Command_Output += NCString + " nodes\n";
                Finished = true;
            }

            else if(command == "node 0"){
                FirstExit = false;

            }
            else if(command == "fastest"){
                FirstExit = false;

            }
            else if(command == "shortest"){
                FirstExit = false;

            }
            else if(command == "save"){
                FirstExit = false;

            }
            else if(command == "print"){
                FirstExit = false;

            }
            else if(command == "exit"){
                if(FirstExit){
                    // Does nothing
                }
                else{
                    std::cout << "TESTING";
                    Command_Output += "> ";
                }
            }

            if(Finished == true){
                Command_Output += "> ";
            }

            // Gets the command output through the if statements and then prints it out to the output sink
            // Write the output to the output sink
            DOutSink->Write(std::vector<char>(Command_Output.begin(), Command_Output.end()));
            DErrSink->Write(std::vector<char>(Error_Output.begin(), Error_Output.end()));
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
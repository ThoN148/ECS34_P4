# CTransportationPlannerCommandLine Markdown File

## Code Segment
```
class CTransportationPlannerCommandLine{
    private:
        struct SImplementation;
        std::unique_ptr<SImplementation> DImplementation;
    public:
        CTransportationPlannerCommandLine(std::shared_ptr<CDataSource> cmdsrc, std::shared_ptr<CDataSink> outsink, std::shared_ptr<CDataSink> errsink, std::shared_ptr<CDataFactory> results, std::shared_ptr<CTransportationPlanner> planner);
        ~CTransportationPlannerCommandLine();
        bool ProcessCommands();
};
```

## Features
There is only one function in this whole code, but that portion is very large. As it helps the user understand the system and how to use the command while also giving them quick and easy information when inputed correctly.

CTransportationPlannerCommandLine: Constructs the implementation with the inputs necessary for the code.
- Would need to give them a DataSource, DataSink for regular and error outputs, and results, and planner.
- These are needed to function the Process command function, without them the whole constructor can't be done


## Example
You can use it to understand how the functions work with this code, like if you were to type "help\n" then it would print out the commands for you
```
> ------------------------------------------------------------------------
help     Display this help menu
exit     Exit the program
count    Output the number of nodes in the map
node     Syntax "node (0, count)"
         Will output node ID and Lat/Lon for node
fastest  Syntax "fastest start end"
         Calculates the time for fastest path from start to end
shortest Syntax "shortest start end"
         Calculates the distance for the shortest path from start to end
save     Saves the last calculated path to file
print    Prints the steps for the last calculated path
> 
```
From here you can start on other functions as well
- help
- exit
- count
- node
- fastest
- shortest
- save
- print
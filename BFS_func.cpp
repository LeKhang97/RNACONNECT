#include<fstream>
#include<boost/program_options.hpp>
#include"support_functions.hpp"

namespace po = boost::program_options;

int main(int argc, char* argv[]){
    string startNode, endNode, filename, outfile;
    map<string, vector<string>> graph;
    po::options_description desc("Options");
    po::variables_map vm;

    try{
        desc.add_options()
        ("help,h", "Print the help message.")
        ("start,s", po::value<string>(&startNode), "Start node.")
        ("end,e", po::value<string>(&endNode), "End node.")
        ("graph,g", po::value<string>(&filename), "Adjacency dictionary in json format. If graph is not provided, the program will use a demo graph.")
        ("outfile,o", po::value<string>(&outfile), "Export result as json format file.");
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm); 

        if(vm.count("help")) {
            cout << desc;
            return 0;
        }
        else if(not(vm.count("start")) || not(vm.count("end"))){
            cout << "Please insert both start and end nodes!\n";
            return 1; 
        }
        
        if(vm.count("graph")){
        ifstream file(filename);
            if(!file){
                cout << "Filename of graph does not exist!" << endl;
                return 1;
            }
            else{
                ifstream f(filename);
                json  json_dict = json::parse(f);
                for(auto i :json_dict.items()){
                    graph[i.key()] = json_value_to_vector(json_dict[i.key()]);
                }
            }
        }
        else{
            cout << "Using demo graph" << endl;
            filename = "demo_graph.json";
            ifstream f(filename);
            if(!f){
                cout << "'demo_graph.json' file is not in this directory!" << endl;
                return 1;
            }
            else{
                json json_dict = json::parse(f);
                for(auto i :json_dict.items()){
                    graph[i.key()] = json_value_to_vector(json_dict[i.key()]);
                }
            }
        }

    }
    catch(exception& e){
        cerr << "error: " << e.what() << "\n";
        return 1;
    }

    cout << "Start node:\t" << startNode << endl << "End node:\t" << endNode << endl;

    Shortest_path x =  BFS(graph, startNode, endNode);
    cout << "Shortest distance is:\t" << x.distance << endl;
    cout << "Shortest paths are: \n";
    print_2d_array(x.path);
    if(vm.count("outfile")){
        nlohmann::ordered_json output = result_to_json(x);

        ofstream file(outfile);
        file << output.dump(2); 

        cout << "Exported result to file name:\t" << outfile << endl;
    }
    return 0;
}
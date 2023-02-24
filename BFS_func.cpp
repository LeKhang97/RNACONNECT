#include<fstream>
#include"support_functions.hpp"
#include<unistd.h>
#include"json.hpp"

using json = nlohmann::json;

int main(int argc, char** argv){
    map<string, vector<string>> graph;
    argument vm = parsing_argv(argc, argv);
    string startNode = vm.start;
    string endNode = vm.end;
    string filename = vm.graph;
    string outfile = vm.outfile;
    string distance_information = vm.distance_information;
    int distance_only = vm.flag_d;
    json  dict_dist;
    
    try{
        if(vm.start == "NULL" || vm.end == "NULL"){
            cout << "Please insert both start and end nodes!\n";
            return 1; 
        }
        
        if(filename != "NULL"){
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
        if(distance_information != "NULL"){
            ifstream dist_file(distance_information);
            if(!dist_file){
                cout << "Filename of distance information does not exist!" << endl;
                return 1;
            }
            else{
                cout << "Using distance dictionary to accelerate the BFS" << endl;
                dict_dist = json::parse(dist_file);
            }
        }
    }
    catch(exception& e){
        cerr << "error: " << e.what() << "\n";
        return 1;
    } 

    cout << "Start node:\t" << startNode << endl << "End node:\t" << endNode << endl;
    

    Shortest_path x =  BFS(graph, startNode, endNode, distance_only, dict_dist);
    
    cout << "\nShortest distance is:\t" << x.distance << endl;
    if(distance_only){
        cout << "Searching shortest paths is not excecuted.\n";
    }
    else{
        cout << "Shortest paths are: \n";
        print_2d_array(x.path);
    }

    if(outfile != "NULL"){
        nlohmann::ordered_json output = result_to_json(x);

        ofstream file(outfile);
        file << output.dump(2); 

        cout << "Exported result to file name:\t" << outfile << endl;
    }
    return 0;
}
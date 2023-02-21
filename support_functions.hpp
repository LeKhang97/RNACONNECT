#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<algorithm>
#include <getopt.h>
#include"json.hpp"

using json = nlohmann::json;
using namespace std;

class Shortest_path{
    public:
        int distance;
        string start, end;
        vector<vector<string>> path;
};

vector<string> json_value_to_vector(auto json_value){
    vector<string> result;
    for(auto j : json_value){
        result.push_back(j);
    }
    return result;
}
void print_1d_array(vector<string> input_array){
    for(string ele: input_array){
        cout << ele << '\t';
    }
    cout << endl;
}

void print_2d_array(vector<vector<string>> input_array){
    for(vector<string> sub_arr: input_array){
        for(string ele: sub_arr){
            cout << ele << '\t';
        }
        cout << endl;
    }
}

vector<vector<string>> duplicate_vector(vector<string> input_vector, int number, vector<string> pushlist = {}){
    vector<vector<string>> output_vector;
    for(int i = 0; i < number; i++){
        vector<string> temp_vector;
        temp_vector.insert(temp_vector.end(), input_vector.begin(), input_vector.end());
        if(pushlist.size() > i){
            temp_vector.push_back(pushlist[i]);
        }
        output_vector.push_back(temp_vector);
        temp_vector.clear();
    }
    return output_vector;
}

Shortest_path BFS(map<string, vector<string>> graph, string startNode, string endNode, 
bool distance_only = false){
    vector<string> visited = {startNode}, queue = {startNode}, keys, lastnodes = {startNode};
    int s = 0, flag = 1;
    vector<vector<string>> visited_list;
    visited_list.push_back({startNode});
    Shortest_path shortestpath;
    shortestpath.distance = -1;
    shortestpath.start = startNode;
    shortestpath.end = endNode;
    
    //Check if startNode = endNode and interact with itself
    if(startNode == endNode){
        if(find(graph[startNode].begin(), graph[startNode].end(), startNode) == graph[startNode].end()){
            shortestpath.distance = 0;
        }
        else{
            shortestpath.distance = 1;
            shortestpath.path = {{startNode, startNode}};
            return shortestpath;
        }
        return shortestpath;
    }

    keys.reserve(graph.size()); // to preallocate enough memory for the new vector
    for(const auto [key, value] : graph) {
        keys.push_back(key);
    }

    while(flag) {
        vector<string> sublastnodes;
        vector<string> next_queue;

        while(queue.size()){
            vector<string> temp_visited_list;
            string currentNode = queue.front();
            
            queue.erase(queue.begin());
            
            if(find(keys.begin(), keys.end(), currentNode) != keys.end()){
                for(string neighbor: graph[currentNode]){
                    if( find(visited.begin(), visited.end(), neighbor) == visited.end() &&
                        find(lastnodes.begin(), lastnodes.end(), neighbor) == lastnodes.end()){
                        temp_visited_list.push_back(neighbor);
                        if(find(next_queue.begin(), next_queue.end(), neighbor) == next_queue.end()){
                            next_queue.push_back(neighbor);
                        }
                        if(neighbor == endNode){
                            shortestpath.distance = s + 1;
                            flag = 0;
                            if(distance_only == true){
                                return shortestpath;
                            }
                        }
                    }
                }

                if(distance_only == false){
                    vector<vector<string>> v = visited_list;
                    int u = 0;
                    if(v.size() > 0){
                        for(int index = 0; index < v.size(); index++){
                            int a = visited_list.size() - v.size();
                            if((v[index].back() == currentNode)){
                                vector<vector<string>> m = duplicate_vector(v[index], temp_visited_list.size(),temp_visited_list);
                                if(m.size()){
                                    for(int i = v.size() - 1; i > index + u -a -1 ; i--){
                                        visited_list.pop_back();
                                    }
                                    for(vector<string> sub_m :m){
                                        visited_list.push_back(sub_m);
                                        if(sub_m.back() == endNode){
                                            shortestpath.path.push_back(sub_m);
                                        }
                                    }
                                    if(v.size() - (index+u+1) > 0){
                                        for(int i = index+u+1-a ; i < v.size(); i++){
                                            visited_list.push_back(v[i]);
                                        }
                                    }
                                    u += m.size() - 1;
                                }
                            }
                        }
                    }
                    v.clear();
                }
            }
            if(find(visited.begin(), visited.end(), currentNode) == visited.end()){
                visited.push_back(currentNode);
            }
            for(string node: temp_visited_list){
                if(find(sublastnodes.begin(), sublastnodes.end(), node) == sublastnodes.end()){
                    sublastnodes.push_back(node);
                }
            }
        }
        if(next_queue.size() == 0 || flag == 0){
            break;
        }
        for(string node: sublastnodes){
            if(find(lastnodes.begin(), lastnodes.end(), node) == lastnodes.end()){
                lastnodes.push_back(node);
            }
        }
        queue = next_queue;
        next_queue.clear();
        s ++;
    }
    return shortestpath;
}

nlohmann::ordered_json result_to_json(Shortest_path x){
    nlohmann::ordered_json output;
    
    output["start"] = x.start;
    output["end"] = x.end;
    output["distance"] = x.distance;
    output["path"] = x.path;

    return output;
}

class argument{
    public:
        string start = "NULL";
        string end = "NULL";
        string graph = "NULL";
        string outfile = "NULL";
        int flag_d = 0;
};

argument parsing_argv(int argc, char** argv){
    argument vm;

    while(1){
        int option_index = 0;
        static struct option long_options[] = 
        {
            {"help", no_argument, NULL, 'h'},
            {"start", required_argument, NULL, 's'},
            {"end", required_argument, NULL, 'e'},
            {"graph", optional_argument, NULL, 'g'},
            {"distance_only", no_argument, NULL, 'd'},
            {"outfile", optional_argument, NULL, 'o'},
            {NULL, 0, NULL, 0}
        };
        int c = getopt_long(argc, argv, "hs:e:g:do:", long_options, &option_index);
        if(c == -1){
            break;
        }
        switch (c)
        {
        case 0:
            cout << "long option " << long_options[option_index].name << endl;
            if(optarg){
                cout << "with arg " << optarg << endl;
            }
            break;
        case 1: // When there is no prefix '-' in option
            cout << "regular argument " << optarg << endl;
            break;
        case 'h':
            cout << "Options:\n";
            cout << "-h [ --help ]\t\t\tPrint the help message.\n";
            cout << "-s [ --start ]\t\t\tStart node.\n";
            cout << "-e [ --end ]\t\t\tEnd node.\n";
            cout << "-g [ --graph ]\t\t\tAdjacency dictionary in json format. If graph is not provided, the program will use a demo graph.\n";
            cout << "-o [ --outfile ]\t\tExport result as json format file.\n";
            cout << "-d [ --distance_only ]\t\tOnly return shortest distance, not the path.\n";
            
            exit(EXIT_FAILURE);
        case 's':
            vm.start = optarg;
            break;
        case 'e':
            vm.end = optarg;
            break;
        case 'g':
            vm.graph = optarg;
            break;
        case 'd':
            vm.flag_d = 1;
            break;
        case 'o':
            vm.outfile = optarg;
            break;
        /*case '?':
            //cout << "Invalid argument!" << "\n";
            exit(EXIT_FAILURE);*/
        case ':':
            cout << "Missing option for " << optopt << "\n";
            break;
        }
    }

    return vm;
}
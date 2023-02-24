# RNACONNECT
This project aims to build the interactive RNA-Protein interaction network on webserver, where people can submit their Proteins/RNAs code and get their neighbor interactions and perform the Breadth-First Search (BFS). 

## The BFS
The <b>BFS_func.cpp</b> can be served as independent program to search the shortest distance, as well as providing all shortest paths between 2 vertices.

### Usage
You can compile this file by:<br>
```g++ BFS_func.cpp -o BFS_func```<br>or<br>```make BFS_func```

Then type ```./BFS_func -h``` for more information of the usage:
```
Options:
  -h [ --help ]                   Print the help message.
  -s [ --start ] arg              Start node.
  -e [ --end ] arg                End node.
  -g [ --graph ] arg              Adjacency dictionary in json format. If graph is not provided, the program will use a demo graph.
  -o [ --outfile ] arg            Export result as json format file.
  -d [ --distance_only ]          Only return shortest distance, not the path.
  -i [ --distance_information ]	  Perform the BFS faster with the known distances stored in json format file.
```


### Notes
- When ```--graph``` option is not called, the program will use the graph in <i>demo_graph.json</i> in the directory by default. There is also a file <i>larger_demo_graph.json</i>, which is much larger in the directory, you can try it as an input.
- When ```--graph``` is called, make sure that your <b>json</b> file contains only <b>string</b> type information. 
- If there is no path between <b>Start node</b> and <b>End node</b>, their distance is set to <b>-1</b> and no path is provided.
- If one node is used for both <b>Start</b> and <b>End node</b>, if it's self-interacted, the distance will be <b>1</b>, otherwise <b>0</b>.
- The program will be much faster with the ```--distance_only``` mode than the return-paths mode.
- ```--distance_information``` field is a filename. That <b>json format</b> file contains information about distances. Check the <i>distance_infor.json</i> for the example. 











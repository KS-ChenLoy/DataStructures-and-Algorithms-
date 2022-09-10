//
//  main.cpp
//  Simplified_PageRankP2
//
//  Created by Kemari Chen Loy on 7/16/21.
//


#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <iomanip>

//Using template offered in PDF

class AdjacentList{
private:
    //Think about what member variables you need to initialize
    int counter = 0;
    std::unordered_map<int, std::vector<std::string>> vertex_Graph;
    std::map<std::string, int> myMap; //need map to store name of site and the page rank

public:

    std::vector<int> helperFunction(){
        std::vector<int> out_Degree(counter,0);
        //traverse through map and graph and increment
        for(auto& iter: myMap){
            for (auto &i : vertex_Graph[iter.second]) {
                out_Degree.at(myMap[i])++;
            }
        }
        return out_Degree;
    }
    //Think about what helper functions you will need in the algorithm
    //prints the PageRank of all pages after powerIterations in ascending alphabetical order of webpages and rounding rank to two decimal places
    void PageRank(int n){

        //1 vertex and 1 iteration will be present at all times.
        std::vector<int> outWard = helperFunction();
        std::vector<double> myVec(counter,1.0/counter), vec(counter,0.0);

        if (n != 1) {
            int i = 1;
            while (i < n) {
                if (i != 1)
                    myVec = vec;
                for (auto &iter : myMap) {
                    double result = 0.0;
                    if (i != n - 1) {} else std::cout << iter.first << " ";
                    for (auto &j: vertex_Graph[iter.second]) {
                        //adding to get the ranks
                        result = result + (myVec.at(myMap[j]) * (1.0 / outWard.at(myMap[j])));
                    }
                    vec.at(iter.second) = result;
                    if (i != n - 1) continue;
                    //prints
                    std::cout << std::fixed << std::setprecision(2) << result << std::endl;
                }
                i++;
            }
        } else {
            for (auto &iter: myMap) {
                //prints
                std::cout << iter.first << " " << std::fixed << std::setprecision(2) << (1.0 / counter) << std::endl;
            }
        }
    }



    void insertEdge(std::string from, std::string to){

        //below checks to see if the vertex is already present and creates mapper
        if (myMap.find(to) == myMap.end()) {
            myMap[to] = counter++;
        }
        if(myMap.find(from) == myMap.end()){
            myMap[from] = counter++;
        }

        //store values in the graph created
        vertex_Graph[myMap[to]].push_back(from);
        //points to empty vector
        if (vertex_Graph.find(myMap[from]) == vertex_Graph.end()) {
            vertex_Graph[myMap[from]] = {};
        }
    }

};
// This class and method are optional. To accept the input, you can use this method:

int main(){

    // creating an object
    AdjacentList myObj;
    int no_of_lines, power_iterations;
    std::string from, to;
    std::cin >> no_of_lines;
    std::cin>>power_iterations;

    for (int i = 0; i< no_of_lines; ++i) {
        std::cin >>from;
        std::cin >> to;
        myObj.insertEdge(from, to);
    }
    //Create a graph object
    myObj.PageRank(power_iterations);
}

//Resources:
/*
 https://www.youtube.com/watch?v=yVPdrGwGee8&list=PLvBZ6Nw3S6DQ-nPvBfz5rBy3vky9NnvHP&index=7
 https://www.youtube.com/watch?v=lsSam83JtWg&list=PLvBZ6Nw3S6DQ-nPvBfz5rBy3vky9NnvHP&index=6
 https://www.cplusplus.com/reference/iomanip/setprecision/
https://www.geeksforgeeks.org/finding-in-and-out-degrees-of-all-vertices-in-a-graph/
 https://github.com/ChrisCJFern/PageRank

 Oracle employee Juan Calle also gave insight on the completion of this project.

 */

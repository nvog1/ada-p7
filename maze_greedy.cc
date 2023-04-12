//Nicolás Van Olmen Giménez, 74383864R
#include <fstream>
#include <string>
#include <limits>
#include <iostream>
#include <vector>
using namespace std;

void show_usage(){
  cerr << "Usage:" << endl << "maze_greedy [-p] -f file" << endl;
}

void print_matrix(vector<vector<char>> matrix, int rows, int cols){
  for(int i=0;i<rows;i++){
    for(int j=0;j<cols;j++){
      if(matrix[i][j] == '\000') cout << "0";
      else if(matrix[i][j] == '\001') cout << "1";
      else{
        cout << matrix[i][j];
      }
    }
    cout << endl;
  }
}

int maze_greedy(const vector<vector<int>> &maze, vector<vector<char>> &path_solu){
  int rows = maze.size();
  int cols = maze[0].size();
  int posx = 0;
  int posy = 0;
  int pasos = 0;

  if(maze[0][0] == 0){
    return 0;
  }
  else{
    pasos++;
    path_solu[0][0] = '*';
  }

  while(posx<(cols-1) || posy<(rows-1)){
    if(posx < (cols-1) && posy < (rows-1) && maze[posy+1][posx+1] == 1){
      pasos++;
      path_solu[posy+1][posx+1] = '*';
      posx++;
      posy++;
    }
    else if(posy < (rows-1) && maze[posy+1][posx] == 1){
      pasos++;
      path_solu[posy+1][posx] = '*';
      posy++;
    }
    else if(posx < (cols-1) && maze[posy][posx+1] == 1){
      pasos++;
      path_solu[posy][posx+1] = '*';
      posx++;
    }
    else{
      return 0;
    }
  }
 
  return pasos;
}

int main(int argc, char *argv[]){
  //comprobacion de argumentos
  bool path = false;
  bool file = false;
  string filename = "";

  if(argc == 1){
    show_usage();
    return -1;
  }

  for(int i=1;i<argc;i++){
    string arg = argv[i];

    if(arg == "-p"){
      path = true;
    }
    else if(arg == "-f"){
      if(!file){
        i++;
        if( i>= argc ){
          cerr << "ERROR: missing filename." << endl;
          show_usage();
          return -1;
        }
        filename = argv[i];
        file = true;
      }
    }
    else{
      cerr << "ERROR: unknown option " << argv[i] << "." << endl;
      show_usage();
      return -1;
    }
  }

  if(!file){
    cerr << "ERROR: -f option is required." << endl;
    show_usage();
    return -1;
  }

  //leo el fichero
  ifstream is(filename);
  if(!is){
    cerr << "ERROR: can't open file: " << filename << "."  << endl;
    show_usage();
    return -1;
  }

  int rows , cols;
  is >> rows >> cols ;
  vector<vector<int>> maze(rows, vector<int>(cols));
  for(int i=0;i<rows;i++)
    for(int j=0;j<cols;j++)
      is >> maze[i][j];

  //ejecucion algoritmos
  vector<vector<char>> path_solu(maze.size(),vector<char>(maze[0].size()));
  for(int i=0;i<rows;i++)
    for(int j=0;j<cols;j++){
      path_solu[i][j] = (char)maze[i][j];
    }

  int greedy = maze_greedy(maze,path_solu);

  //salida
  cout << greedy << endl;

  if(path){
    print_matrix(path_solu, path_solu.size(), path_solu[0].size());
  }

  return 0;
}

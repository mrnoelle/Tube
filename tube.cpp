#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

#include "tube.h"

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* internal helper function which allocates a dynamic 2D array */
char **allocate_2D_array(int rows, int columns) {
  char **m = new char *[rows];
  assert(m);
  for (int r=0; r<rows; r++) {
    m[r] = new char[columns];
    assert(m[r]);
  }
  return m;
}

/* internal helper function which deallocates a dynamic 2D array */
void deallocate_2D_array(char **m, int rows) {
  for (int r=0; r<rows; r++)
    delete [] m[r];
  delete [] m;
}

/* internal helper function which gets the dimensions of a map */
bool get_map_dimensions(const char *filename, int &height, int &width) {
  char line[512];
  
  ifstream input(filename);

  height = width = 0;

  input.getline(line,512);  
  while (input) {
    if ( (int) strlen(line) > width)
      width = strlen(line);
    height++;
    input.getline(line,512);  
  }

  if (height > 0)
    return true;
  return false;
}

/* pre-supplied function to load a tube map from a file*/
char **load_map(const char *filename, int &height, int &width) {

  bool success = get_map_dimensions(filename, height, width);
  
  if (!success)
    return NULL;

  char **m = allocate_2D_array(height, width);
  
  ifstream input(filename);

  char line[512];
  char space[] = " ";

  for (int r = 0; r<height; r++) {
    input.getline(line, 512);
    strcpy(m[r], line);
    while ( (int) strlen(m[r]) < width )
      strcat(m[r], space);
  }
  
  return m;
}

/* pre-supplied function to print the tube map */
void print_map(char **m, int height, int width) {
  cout << setw(2) << " " << " ";
  for (int c=0; c<width; c++)
    if (c && (c % 10) == 0) 
      cout << c/10;
    else
      cout << " ";
  cout << endl;

  cout << setw(2) << " " << " ";
  for (int c=0; c<width; c++)
    cout << (c % 10);
  cout << endl;

  for (int r=0; r<height; r++) {
    cout << setw(2) << r << " ";    
    for (int c=0; c<width; c++) 
      cout << m[r][c];
    cout << endl;
  }
}

/* pre-supplied helper function to report the errors encountered in Question 3 */
const char *error_description(int code) {
  switch(code) {
  case ERROR_START_STATION_INVALID: 
    return "Start station invalid";
  case ERROR_ROUTE_ENDPOINT_IS_NOT_STATION:
    return "Route endpoint is not a station";
  case ERROR_LINE_HOPPING_BETWEEN_STATIONS:
    return "Line hopping between stations not possible";
  case ERROR_BACKTRACKING_BETWEEN_STATIONS:
    return "Backtracking along line between stations not possible";
  case ERROR_INVALID_DIRECTION:
    return "Invalid direction";
  case ERROR_OFF_TRACK:
    return "Route goes off track";
  case ERROR_OUT_OF_BOUNDS:
    return "Route goes off map";
  }
  return "Unknown error";
}

/* presupplied helper function for converting string to direction enum */
Direction string_to_direction(const char *token) {
  const char *strings[] = {"N", "S", "W", "E", "NE", "NW", "SE", "SW"};
  for (int n=0; n<8; n++) {
    if (!strcmp(token, strings[n])) 
      return (Direction) n;
  }
  return INVALID_DIRECTION;
}

/* question 1 */
bool get_symbol_position(char **map, int height, int width, char target, int& map_row, int& map_column)
{
  for(map_row=0; map_row<height; map_row++)
    {
      for(map_column=0; map_column<width; map_column++)
	{
	  if(target==map[map_row][map_column])
	    {
	      return true;
	      break;
	    }
	}
    }
  return false;
}

/* question 2 */
char get_symbol_for_station_or_line(char* name)
{

  int i=0;
  const int max=100;
  char symbol[max];
  char station[max][max];
  char line[max][max];
  char character;

  //check stations

  ifstream in_stream1("stations.txt");

  in_stream1.unsetf(ios::skipws);

  if(in_stream1.fail())
    {
      cout << "[ERROR] File 'stations.txt' could not be opened." << endl;
      exit(1); 
    }
      
  while(!in_stream1.eof())
    {
      in_stream1>>symbol[i];
      in_stream1>>character;
      in_stream1.getline(station[i],max);
      //   cout<<i<<" "<<symbol[i]<<" "<<station[i]<<endl;
     
      i++;

    }
     

  for(int j=0; j<i; j++)
    {
      if(strcmp(name,station[j])==0)
	return symbol[j];
    }

  in_stream1.close();

  //check station lines
         
  i=0;
      
  ifstream in_stream2("lines.txt");

  in_stream2.unsetf(ios::skipws);

  if(in_stream2.fail())
    {
      cout << "[ERROR] File 'lines.txt' could not be opened." << endl;
      exit(1); 
    }
     
  while(!in_stream2.eof())
    {
      in_stream2>>symbol[i];
      in_stream2>>character;
      in_stream2.getline(line[i], max);
	  
      i++;
	  
    }
        
	
  for(int j=0; j<i; j++)
    {
      if(strcmp(name,line[j])==0)
	return symbol[j];
    }	


  in_stream2.close();
  return  ' ';
}






/*question 3*/

char get_symbol_for_station(char* name)
{

  int i=0;
  const int max=100;
  char symbol[max];
  char station[max][max];
 
  char character;

  ifstream in_stream1("stations.txt");

  in_stream1.unsetf(ios::skipws);

  if(in_stream1.fail())
    {
      cout << "[ERROR] File 'stations.txt' could not be opened." << endl;
      exit(1); 
    }
      

  while(!in_stream1.eof())
    {
      in_stream1>>symbol[i];
      in_stream1>>character;
      in_stream1.getline(station[i],max);
      i++;

    }
     

  for(int j=0; j<i; j++)
    {
	if(strcmp(name,station[j])==0)
	  return symbol[j];
    }
  in_stream1.close();
  return  ' ';
}



bool check_start_station(char* name)
{
  char result=get_symbol_for_station(name);
  if (result==' ')
    return false;
  else
    return true;
} 



char **allocate_route_array(char* route, int& n_row, int& n_column)
  {
    char* direction=route;
    n_row=0;
    n_column=3;

    while(*direction!='\0')
      {
	if(*direction==',')
	  n_row++;
	direction++;

      }
    n_row++;
     
    char **route_array =allocate_2D_array(n_row,n_column);
    direction=route;
    int i=0;
    int j=0;
    while( i<n_row )
    {
      while (*direction!=',' && *direction!='\0')
	{
	  route_array[i][j]=*direction++;
	  j++;
	}
      while ( j<n_column )
	{
	  route_array[i][j]='\0';
	  j++;

	}
      i++;
      j=0;
      direction++;
    }

    return route_array;
  }



//check the next step

bool next_step(const char* token,int &map_row, int &map_column)
{
  Direction direction = string_to_direction(token);

  switch (direction) 
    {
    case N: map_row--; break;
    case S: map_row++; break;
    case W: map_column--; break;
    case E: map_column++; break;
    case NE: map_row--; map_column++; break;
    case NW: map_row--; map_column--; break;
    case SE: map_row++; map_column++; break;
    case SW: map_row++; map_column--; break;
    case INVALID_DIRECTION: return false;
    }
  
  return true;

}


bool get_station_by_position(char **map,int map_row,int map_column, char station_name[]){

 
  const int max=30;
  
 
  char white_space;
  char character;

  ifstream in_stream1("stations.txt");

  in_stream1.unsetf(ios::skipws);

  if(in_stream1.fail())
    {
      cout << "[ERROR] File 'stations.txt' could not be opened." << endl;
      exit(1); 
    }
      

  while(!in_stream1.eof())
    {
      in_stream1>>character;
      in_stream1>>white_space;
      in_stream1.getline(station_name,max);
      

      if(map[map_row][map_column]==character)
	{
	  in_stream1.close();
	  return true;
	}
    }

  in_stream1.close();
  return false;
}

bool get_line_by_position(char **map,int map_row,int map_column, char line_name[]){

 
  const int max=30;
  
 
  char white_space;
  char character;

  ifstream in_stream2("lines.txt");

  in_stream2.unsetf(ios::skipws);

  if(in_stream2.fail())
    {
      cout << "[ERROR] File 'lines.txt' could not be opened." << endl;
      exit(1); 
    }
      
  while(!in_stream2.eof())
    {
      in_stream2>>character;
      in_stream2>>white_space;
      in_stream2.getline(line_name,max);
      
      if(map[map_row][map_column]==character)
	{
	  in_stream2.close();
	  return true;
	}
    }
  in_stream2.close();
  return false;
}



int validate_route(char** map,int height,int width, char* start_station,char* route,char* destination)
{
  
  
  //check error for start station, ERROR -1
 
  if(!check_start_station(start_station))
  return ERROR_START_STATION_INVALID; 

  char symbol=get_symbol_for_station(start_station);
  int map_row=0;
  int map_column=0;
  get_symbol_position(map, height, width, symbol, map_row, map_column);
  
  //read route
  int n_rows=0;
  int n_columns=0;

  char** route_array = allocate_route_array(route, n_rows, n_columns);
 
  
  char map_char;
  enum State {AT_STATION, ON_LINE};
  State prev_state = AT_STATION;
  State current_state;
 
  int prev_row=map_row, prev_column=map_column;
  int prev_prev_row=map_row, prev_prev_column=map_column;
  
  char current_name[30];
  

  int count_for_interchange=0;


  for (int i=0; i<n_rows; i++) 
    {
      //check invalid direction, ERROR -5
      if (!next_step(route_array[i], map_row, map_column)) 
	return ERROR_INVALID_DIRECTION;
	

      // check we're in bounds of the map, ERROR -7
      if (map_row > height || map_row <0 || map_column >width || map_column <0)
	return ERROR_OUT_OF_BOUNDS;
       
      map_char = map[map_row][map_column];

      // check we're on the line, ERROR -6
      if (map_char== ' ') 
	return ERROR_OFF_TRACK;

      // update current state
      if (get_station_by_position(map, map_row, map_column,current_name))
	current_state = AT_STATION;
      else if (get_line_by_position(map,map_row,map_column,current_name))
	current_state = ON_LINE;
        
      // line hopping, ERROR -3
      if (prev_state==ON_LINE && current_state==ON_LINE)
	{
	  if (map_char!= map[prev_row][prev_column])
	    return ERROR_LINE_HOPPING_BETWEEN_STATIONS;
        }
      
    
      //prev and current state on the line, checking backtracking, ERROR -4
       if (prev_state==ON_LINE && current_state==ON_LINE)
	 {
	   if (map_row == prev_prev_row && map_column == prev_prev_column)
	     return ERROR_BACKTRACKING_BETWEEN_STATIONS;
	 }

      //count for interchange
	      
       if (prev_state==AT_STATION)
	 {	 
	   if(!isalnum(map[prev_prev_row][prev_prev_column]) && 
	      (map[map_row][map_column]!= map[prev_prev_row][ prev_prev_column]))
	     {
	       count_for_interchange++;
	     }
	 }

       prev_prev_row=prev_row;
       prev_prev_column=prev_column;
       prev_row=map_row;
       prev_column=map_column;
       prev_state=current_state;
 

    }
 
  //end point not a station, ERROR -2 

  if (!isalnum(map_char))
    return -2;

  if (get_station_by_position(map, map_row, map_column, current_name))
    {
     strcpy(destination, current_name);
     return count_for_interchange;
    }

  return 0;
}




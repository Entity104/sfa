#include<iostream>
#include<unordered_map>
#include<string.h>
#include<vector>
#include<sstream>
#include<math.h>
#include<cctype>

using namespace std;

#define STATUS_ERROR -1
#define V 1

int curline = 0;
unordered_map<string, long double> smap;
unordered_map<string, vector<long double>> mmap;

enum op{
  DEF = 'd'+'e'+'f',
  OUT = 344,
  VOP = 341
};

enum vop{
  MEAN = 417
};

void vprint(string message, int level){
	if(level <= V){
		cout << "(v" << level << " " << message << ")";
	}
}

int pexit(int status){
	printf("(line: %d)\n", curline);
	return status;
}

long double numberOrMap(string s1){
	return (isdigit(s1[0]))? strtold(s1.c_str(), NULL) : smap[s1];   
}

long double mean(string mapname){
	long double i=0;
	long double sum=0;
	for(auto v : mmap[mapname]){
		i++;
		sum += v;
	}
	return (sum/i);
}

unsigned int op2int(string operation){
  int i=0;
  unsigned int n = 0;
  while(operation[i] != '\0'){
	n+=operation[i];
	i++;
  }
  return n;
}


int main(int argc, char** argv){
  string operation;
  string varname;
  long double number;

  long double r1,r2,r3,r4;
  string s1,s2,s3,s4;

  while(cin >> operation){
	curline++;
	if(operation[0] == '#') continue;
    	switch(op2int(operation)){
		case DEF:{
			int n = 0;
			cin >> varname;
			if(isdigit(varname[0])){
				vprint("Name of a variable cannot start with a number", 1);
				return pexit(STATUS_ERROR);
			}
			string line;
			if(getline(cin, line)){
				istringstream iss(line);
				while(iss >> number){
					n++;
					mmap[varname].push_back(number);
				}
				if(n == 1) smap[varname] = number;
			}
	  		break;
		}
		case OUT:{
	  		string file;
			string op;
			cin >> file >> s1;
			switch(s1[0]){
				case '@':
					//Just a single variable
					varname = s1.substr(1);
					number = smap[varname];
					break;
				case '"':
					//Immediate string
					break;
				default:
					//An operation
					cin >> op >> s2;
					switch(op[0]){
						case '+':
							r1 = numberOrMap(s1);
							r2 = numberOrMap(s2);
						
							number = r1 + r2;
							break;
						case '-':
							r1 = numberOrMap(s1);
							r2 = numberOrMap(s2);
						
							number = r1 - r2;
							break;
						case '*':	
							r1 = numberOrMap(s1);
							r2 = numberOrMap(s2);
						
							number = r1 * r2;

							break;
						case '/':	
							r1 = numberOrMap(s1);
							r2 = numberOrMap(s2);
						
							number = r1 / r2;

							break;
						case '^':	
							r1 = numberOrMap(s1);
							r2 = numberOrMap(s2);
						
							number = pow(r1,r2);
							break;
						default:

							break;
					}
			}
			switch(file[0]){
				case '#':
					if(s1[0] == '"') cout << (s1.substr(1, s1.size() - 2));
					else cout << number << endl;
					break;
				case '$':
					break;
				default:
					file = file.substr(1);
					smap[file] = number;
					break;
			}
	  		break;
		}
		case VOP:{
			cin >> s1 >> s2 >> s3;
			switch(op2int(s2)){
				case MEAN:
					smap[s1] = mean(s3);
					break;
			}
			break;
		}
		default:
			cout << "error";
			break;
    	}
  }
  return 0;
}

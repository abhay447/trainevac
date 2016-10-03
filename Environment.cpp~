#include <iostream>
#include<fstream>
#include<algorithm>
#include<sstream>
#include<string>
#include<string.h>

using namespace std;

extern vector<Wall> myWalls;
extern vector<Pedestrian> myPeds;

float RandomFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

void CreateMap()
{
	ifstream myfile;
	string line;
	myfile.open("Maps/room2.mpf");
	GLfloat  cx,cy,nx,ny,length;
	int id;
	while(getline(myfile,line))
	{
		istringstream iss(line);
		if(line[0]=='/' && line[1]=='/' || line[0]==' ')
		    continue;
		while(iss>>id>>cx>>cy>>nx>>ny>>length)
		{
			myWalls.push_back(Wall(id,cx,cy,nx,ny,length));
		}
	}
}

void AddAgents(int numAgents)
{	
    for(int i=0;i<numAgents;i++)
    {
    	myPeds.push_back(Pedestrian(i, RandomFloat(10.0f,2080.0f),RandomFloat(10.0f,304.0f)));
    }
          
}


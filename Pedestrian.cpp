#include <iostream>
#include <iostream>
#include <math.h>
#include <string>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "PedestrianRenderer.h"

extern glm::mat4 MVP,View,Projection;

using namespace std;

GLfloat getAgeFactor(int age){
    return 1.29f/(1.29f + (age-20.00f)*(1.91f-1.29f)/(59-20));
}

GLfloat getWaistFactor(int age, int gender){
    GLfloat ChnWaist,IndWaist;
    if(gender == 0){
        ChnWaist = 88.1 + (65-19)/(106.7-88.1)*(age-19);
    }
    else{
        ChnWaist = 85.8 + (65-19)/(98.6-85.8)*(age-19);
    }
    IndWaist = ChnWaist * 80.00/98.33;
    return 1.28f/(1.28f + (IndWaist - 68.55)*(1.88-1.28)/(130.8-68.55));
}

class Pedestrian
{
	private:
		int id;		
	public:
		GLfloat px,py;		
		GLfloat vx,vy;
		GLfloat ax,ay;
		GLfloat tx,ty;
        GLfloat maxSpeed;
        GLfloat ageF,waistF;
		void draw();
		void destroy();
		void clearForces();
		Pedestrian(int PID, GLfloat PX, GLfloat PY,int PAge,int PGender);
		Pedestrian(){};
    	PedestrianRenderer* renderer;
};

Pedestrian::Pedestrian(int PID, GLfloat PX, GLfloat PY,int PAge,int PGender)
{
	id = PID;
	px = PX;
	py = PY;
	vx = 0.0f;
	vy = 0.0f;
	ax = 0.0f;
	ay = 0.0f;
	tx = px+100.0f;
	ty = py+100.0f;
	renderer = new PedestrianRenderer();
    
    ageF = getAgeFactor(PAge);
    waistF = getWaistFactor(PAge,PGender);
    maxSpeed = 0.7f*(0.4f*ageF + 0.6f*waistF)/(ageF+waistF);
}

void Pedestrian::clearForces()
{
	ax = 0;
	ay = 0;
}


void Pedestrian::draw()
{	
	vx += ax*(0.4f*ageF + 0.6f*waistF)/(ageF+waistF);
	vy += ay*(0.4f*ageF + 0.6f*waistF)/(ageF+waistF);
	if(vx >   maxSpeed)
		vx =  maxSpeed;
    if(vx < - maxSpeed)
		vx =- maxSpeed;
	if(vy >   maxSpeed)
		vy =  maxSpeed;
	if(vy < - maxSpeed)
		vy =- maxSpeed;
	px += vx;
	py += vy;	
	glm::mat4 Model;
	Model = glm::translate(Model, glm::vec3(px, py, 0.0f));	
	renderer->draw(Model);
}

void Pedestrian::destroy()
{
	renderer->clearBuffers();
}


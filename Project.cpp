//
//  Project.cpp
//  TimeMe
//
//  Created by Mustafa Soby on 3/11/21.
//

#include "Project.hpp"
#include <ctime>

void Project::setProjectName(std::string in){
	projectName=in;
}

std::string Project::getProjectName(){
	return projectName;
}

void Project::setPathName(std::string in){
	pathName=in;
}

std::string Project::getPathName(){
	return pathName;
}

void Project::setModified(time_t in){
	modified=in;
}

time_t Project::getModified(){
	return modified;
}

void Project::setLineCount(int in){
	lineCount=in;
}

int Project::getLineCount(){
	return lineCount;
}

void Project::setSecondsSpent(double in){
	secondsSpent=in;
}

double Project::getSecondsSpent(){
	return secondsSpent;
}

void Project::setBuildCount(int in){
	buildCount=in;
}

int Project::getBuildCount(){
	return buildCount;
}


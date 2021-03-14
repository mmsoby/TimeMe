//
//  Project.hpp
//  TimeMe
//
//  Created by Mustafa Soby on 3/11/21.
//

#ifndef Project_hpp
#define Project_hpp

#include <stdio.h>
#include <string>
#include <cstdlib>
#include <ctime>

class Project{
private:
	std::string projectName="";//Needs work
	std::string pathName="";
	time_t modified;
	int lineCount=0;
	double secondsSpent=0;
	int buildCount=0;
public:
	
	void setProjectName(std::string in);
	std::string getProjectName();
	void setPathName(std::string in);
	std::string getPathName();
	void setModified(time_t in);
	time_t getModified();
	void setLineCount(int in);
	int getLineCount();
	void setSecondsSpent(double in);
	double getSecondsSpent();
	void setBuildCount(int in);
	int getBuildCount();

};


#endif /* Project_hpp */

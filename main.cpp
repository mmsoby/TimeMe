//
//  main.cpp
//  TimeMe
//
//  Created by Mustafa Soby on 3/5/21.
//

#include <iostream>
#include <fstream>
#include "Project.hpp"
#include <ctime>
#include <sstream>
//#include <boost/algorithm/string/trim.hpp>

using namespace std;

#define ARRAYSIZE 10
#define MINUTESSINCELASTBUILD 30
int projectCount=0;

static void parseNewInfo(std::ifstream &log, std::ifstream &mostRecent, Project *projects);
static int printReport(Project *projects);

int alreadyExists(string projectName_in, Project *projects);
int hoursToSeconds(string hours);

string secondsToHours(int seconds);
string timeToString(time_t t);

time_t timeParser(string in);


int main() {
	/**READ LOG.TXT AND MOSTRECENT.TXT*/
	//Prepare input file variables
	ifstream log;
	log.open("log.txt");
	
	ifstream mostRecent;
	mostRecent.open("mostRecent.txt");
	
	if(!log.is_open() || !mostRecent.is_open()){
		return 9;
	}
	
	//Prepare Project array to store data
	Project projects[ARRAYSIZE];
	
	//Parse input files
	parseNewInfo(log, mostRecent, projects);
	log.close();
	mostRecent.close();
	
	//Should contain the Project name of the most recently built project
	time_t max=time(0);
	int highestTimeIndex=0;
	
	for(int i=0;i<projectCount;++i){
		if(projects[i].getModified()>max){
			max=projects[i].getModified();
			highestTimeIndex=i;
		}
	}
	
	string mostRecentlyBuiltProject=projects[highestTimeIndex].getProjectName();
	
	/** READ REPORT.CSV*/
	
	//Prepare file
	ifstream report;
	report.open("report.csv");
	if(!report.is_open()){
		ofstream createReportFile;
		createReportFile.open("report.csv");
		createReportFile.close();
		report.open("report.csv");
	}
	string temp;
	
	//Trash first line
	getline(report,temp,'\n');
	
	while(true){
		getline(report,temp,',');
		
		if(report.eof()){
			break;
		}
		
		int existence=alreadyExists(temp, projects);
		if(existence>-1){
			//Merge entry with entry at index-existence
			
			//Set time spent
			getline(report,temp,',');
			int oldTotalTime=hoursToSeconds(temp);
			
			time_t currentModifiedTime=projects[existence].getModified();
			getline(report,temp,',');
			
			//Parse Date info
			//Date format: Mar 11 08:10:23 2021
			if(mostRecentlyBuiltProject==projects[existence].getProjectName()){
				struct tm tm;
				strptime(temp.c_str(),"%h %d %H:%M:%S %Y",&tm);
				tm.tm_isdst=-1;
				time_t oldModifiedTime=mktime(&tm);
				long timeDifference=currentModifiedTime-oldModifiedTime;
				
				if((timeDifference)<(MINUTESSINCELASTBUILD*60)){
					projects[existence].setSecondsSpent(timeDifference+oldTotalTime);
				}
				else{
					projects[existence].setSecondsSpent(oldTotalTime);
				}
			}
			else{
				projects[existence].setSecondsSpent(oldTotalTime);
			}
			
			//Set build count if this was the project that was just built
			getline(report,temp,',');
			if(mostRecentlyBuiltProject==projects[existence].getProjectName()){
				projects[existence].setBuildCount(stoi(temp)+1);
			}
			else{
				projects[existence].setBuildCount(stoi(temp));
			}
			
			//Set line count- do not change since new line count is more accurate
			getline(report,temp,',');
			
			//Set Path- do not change since new path is more accurate
			getline(report,temp,'\n');
		}
		else{
			//Create new entry with project name temp
			projects[projectCount].setProjectName(temp);
			
			//Set time spent
			getline(report,temp,',');
			projects[projectCount].setSecondsSpent(hoursToSeconds(temp));
			
			//Set time last modified
			getline(report,temp,',');
			struct tm tm;
			strptime(temp.c_str(),"%h %d %H:%M:%S %Y",&tm);
			
			tm.tm_isdst=-1;
			time_t oldModifiedTime=mktime(&tm);
			projects[projectCount].setModified(oldModifiedTime);
			
			//Set build count
			getline(report,temp,',');
			projects[projectCount].setBuildCount(stoi(temp));
			
			//Set line count
			getline(report,temp,',');
			projects[projectCount].setLineCount(stoi(temp));
			
			//Set Path
			getline(report,temp,'\n');
			projects[projectCount].setPathName(temp);
			
			projectCount++;
		}
		
	}
	report.close();
	
	
	/**PRINT TO REPORT.CSV*/
	printReport(projects);
	
}

time_t timeParser(string in){
	string temp;
	istringstream line(in);
	string date="";
	
	//Skip unnecessary file info
	line>>temp;
	line>>temp;
	line>>temp;
	line>>temp;
	line>>temp;
	
	//Start Date info
	line>>temp;
	date+=temp+" ";
	
	line>>temp;
	date+=temp+" ";
	
	line>>temp;
	date+=temp+" ";
	
	line>>temp;
	date+=temp+" ";
	
	//Delete file name
	line>>temp;
	
	//Parse Date info
	//Date format: Mar 11 08:10:23 2021
	struct tm tm;
	strptime(date.c_str(),"%h %d %H:%M:%S %Y",&tm);
	tm.tm_isdst=-1;
	time_t mostRecentTimeModified=mktime(&tm);
	
	return mostRecentTimeModified;
}


static void parseNewInfo(std::ifstream &log, std::ifstream &mostRecent, Project *projects) {
	int index=0;
	string temp;
	while(true){
		//Grabs Project Path Name
		getline(log,temp);
		projects[index].setPathName(temp);
		
		//Grabs Project Time
		getline(mostRecent, temp);
		if(log.eof()){
			break;
		}
		time_t x=timeParser(temp);
		projects[index].setModified(x);
		
		//Sets Project Name
		istringstream tokenizer(projects[index].getPathName());
		getline(tokenizer,temp,'.');
		int strIndex=(int)temp.length()-1;
		while(true){
			if(temp[strIndex]=='/'){
				break;
			}
			strIndex--;
		}
		temp=temp.substr(strIndex+1);
		projects[index].setProjectName(temp);
		
		//Grabs line count
		int count;
		getline(mostRecent, temp);
		count=stoi(temp);
		projects[index].setLineCount(count);
		
		
		index++;
		projectCount++;
	}
}

int alreadyExists(string projectName_in, Project *projects){
	for(int i=0;i<projectCount;++i){
		if(projectName_in==projects[i].getProjectName()){
			return i;
		}
	}
	
	return -1;
}


int hoursToSeconds(string hours){
	istringstream tokens(hours);
	string temp;
	
	getline(tokens,temp,':');
	int hoursAsInt=stoi(temp);
	
	getline(tokens,temp,':');
	int minutes=stoi(temp);
	
	getline(tokens,temp);
	int seconds=stoi(temp);
	
	return hoursAsInt*3600+minutes*60+seconds;
}

string secondsToHours(int seconds){
	int hours=seconds/3600;
	int minutes=(seconds-3600*hours)/60;
	int remainingSeconds=(seconds-3600*hours-60*minutes)%60;
	
	return to_string(hours)+":"+to_string(minutes)+":"+to_string(remainingSeconds);
}


string timeToString(time_t t){
	struct tm * timeinfo;
	char buffer [80];
	
	timeinfo = localtime (&t);
	
	strftime (buffer,80,"%h %d %H:%M:%S %Y",timeinfo);
	
	string result=buffer;
	
	return result;
}

static int printReport(Project *projects) {
	ofstream reportOut;
	reportOut.open("report.csv");
	if(!reportOut.is_open()){	return 7;}
	
	reportOut<<"Project,TimeSpent,LastModified,BuildCount,LineCount,Path\n";
	for(int i=0;i<projectCount;++i){
		reportOut<<projects[i].getProjectName()<<",";
		reportOut<<secondsToHours(projects[i].getSecondsSpent())<<",";
		
		//TODO:Time
		string timeOutput=timeToString(projects[i].getModified());
		reportOut<<timeOutput<<",";
		
		reportOut<<projects[i].getBuildCount()<<",";
		reportOut<<projects[i].getLineCount()<<",";
		
		reportOut<<projects[i].getPathName()<<"\n";
	}
	reportOut.close();
	
	return 0;
}

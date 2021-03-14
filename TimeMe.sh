#! /bin/bash
cd "/Users/mustafasoby/Documents/coding/miniProjects/TimeMe/TimeMe/TimeMe"
osascript TimeMe.scpt

>mostRecent.txt

cat log.txt | while read line || [[ -n $line ]];
do
	#This takes us into the .xcodeproj directory
   cd $line
   #This takes us one directory up
   cd ..
   
   #This grabs the folder name and puts us inside it
   cd $(basename "$line" .xcodeproj)
   
   #Find name of most recently modified file.
   name=$(ls -lTth |head -2 |tail -1)
   
   #date -r main.cpp +%Y%m%d%H%M%S #Gets time of a certain file
   
   #Get line counts
   cppLines=$(wc -l ./*.cpp |tail -1| tr -dc '0-9')
   hppLines=$(wc -l ./*.hpp |tail -1 | tr -dc '0-9')
   
   #Go back to put name of most recently modfied file in log.txt
   cd "/Users/mustafasoby/Documents/coding/miniProjects/TimeMe/TimeMe/TimeMe"
   echo "$name" >> mostRecent.txt
   echo "$((cppLines + hppLines))" >>mostRecent.txt
done

cd "/Users/mustafasoby/Documents/coding/miniProjects/TimeMe/TimeMe/TimeMe"
./TimeMe


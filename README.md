# TimeMe for Xcode C++
## I don't know why this isn't built into Xcode
Xcode is a very sophisticated IDE, yet for some reason they don't have a feature that measures how long you spend on a program. I like Xcode too much to leave it, so I decided to write a custom behavior that checks how long you spent on a project every time you build it. There is an app called wakatime that does this, but it requires too many file permissions that most people would not feel comfortable with. It also backs up all the information to wakatimes database, which is again uncomfortable to deal with. This is a light, user friendly solution to a simple problem.

## How it works
After set up, you do absolutely nothing to maintain this program. It will manage itself. To see how much time you spent on any one project all you need to do is open up `report.csv`

## Setup
### You could just watch my [Youtube Video]("")
### OR
1. Download this project
2. Store it somewhere safe, a place with directories you won't mess around with too much
3. Open up a terminal, and navigate to the location of the script
4. Run the following commands to give the files access to change the files in their directory. (These won't ever change files from other directories)
    i.  `chmod +x TimeMe.scpt` 
    ii. `chmod +x TimeMe.sh`  
    iii.  `chmod +x TimeMe`
5. Open up any Xcode project
  i. Click `Xcode > Behaviors > Edit Behaviors...`
  ii. Click on the first selection in the left panel `Starts`, under the build section
  iii. Scroll to the bottom of the right panel and select run, then select choose script
  iv. Navigate to the `TimeMe.scpt` script and select it.

## That's all
Now anytime you want to see how long you spent on a project just open up `report.csv` and the information will be there.


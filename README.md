# TimeMe for Xcode C++
## I don't know why this isn't built into Xcode
Xcode is a very sophisticated IDE, yet for some reason they don't have a feature that measures how long you spend on a program. I like Xcode too much to leave it, so I decided to write a custom behavior that checks how long you spent on a project every time you build it.

## How it works
After set up, all you need to do is copy the class attributes that you want setters and getters for. Then the script will change what's inside your clipboard. Meaning all you need to do is paste the setters and getters where you want them to go.

For example:
```cpp 
int x;
```

Turns into:
```cpp
void setX(int in){ 
x=in; 
}

int getX(){ 
return x; 
}
```

## Setup
### You could just watch my [Youtube Video]("")
### OR
1. Fork this project
2. Store it somewhere safe, a place with directories you won't mess around with too much
3. Open up a terminal, and navigate to the location of the script
4. Run `chmod +x AutoGenerateSetAndGet.sh` 
5. Open up any Xcode project
1. Click `Xcode > Behaviors > Edit Behaviors...`
2. Add a new behavior by clicking the `+` on the bottom left
3. Name it, and give it a custom shortcut by clicking the little box to the right of it and typing the keys you want to use for this shortcut. For example I used ⌘ + \` 
4. Scroll to the bottom and check run
5. Choose `AutoGenerateSetAndGet.sh`



## That's all
Now every time you want a long list of setters and getters all you need to do is copy your attributes, press the special shortcut, and paste your methods. Hope I helped.


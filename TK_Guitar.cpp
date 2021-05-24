#include <iostream>
#include <string>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

//Thomas Kestler


class Guitar{
public:
Guitar(){//both constructors initialize the guitar to EADGBE tuning
    numberOfFrets=21;
    stringTuning[0]=82.41, stringTuning[1]=110, stringTuning[2]=146.8;
    stringTuning[3]=196, stringTuning[4]=246.9, stringTuning[5]=329.6;
}

Guitar(unsigned char nFrets){//this one takes in a value for numberOfFrets
    numberOfFrets=nFrets;
    stringTuning[0]=82.41, stringTuning[1]=110, stringTuning[2]=146.8;
    stringTuning[3]=196, stringTuning[4]=246.9, stringTuning[5]=329.6;
}

private:
unsigned char numberOfFrets;
double stringTuning[6];//tuning for the 6 strings

public://only public members are methods

bool setFretBoardLength(const unsigned char numFrets){//set private field, make sure input is between 1 and 24
    if(numFrets>=1 && numFrets<=24){
        numberOfFrets=numFrets;
        return true;
    }
    else{
        return false;}
}


//returns frequency for given string and fret
double pitchAt(const char stringNumber, const char fret){
    
    double f = (int)fret;
    double s = stringTuning[(int)stringNumber];

    double pitch = s * (pow(2,(f/12)));
    return pitch;
}

//returns pair object with string/fret combination for given pitch
//it will try to find an exact match or one rounded up or down by 1
//if it cannot, it will return the closest combination to the given pitch
std::pair<double,int> getStringAndFret(double pitch){
    std::pair<double,int> stringFret;
    bool matchFound=false;
    double prevP=0.0;
    double deviation=0.0, prevdev=0.0;
    std::pair<double,int> prevComb;
    for(int i=0;i<numberOfFrets;i++){
    //check each combination of frets and strings to look for a match with the specified pitch
    //when the combination is found, return the string and fret that produced that pitch
        for(int j=0;j<6;j++){
            double currP = stringTuning[j] * (pow(2,(i/12)));
            if(pitch==currP || (((pitch-1)<=currP) && ((pitch+1)>=currP))){//if exact or close enough match is found, stop looping
                std::cout<<"found match: string "<<j<<", fret: "<<i<<", given pitch: "<<pitch<<", calc pitch: "<<currP<<std::endl;
                stringFret = std::make_pair(stringTuning[j],i);
                matchFound=true;
                break;
            }
            deviation = abs(currP-pitch);//take difference between given and calculated pitch for current and previous, and compare the differences
            prevdev=abs(prevP-pitch);
            //deviation 
            if(deviation<prevdev){
                prevP=currP;//only update these values if a closer match is found
                prevComb=std::make_pair(stringTuning[j],i);
                std::cout<<"updating previous values!"<<std::endl;
            }
            prevdev=deviation;
        }
        if(matchFound){
            break;
        }
    }
    
    if(!matchFound){
        std::cout<<"string and fret pair exact match not found. "<<std::endl;
        double d = prevComb.first * (pow(2,(prevComb.second/12)));
        std::cout<<"closest pitch that was found: "<<d<<std::endl;
        return prevComb;
    }
    return stringFret;
}

void tuneString( char string, const double& pitch){//changes tuning for individual string
    int s = (int)string;
    stringTuning[s]=pitch;
    //string parameter specifies the index of the stringTuning array to modify. change the value at 
    //that index to the specified pitch
}

};

int main(){
    Guitar g1;
    Guitar g2(24);
    bool fret = g2.setFretBoardLength(21);
    double d1 = g1.pitchAt(2,5);
    std::cout<<d1<<std::endl;
    g2.tuneString(0,198);//change first string to demonstrate tuneString method
    std::cout<<g2.pitchAt(0,1)<<std::endl;//demonstrates that first string has been changed from 82.41 to 198

    Guitar g3;
    std::pair<double,int> pair1 = g1.getStringAndFret(195.954);//verifies that function can return an exact or close to exact match
    
    std::cout<<pair1.first<<", "<<pair1.second<<std::endl;
    

    //this will verify that getStringAndFret can return a combination closest to the pitch provided
    std::pair<double,int> pair2 = g1.getStringAndFret(170);
    
    std::cout<<pair2.first<<", "<<pair2.second<<std::endl;
    

    return 0;
}
# Guitar
This is a Guitar class that can initialize a Guitar with a fret board length. 
It can calculate a pitch for a given string and fret, return a pair giving a specified string fret combination, 
and change the tuning for an individual string. 

The default and other constructor initializes the guitar to EADGBE tuning.

There are two private fields. numberOfFrets holds the number of frets the guitar has, and the stringTuning array holds the values for the 6 strings of the guitar.
Public methods:
setFretBoardLength changes the private field numberOfFrets to match the input if it is between 1 and 24.
pitchAt takes a string number which indicates the appropriate string value in stringTuning, and takes a fret character. It calculates and returns the frequency for 
the given string and fret.
getStringAndFret takes a pitch as the input and searches for a string/fret pair combination. If it cannot find an exact match, it will use rounding to find a close match or return 
the combination closest to the given pitch.
tuneString takes a pitch and changes the tuning for the specified string.

The main method initializes several Guitar objects and demonstrates each method in the Guitar class.

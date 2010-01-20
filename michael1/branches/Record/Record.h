#include "WPILib.h"
#include <vector>
#include <fstream>

class Record {
	
 public:
  /*I was debating using recordName instead of recordNumber, but then I
  **decided that ints are easier to work with than strings
  */
  Record(void);
  ~Record(void);


  void OpenForSaving(int recordNumber);
  void OpenForPlaying(int recordNumber);//I don't check if the file actually exists
  void Close(int recordNumber);
  void Save(int count, ...);
  vector<double>* Play(void);//Don't forget to dereference this
  bool CanIContinuePlaying(void);//Should be used if you are looping the Play function
 private:
  ofstream *saveFile;
  ifstream *playFile;
  bool areWePlaying;
  bool areWeSaving;
};

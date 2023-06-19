#include <vector>
#include <fstream>
#include <iostream>
using namespace std;


class PageInfo {
  public : char id;
  public : int counter;

  public : PageInfo(char i) {
    id = i, counter = 1;
  } // constructor()

}; // class PageInfo


class Page {
  public : vector<PageInfo*> pageTable, frame;
  public : string referenceString;
  public : int method, frameSize, pageFault, pageReplace;

  public : Page(int m, int fs, string rs) {
    referenceString = rs, 
    method = m, frameSize = fs, pageFault = pageReplace = 0;
    pageTable.clear();
    frame.clear();
  } // constructor


  public : void Paging(ofstream& file) {
    if      (method == 1)     FIFO(file);
    else if (method == 2)      LRU(file);
    else if (method == 3) LFU_FIFO(file);
    else if (method == 4) MFU_FIFO(file);
    else if (method == 5)  LFU_LRU(file);
  } // Paging()


  public : void FIFO(ofstream& file) {
    file << "--------------FIFO-----------------------\n";

    for (int a = 0; a < referenceString.length(); a++) {
      file << referenceString[a] << '\t';

      // RenewPageTable
      PageInfo* now = new PageInfo(referenceString[a]);
      int find = IsThisPageInPageTable(referenceString[a]); // -1   = not find
                                                            // else = index
      if (find == -1) pageTable.push_back(now);
      else            now = pageTable[find];

      // RenewFrame
      find = IsThisPageInFrame(referenceString[a]); // -1   = Not Find 
                                                    // else = index
      if (find == -1) {
        if (frame.size() == frameSize) {
          frame.erase(frame.begin());
          pageReplace++;
        } // if()

        frame.push_back(now);
      } // if()

      PrintFrame(file);

      if (find == -1) {
        file << "\tF";
        pageFault++;
      } // if()

      file << "\n";
    } // for(a)

    PrintPageFault_PageReplace_PageFrame(file);
  } // FIFO()


  public : void LRU(ofstream& file) {
    file << "--------------LRU-----------------------\n";

    for (int a = 0; a < referenceString.length(); a++) {
      file << referenceString[a] << '\t';

      // RenewPageTable
      PageInfo* now = new PageInfo(referenceString[a]);
      int find = IsThisPageInPageTable(referenceString[a]); // -1   = not find
                                                            // else = index
      if (find == -1) pageTable.push_back(now);
      else            now = pageTable[find];

      // RenewFrame
      find = IsThisPageInFrame(referenceString[a]); // -1   = Not Find 
                                                    // else = index
      if (find == -1) {
        if (frame.size() == frameSize) {
          frame.erase(frame.begin());
          pageReplace++;
        } // if()
      } // if()
      else
        frame.erase(frame.begin() + find);

      frame.push_back(now);
      PrintFrame(file);

      if (find == -1) {
        file << "\tF";
        pageFault++;
      } // if()

      file << "\n";
    } // for(a)

    PrintPageFault_PageReplace_PageFrame(file);
  } // LRU()


  public : void LFU_FIFO(ofstream& file) {
    file << "--------------Least Frequently Used Page Replacement-----------------------\n";

    for (int a = 0; a < referenceString.length(); a++) {
      file << referenceString[a] << '\t';

      // RenewPageTable
      PageInfo* now = new PageInfo(referenceString[a]);
      int find = IsThisPageInPageTable(referenceString[a]); // -1   = not find
                                                            // else = index
      if (find == -1) pageTable.push_back(now);
      else            now = pageTable[find];

      // RenewFrame
      find = IsThisPageInFrame(referenceString[a]); // -1   = Not Find 
                                                    // else = index
      if (find == -1) {
        if (frame.size() == frameSize) {
          int index = SearchCounterInFrame("min"); // Search Min Counter In Frame
          frame[index]->counter = 0;
          frame.erase(frame.begin() + index);
          pageReplace++;
        } // if()

        frame.push_back(now);
      } // if()

      PrintFrame(file);

      if (find == -1) {
        file << "\tF";
        pageFault++;
      } // if()

      file << "\n";
    } // for(a)

    PrintPageFault_PageReplace_PageFrame(file);
  } // LFU_FIFO()


  public : void MFU_FIFO(ofstream& file) {
    file << "--------------Most Frequently Used Page Replacement -----------------------\n";

    for (int a = 0; a < referenceString.length(); a++) {
      file << referenceString[a] << '\t';

      // RenewPageTable
      PageInfo* now = new PageInfo(referenceString[a]);
      int find = IsThisPageInPageTable(referenceString[a]); // -1   = not find
                                                            // else = index
      if (find == -1) pageTable.push_back(now);
      else            now = pageTable[find];

      // RenewFrame
      find = IsThisPageInFrame(referenceString[a]); // -1   = Not Find 
                                                    // else = index
      if (find == -1) {
        if (frame.size() == frameSize) {
          int index = SearchCounterInFrame("max"); // Search Max Counter In Frame
          frame[index]->counter = 0;
          frame.erase(frame.begin() + index);
          pageReplace++;
        } // if()

        frame.push_back(now);
      } // if()

      PrintFrame(file);

      if (find == -1) {
        file << "\tF";
        pageFault++;
      } // if()

      file << "\n";
    } // for(a)

    PrintPageFault_PageReplace_PageFrame(file);
  } // MFU_FIFO()


  public : void LFU_LRU(ofstream& file) {
    file << "--------------Least Frequently Used LRU Page Replacement-----------------------\n";

    for (int a = 0; a < referenceString.length(); a++) {
      file << referenceString[a] << '\t';

      // RenewPageTable
      PageInfo* now = new PageInfo(referenceString[a]);
      int find = IsThisPageInPageTable(referenceString[a]); // -1   = not find
                                                            // else = index
      if (find == -1) pageTable.push_back(now);
      else            now = pageTable[find];

      // RenewFrame
      find = IsThisPageInFrame(referenceString[a]); // -1   = Not Find 
                                                    // else = index
      if (find == -1) {
        if (frame.size() == frameSize) {
          int index = SearchCounterInFrame("min"); // Search Min Counter In Frame
          frame[index]->counter = 0;
          frame.erase(frame.begin() + index);
          pageReplace++;
        } // if()
      } // if()
      else
        frame.erase(frame.begin() + find);

      frame.push_back(now);
      PrintFrame(file);

      if (find == -1) {
        file << "\tF";
        pageFault++;
      } // if()

      file << "\n";
    } // for(a)

    PrintPageFault_PageReplace_PageFrame(file);
  } // LFU_LRU()


  public : int IsThisPageInPageTable(char id) {
    for (int a = 0 ; a < pageTable.size(); a++) {
      if (pageTable[a]->id == id) {
        pageTable[a]->counter++;
        return a;
      } // if()
    } // for(a)

    return -1;
  } // IsThisPageInPageTable()


  public : int IsThisPageInFrame(char id) {
    for (int a = 0 ; a < frame.size(); a++)
      if (frame[a]->id == id)
        return a;

    return -1;
  } // IsThisPageInFrame()


  public : void PrintFrame(ofstream& file) {
    for (int a = frame.size() - 1; a >= 0; a--)
      file << frame[a]->id;
  } // PrintFrame()


  public : void PrintPageFault_PageReplace_PageFrame(ofstream& file) {
    file <<   "Page Fault = "    << pageFault 
         << "  Page Replaces = " << pageReplace 
         << "  Page Frames = "   << frameSize   << "\n";
  } // PrintPageFault_PageReplace_PageFrame()


  public : int SearchCounterInFrame(string type) {
    int index = 0, limit = frame[0]->counter;

    for (int b = 1; b < frame.size(); b++)
      if (type == "min" && limit > frame[b]->counter || type == "max" && limit < frame[b]->counter) 
        index = b, limit = frame[b]->counter;

    return index;
  } // SearchCounterInFrame()

}; // class Page


char* StringTransToCharPointer(string s);
int ReadFile(vector<Page*>& allPage, ifstream& file);


int main() {

  while(true) {
    string fileName;
    ifstream inFile;

    do {
      cout << "Please enter the file name (eg. input1, input1_method2) : ";

      getline(cin, fileName);
      //inFile.open(StringTransToCharPointer("input1_method4.txt")); // try to open file
      inFile.open(StringTransToCharPointer(fileName + ".txt")); // try to open file

      if (!inFile) cout << "Input error, please try again.\n\n";
    } while(!inFile);

    vector<Page*> allPage;
    int method = ReadFile(allPage, inFile);
    ofstream outFile;
    outFile.open(StringTransToCharPointer("out_" + fileName + ".txt"));

    if (method != 6) 
      allPage[method - 1]->Paging(outFile);
    else { // All
      for (int a = 0; a < allPage.size() - 1; a++) {
        allPage[a]->Paging(outFile);
        outFile << "\n";
      } // for(a)

      allPage[allPage.size() - 1]->Paging(outFile);
    } // else

    outFile.close();
  } // while(true)
} // main()


char* StringTransToCharPointer(string s) {
  char* fileName = new char[s.length() + 1]; // string transfer to char[]
  for (int a = 0; a < s.length(); a++) fileName[a] = s[a];
  fileName[s.length()] = '\0';
  return fileName;
} // StringTransToCharStar()


int ReadFile(vector<Page*>& allPage, ifstream& inFile) {
  int method, frameSize;
  string referenceString;
  inFile >> method >> frameSize >> referenceString;

  for(int a = 1; a <= 5; a++) {
    Page* p = new Page(a, frameSize, referenceString);
    allPage.push_back(p);
  } // for(a)

  inFile.close();
  return method;
} // ReadFile()

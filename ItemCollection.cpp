#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "ItemCollection.hpp"

using std::string;
using std::ifstream;
using std::cout;
using std::endl;

// function to return the hash value based on the first digit
unsigned int hashfct1(unsigned int barcode) {
  
    unsigned int d;
    d = (barcode / 1000000) % 10;
    return d;
}

// function to return the hash value based on the second digit
unsigned int hashfct2(unsigned int barcode) {
	
    unsigned int d;
    d = (barcode / 100000) % 10;
    return d;
}

// function to return the hash value based on the third digit
unsigned int hashfct3(unsigned int barcode) {
  
    unsigned int d;
    d = (barcode / 10000) % 10;
    return d;
}

// function to return the hash value based on the fourth digit
unsigned int hashfct4(unsigned int barcode) {
  
    unsigned int d;
    d = (barcode / 1000) % 10;
    return d;
}

// function to return the hash value based on the fifth digit
unsigned int hashfct5(unsigned int barcode) {
    
    unsigned int d;
    d = (barcode / 100) % 10;
    return d;
}

// function to return the hash value based on the fourth digit
unsigned int hashfct6(unsigned int barcode) {
    
    unsigned int d;
    d = (barcode / 10) % 10;
    return d;
}

// function to return the hash value based on the fifth digit
unsigned int hashfct7(unsigned int barcode) {
    
    unsigned int d;
    d = barcode% 10;
    return d;
}


// Constructor for struct Item
Item::Item(string itemColor, string itemShape, string itemBrand,
		 unsigned int barcode):itemColor_(itemColor),itemShape_(itemShape), itemBrand_(itemBrand),
				       barcode_(barcode)
{};

// Load information from a text file with the given filename
// THIS FUNCTION IS COMPLETE
void ItemCollection::readTextfile(string filename) {
  ifstream myfile(filename);

  if (myfile.is_open()) {
    cout << "Successfully opened file " << filename << endl;
    string itemColor;
    string itemShape;
    string itemBrand;
    unsigned int barcode;
    while (myfile >> itemColor >> itemShape >> itemBrand >> barcode) {
			if (itemColor.size() > 0)
      	addItem(itemColor, itemShape, itemBrand, barcode);
    }
    myfile.close();
  }
  else
    throw std::invalid_argument("Could not open file " + filename);
}

//adds items to the hashtable
void ItemCollection::addItem(string itemColor, string itemShape, string itemBrand, unsigned int barcode) {
  
  Item glass = {itemColor, itemShape, itemBrand, barcode};
  std::pair<unsigned int, Item> glasses(barcode, glass);

  hT1.insert(glasses);
  hT2.insert(glasses);
  hT3.insert(glasses);
  hT4.insert(glasses);
  hT5.insert(glasses);
  hT6.insert(glasses);
  hT7.insert(glasses);

}

bool ItemCollection::removeItem(unsigned int barcode) {
  // function that removes the pair of glasses specified by the barcode from the display
  // if pair is found, then it is removed and the function returns true
  // else returns false

  hT1.erase(barcode);
  hT2.erase(barcode);
  hT3.erase(barcode);
  hT4.erase(barcode);
  hT5.erase(barcode);
  hT6.erase(barcode);
  hT7.erase(barcode);
    return true;
}

unsigned int ItemCollection::bestHashing() {
  
  // function that decides the best has function, i.e. the ones among
  // fct1-fct7 that creates the most balanced hash table for the current
  // ItemCollection data member allItems


    unsigned int balance[8];
    balance[0] = 1000;

    unsigned int min_loc=0;

    int tempmax1 = 0, tempmax2 = 0, tempmax3 = 0,  tempmax4 = 0, tempmax5 = 0, tempmax6 = 0, tempmax7 = 0;
    int tempmin1 = 1000, tempmin2 = 1000, tempmin3 = 1000, tempmin4 = 1000, tempmin5 = 1000, tempmin6 = 1000, tempmin7 = 1000, minval= 1000;

    for (int i = 0; i < 10; i++) 
    {
        if ((hT1.bucket_size(i) > tempmax1))
            tempmax1 = hT1.bucket_size(i);

        if ((hT1.bucket_size(i) < tempmin1))
            tempmin1 = hT1.bucket_size(i);
      
    }
    balance[1] = tempmax1-tempmin1;

    for (int i = 0; i < 10; i++)
    {
        if ((hT2.bucket_size(i)  > tempmax2))
            tempmax2 = hT2.bucket_size(i);

        if ((hT2.bucket_size(i)  < tempmin2))
            tempmin2 = hT2.bucket_size(i);
    }
    balance[2] = tempmax2-tempmin2;

    for (int i = 0; i < 10; i++)
    {
        if ((hT3.bucket_size(i) > tempmax3))
            tempmax3 = hT3.bucket_size(i);

        if ((hT3.bucket_size(i) < tempmin3))
            tempmin3 = hT3.bucket_size(i);
    }
    balance[3] = tempmax3-tempmin3;

    for (int i = 0; i < 10; i++)
    {
        if ((hT4.bucket_size(i) > tempmax4))
            tempmax4 = hT4.bucket_size(i);

        if ((hT4.bucket_size(i) < tempmin4))
            tempmin4 = hT4.bucket_size(i);
    }
    balance[4] = tempmax4-tempmin4;

    for (int i = 0; i < 10; i++)
    {
        if ((hT5.bucket_size(i) > tempmax5))
            tempmax5 = hT5.bucket_size(i);

        if ((hT5.bucket_size(i) < tempmin5))
            tempmin5 = hT5.bucket_size(i);
    }
    balance[5] = tempmax5-tempmin5;

    for (int i = 0; i < 10; i++)
    {
        if ((hT6.bucket_size(i) > tempmax6))
            tempmax6 = hT6.bucket_size(i);

        if ((hT6.bucket_size(i) < tempmin6))
            tempmin6 = hT6.bucket_size(i);
    }
    balance[6] = tempmax6-tempmin6;

    for (int i = 0; i < 10; i++)
    {
        if ((hT7.bucket_size(i) > tempmax7))
            tempmax7 = hT7.bucket_size(i + 1);

        if ((hT7.bucket_size(i) < tempmin7))
            tempmin7 = hT7.bucket_size(i);
    }
    balance[7] = tempmax7-tempmin7;

    for (int j = 0; j < 7; j++) {
        if ((balance[j]  < minval))
        {
            minval = balance[j];
            min_loc = j;
        }

    }

    return min_loc;
}

// ALREADY COMPLETED
size_t ItemCollection::size() {
    if ((hT1.size() != hT2.size()) || (hT1.size() != hT3.size()) || (hT1.size() != hT4.size()) || (hT1.size() != hT5.size())|| (hT1.size() != hT6.size()) || (hT1.size() != hT7.size()))
  	throw std::length_error("Hash table sizes are not the same");

	return hT1.size();
}

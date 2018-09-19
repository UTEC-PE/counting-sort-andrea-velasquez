#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
--------------------
Counting sort steps
--------------------
numbers = vector to be sorted
1. Create another vector (freq) filled with 0s.
   freq size = max element in numbers - min element in numbers + 1
   Why? Take A1={100, 95, 98} and A2={5, 0, 3}
        If freq size = max element, A1 size would be 100 and A2, 5.
        But A1 is basically the same as A2-95 (95=min element). So,
        to save space we can subtract 95 from all elements in A2.
        The +1 is just there because size=last index+1

2. Count elements in numbers
   Add 1 to the freq element in the position of the numbers element value
   Ex: Put element 65 in freq[65-x] (x = numbers min element)

3. Sum elements in freq to get the sorted positions (begin from index 1)
   Ex: freq = {2,4,1}:  2+4=6 so freq[1]=6
       freq = {2,6,1}:  6+1=7 so freq[2]=7
       freq = {2,6,7}

** Freq will now be the vector with numbers elements new positions **
** (freq index= numbers element, freq value = numbers new position)      **

4. Put sorted numbers elements into a new vector
   4.1 Put element in sorted vector.
   4.2 Decrease the freq element by 1. This will avoid overwritting
   elements with same value (Ex: numbers has two 5's and sortedNumbers ends up with one 5)

   Important: We're mergin 4.1 and 4.2 in --freq[numbers[i]-min] because
   for 4.2: freq[numbers[i]-min]--, but arrays start at 0: freq[numbers[i]-min]-- -1,
   which is equal to --freq[numbers[i]-min]

5. Change unsorted numbers with sortedNumbers
*/

void print(vector<int>& numbers);
void countingSort(vector<int>& numbers);

int main(int argc, char *argv[]) {
    vector<int> numbers = {1, 4, 1, 2, 7, 5, 2};

    print(numbers);
    countingSort(numbers);
    print(numbers);

    system("read");
    return EXIT_SUCCESS;
}

void print(vector<int>& numbers) {
    for (int i = 0; i < numbers.size(); i++) {
        cout << numbers[i] << ' ';
    }
    cout << endl;
}

void countingSort(vector<int>& numbers) {
  //1
  int min = *min_element(numbers.begin(),numbers.end());
  int freqsize = *max_element(numbers.begin(),numbers.end()) - min +1;
  vector <int> freq(freqsize, 0);
  vector <int> sortedNumbers(numbers.size());

  for (int i=0; i<numbers.size(); ++i) ++freq[numbers[i]-min]; //2
  for (int i=1; i<freqsize;++i) freq[i]+=freq[i-1]; //3
  for (int i=0; i<numbers.size();++i) sortedNumbers[ --freq[numbers[i]-min]] = numbers[i]; //4
  numbers = sortedNumbers; //5
}

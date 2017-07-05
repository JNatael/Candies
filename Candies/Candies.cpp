//Defines the entry point for the console application.
#include <iostream>
#include <vector>
#include <numeric>
#include <math.h>
using namespace std;

/*
This function reads a line of int values into a vector function and returns that
vector.
*/
vector<int> readlineofints(int count) {
    // Input values
    vector<int> linevalues(count);
    for (int j = 0; j < count; j++) {
        int val;
        cin >> val;
        linevalues[j] = val;
    }
    return linevalues; // Return line values as a vector
}

/*Program to find the GCD of two input values
*/
unsigned long long gcd(unsigned long long a, unsigned long long b) {
    if (b == 0) { return a; }
    else {
        return gcd(b, a % b);
    }
}

//Calculate the LCM via the GCD
//Checked https://www.quora.com/How-do-I-find-the-LCM-of-three-numbers to verify the LCM properties in writing this
unsigned long long lcm(unsigned long long a, unsigned long long b) {
    return a*b / gcd(a, b);
}

/*Build, by brute force recursion, all possible combinations of attendees
*/
void combo_builder(int depth, int n, vector<long long> &combos, const vector<int> &candies, bool attending[15]) {
    //If we're at the last attendee, record how many candies they took
    if (depth == n) {
        long long result = 0;
        for (int i = 0; i < n; i++) {
            if (attending[i]) { result += candies[i]; } //For each person attending add their candy draw to the count
        }
        if (result != 0) { //If at least someone is attending
            combos.push_back(result+1); //Record this result plus the one the host takes
        }
        return;
    }

    //Calculate a sum with this friend attending
    bool new_attending[15];
    for (int j = 0; j < 15; j++) { new_attending[j] = attending[j]; } //Initialize new attending
    new_attending[depth] = true; //Set this friend to attending
    combo_builder(depth + 1, n, combos, candies, new_attending); //Start path with new attending
        
        
    //Calculate a sum with this friend not attending
    new_attending[depth] = false;
    combo_builder(depth + 1, n, combos, candies, new_attending); //Start path with new not attending
}



int main() {
    std::ios_base::sync_with_stdio(false);

    // get test case count
    int t;
    std::cin >> t;

    //! loop over all the test cases
    for (int i = 1; i <= t; i++) {
        // Read in params
        vector<int> params = readlineofints(1);
        long n = params[0];

        vector<int> candies = readlineofints(n);

        unsigned long long product = 1;

        //Calculate all possible combinations of friends
        vector<long long> combos;
        //Iterate over depth of friends
        bool attending[15] = { 0 }; //Bool array of false values
        combo_builder(0, n, combos, candies, attending); //Calculate possible combinations of friends + host

        //Calculate LCM of all combos of friends
        unsigned long long int_lcm;
        if (n > 1) { //If more than one friend came
            int_lcm = lcm(combos[0], combos[1]);
            for (int i = 2; i < combos.size(); i++) {
                int_lcm = lcm(int_lcm, combos[i]);

            }
        }
        else { //If only one friend came, set LCM to the only combo
            int_lcm = combos[0];
        }

        //Print output
        std::cout << "Case #" << i << ": " << int_lcm << std::endl;
    }
    return 0;
}
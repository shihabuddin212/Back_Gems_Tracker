#include <iostream>
#include <vector>
using namespace std;

class SumOfSubsets {
private:
    vector<int> set;
    vector<int> subset;
    int targetSum;
    int n;
    bool found;
    
    // Print current subset
    void printSubset() {
        cout << "Subset found: { ";
        for (int i = 0; i < subset.size(); i++) {
            cout << subset[i] << " ";
        }
        cout << "}" << endl;
    }
    
    // Check if remaining elements can reach target sum
    bool isPromising(int index, int currentSum, int remainingSum) {
        // If current sum equals target, we found a solution
        if (currentSum == targetSum) {
            return true;
        }
        
        // If current sum exceeds target or no more elements left
        if (currentSum > targetSum || index >= n) {
            return false;
        }
        
        // Check if it's possible to reach target with remaining elements
        if (currentSum + remainingSum < targetSum) {
            return false;
        }
        
        return true;
    }
    
    // Recursive backtracking function
    void findSubsets(int index, int currentSum, int remainingSum) {
        // If we found a solution
        if (currentSum == targetSum) {
            printSubset();
            found = true;
            return;
        }
        
        // If not promising, return
        if (!isPromising(index, currentSum, remainingSum)) {
            return;
        }
        
        // If there are more elements to consider
        if (index < n) {
            // Include current element
            subset.push_back(set[index]);
            findSubsets(index + 1, currentSum + set[index], remainingSum - set[index]);
            
            // Backtrack: exclude current element
            subset.pop_back();
            findSubsets(index + 1, currentSum, remainingSum - set[index]);
        }
    }
    
public:
    SumOfSubsets(vector<int>& inputSet, int target) {
        set = inputSet;
        targetSum = target;
        n = set.size();
        found = false;
        
        // Sort the set in ascending order for better pruning
        sort(set.begin(), set.end());
    }
    
    void solve() {
        cout << "Finding subsets with sum = " << targetSum << endl;
        cout << "Set: { ";
        for (int i = 0; i < n; i++) {
            cout << set[i] << " ";
        }
        cout << "}" << endl << endl;
        
        // Calculate total sum
        int totalSum = 0;
        for (int i = 0; i < n; i++) {
            totalSum += set[i];
        }
        
        // Check if solution is possible
        if (totalSum < targetSum) {
            cout << "No solution possible. Total sum is less than target." << endl;
            return;
        }
        
        findSubsets(0, 0, totalSum);
        
        if (!found) {
            cout << "No subset found with sum = " << targetSum << endl;
        }
    }
};

// Function to find all subsets (alternative approach)
void findAllSubsets(vector<int>& set, int target) {
    int n = set.size();
    bool found = false;
    
    cout << "\nFinding ALL subsets with sum = " << target << ":" << endl;
    
    // Generate all possible subsets using bit manipulation
    for (int i = 0; i < (1 << n); i++) {
        vector<int> subset;
        int sum = 0;
        
        // Check each bit
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                subset.push_back(set[j]);
                sum += set[j];
            }
        }
        
        // If sum matches target
        if (sum == target) {
            cout << "{ ";
            for (int k = 0; k < subset.size(); k++) {
                cout << subset[k] << " ";
            }
            cout << "}" << endl;
            found = true;
        }
    }
    
    if (!found) {
        cout << "No subset found with sum = " << target << endl;
    }
}

int main() {
    int n, target;
    
    cout << "Sum of Subsets Problem" << endl;
    cout << "======================" << endl;
    
    cout << "Enter number of elements: ";
    cin >> n;
    
    vector<int> set(n);
    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; i++) {
        cin >> set[i];
    }
    
    cout << "Enter target sum: ";
    cin >> target;
    
    cout << endl;
    
    // Method 1: Backtracking (finds first solution)
    cout << "Method 1: Backtracking (First Solution)" << endl;
    cout << "========================================" << endl;
    SumOfSubsets solver(set, target);
    solver.solve();
    
    // Method 2: Find all solutions
    cout << "\nMethod 2: All Solutions (Bit Manipulation)" << endl;
    cout << "===========================================" << endl;
    findAllSubsets(set, target);
    
    return 0;
}

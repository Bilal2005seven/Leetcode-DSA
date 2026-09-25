class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {

        vector<int> freq(26, 0);

        // Count frequency of each task
        for (char task : tasks) {
            freq[task - 'A']++;
        }

        // Find maximum frequency
        int maxFreq = 0;

        for (int f : freq) {
            maxFreq = max(maxFreq, f);
        }

        // How many tasks have the maximum frequency?
        int countMax = 0;

        for (int f : freq) {
            if (f == maxFreq) {
                countMax++;
            }
        }

        int totalTasks = tasks.size();

        int answer = (maxFreq - 1) * (n + 1) + countMax;

        return max(totalTasks, answer);
    }
};
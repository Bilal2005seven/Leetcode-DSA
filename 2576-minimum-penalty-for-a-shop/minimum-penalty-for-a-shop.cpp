class Solution {
public:
    int bestClosingTime(string customers) {
        int penalty = 0;
        
        // Initial penalty: shop closed all day (j = 0)
        for (char c : customers) {
            if (c == 'Y') penalty++;
        }

        int minPenalty = penalty;
        int bestHour = 0;

        // Traverse hours
        for (int i = 0; i < customers.size(); i++) {
            if (customers[i] == 'Y')
                penalty--;   // opening helps
            else
                penalty++;   // opening hurts

            // i + 1 is the closing hour after this hour
            if (penalty < minPenalty) {
                minPenalty = penalty;
                bestHour = i + 1;
            }
        }

        return bestHour;
    }
};

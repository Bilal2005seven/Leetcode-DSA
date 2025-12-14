class Solution {
public:
    int numberOfWays(string corridor) {
        const int MOD = 1e9 + 7;
        
        long long ways = 1;
        int seatCount = 0;
        int plantCount = 0;
        
        for (char c : corridor) {
            if (c == 'S') {
                seatCount++;
                
                // If this is the first seat of a new pair
                if (seatCount > 2 && seatCount % 2 == 1) {
                    ways = (ways * (plantCount + 1)) % MOD;
                    plantCount = 0;
                }
            } else { // 'P'
                if (seatCount >= 2 && seatCount % 2 == 0) {
                    plantCount++;
                }
            }
        }
        
        // Total seats must be even and at least 2
        if (seatCount < 2 || seatCount % 2 != 0) {
            return 0;
        }
        
        return ways;
    }
};

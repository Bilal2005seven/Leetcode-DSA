class Solution {
public:
    int climbStairs(int n) {
        if( n<= 1) return 1 ;
        int first = 1 ;
        int second = 2 ;
        for(int i=3 ; i<=n ; i++){
            int curr = first + second ;
            first = second ;
            second = curr ;
        } return second ;
    }
};
class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        int left = 0;
        int right = 0;
        int max_len = 0;
        unordered_map<int,int>mpp ;
        while(right < fruits.size()){
            mpp[fruits[right]]++;
            while(mpp.size() > 2){
                mpp[fruits[left]]--;
                if(mpp[fruits[left]] == 0){
                    mpp.erase(fruits[left]) ;
                }
                left++;
            }
            if(mpp.size() <= 2){
                max_len = max(max_len , right-left+1) ;
            }
            right++;
        }return max_len ;
    }
};
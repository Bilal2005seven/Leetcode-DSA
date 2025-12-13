class Solution {
public:
    vector<string> validateCoupons(vector<string>& code,
                                   vector<string>& businessLine,
                                   vector<bool>& isActive) {

        // Fixed business line order
        unordered_map<string, int> priority = {
            {"electronics", 0},
            {"grocery", 1},
            {"pharmacy", 2},
            {"restaurant", 3}
        };

        vector<pair<int, string>> validCoupons;

        for (int i = 0; i < code.size(); i++) {

            // Condition 1: must be active
            if (!isActive[i]) continue;

            // Condition 2: valid business line
            if (!priority.count(businessLine[i])) continue;

            // Condition 3: valid code
            if (code[i].empty()) continue;

            bool valid = true;
            for (char c : code[i]) {
                if (!isalnum(c) && c != '_') {
                    valid = false;
                    break;
                }
            }
            if (!valid) continue;

            // store (business order, code)
            validCoupons.push_back({priority[businessLine[i]], code[i]});
        }

        // Sort by businessLine order, then lexicographically by code
        sort(validCoupons.begin(), validCoupons.end(),
             [](const auto& a, const auto& b) {
                 if (a.first != b.first)
                     return a.first < b.first;
                 return a.second < b.second;
             });

        // Extract result
        vector<string> result;
        for (auto& p : validCoupons)
            result.push_back(p.second);

        return result;
    }
};

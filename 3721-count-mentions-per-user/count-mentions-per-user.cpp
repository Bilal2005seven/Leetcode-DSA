class Solution {
public:
    vector<int> countMentions(int numberOfUsers, vector<vector<string>>& events) {
        vector<int> mentions(numberOfUsers, 0);
        vector<bool> online(numberOfUsers, true);

        // (timestamp, type, user/message)
        struct Event {
            int ts;
            int type; // 0=OFFLINE, 1=MESSAGE
            string data;
        };

        vector<Event> ev;

        // Convert and store
        for (auto &e : events) {
            int ts = stoi(e[1]);
            int type = (e[0] == "OFFLINE" ? 0 : 1);
            ev.push_back({ts, type, e[2]});
        }

        // Sort by timestamp, and OFFLINE before MESSAGE at same timestamp
        sort(ev.begin(), ev.end(), [](auto &a, auto &b) {
            if (a.ts != b.ts) return a.ts < b.ts;
            return a.type < b.type;
        });

        // Min-heap to restore users at the correct time
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

        for (auto &e : ev) {
            int ts = e.ts;

            // Restore users whose timers expired
            while (!pq.empty() && pq.top().first <= ts) {
                online[pq.top().second] = true;
                pq.pop();
            }

            if (e.type == 0) { 
                // OFFLINE
                int uid = stoi(e.data);
                if (online[uid]) {
                    online[uid] = false;
                    pq.push({ts + 60, uid});
                }
            } 
            else {
                // MESSAGE
                const string &msg = e.data;
                
                if (msg == "ALL") {
                    for (int i = 0; i < numberOfUsers; i++) mentions[i]++;
                } 
                else if (msg == "HERE") {
                    for (int i = 0; i < numberOfUsers; i++)
                        if (online[i]) mentions[i]++;
                } 
                else {
                    // tokens like: id3 id1 id3
                    stringstream ss(msg);
                    string t;
                    while (ss >> t) {
                        int uid = stoi(t.substr(2));
                        mentions[uid]++;
                    }
                }
            }
        }

        return mentions;
    }
};

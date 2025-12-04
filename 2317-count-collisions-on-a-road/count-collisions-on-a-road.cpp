class Solution {
public:
    int countCollisions(string directions) {
        int n = directions.size();
        int left = 0, right = n - 1;

        // Ignore all 'L' on the far left
        while (left < n && directions[left] == 'L') left++;

        // Ignore all 'R' on the far right
        while (right >= 0 && directions[right] == 'R') right--;

        int collisions = 0;
        // All remaining R or L will collide
        for (int i = left; i <= right; i++) {
            if (directions[i] != 'S') collisions++;
        }

        return collisions;
    }
};

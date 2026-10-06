class LRUCache {
private:

    // Node of doubly linked list
    struct Node {
        int key;
        int value;
        Node* prev;
        Node* next;

        Node(int k, int v) {
            key = k;
            value = v;
            prev = nullptr;
            next = nullptr;
        }
    };

    int capacity;

    // key -> address of node
    unordered_map<int, Node*> mp;

    // Dummy nodes
    Node* head;
    Node* tail;

    // Remove a node from the list
    void removeNode(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    // Add node just before tail = MRU position
    void addToFront(Node* node) {
        node->next = head->next;
        node->prev = head;

        head->next->prev = node;
        head->next = node;
    }

public:

    LRUCache(int capacity) {
        this->capacity = capacity;

        head = new Node(0, 0);
        tail = new Node(0, 0);

        head->next = tail;
        tail->prev = head;
    }

    int get(int key) {

        // Key doesn't exist
        if (mp.find(key) == mp.end()) {
            return -1;
        }

        Node* node = mp[key];

        // This node was just used,
        // so move it to MRU position
        removeNode(node);
        addToFront(node);

        return node->value;
    }

    void put(int key, int value) {

        // Key already exists
        if (mp.find(key) != mp.end()) {

            Node* node = mp[key];

            // Update value
            node->value = value;

            // Move to MRU
            removeNode(node);
            addToFront(node);

            return;
        }

        // Create new node
        Node* node = new Node(key, value);

        mp[key] = node;
        addToFront(node);

        // Cache is full
        if (mp.size() > capacity) {

            // LRU node
            Node* lru = tail->prev;

            // Remove from hashmap
            mp.erase(lru->key);

            // Remove from linked list
            removeNode(lru);

            // Free memory
            delete lru;
        }
    }
};
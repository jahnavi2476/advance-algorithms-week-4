#include <iostream>
#include <queue>
#include <unordered_map>
#include <climits>

using namespace std;

struct Node
{
    string name;
    unordered_map<Node *, int> neighbors;
};

struct CompareDist
{
    bool operator()(pair<Node *, int> n1, pair<Node *, int> n2)
    {
        return n1.second > n2.second;
    }
};

void addEdge(Node *node1, Node *node2, int cost)
{
    node1->neighbors[node2] = cost;
    node2->neighbors[node1] = cost;
}

pair<int, vector<string>> dijkstra(Node *start, Node *end)
{
    priority_queue<pair<Node *, int>, vector<pair<Node *, int>>, CompareDist> toVisit;
    unordered_map<Node *, int> dist;
    unordered_map<Node *, vector<string>> path;

    for (auto &neighbor : start->neighbors)
    {
        dist[neighbor.first] = INT_MAX;
    }
    toVisit.push({start, 0});
    dist[start] = 0;
    path[start] = {start->name};

    while (!toVisit.empty())
    {
        Node *curr = toVisit.top().first;
        int currDist = toVisit.top().second;
        toVisit.pop();

        for (auto &neighbor : curr->neighbors)
        {
            int oldDist = dist[neighbor.first];
            int newDist = currDist + neighbor.second;
            if (newDist < oldDist)
            {
                toVisit.push({neighbor.first, newDist});
                dist[neighbor.first] = newDist;
                path[neighbor.first] = path[curr];
                path[neighbor.first].push_back(neighbor.first->name);
            }
        }
        if (curr == end)
        {
            break;
        }
    }
    return {dist[end], path[end]};
}

int main()
{
    Node *a = new Node{"A"};
    Node *b = new Node{"B"};
    Node *c = new Node{"C"};
    Node *d = new Node{"D"};
    Node *e = new Node{"E"};

    addEdge(a, b, 1);
    addEdge(a, c, 3);
    addEdge(b, c, 2);
    addEdge(b, d, 5);
    addEdge(c, e, 4);
    addEdge(d, e, 1);

    string startName, endName;
    cout << "Enter start node: ";
    cin >> startName;
    cout << "Enter end node: ";
    cin >> endName;

    Node *start = (startName == "A" ? a : startName == "B" ? b
                                      : startName == "C"   ? c
                                      : startName == "D"   ? d
                                                           : e);
    Node *end = (endName == "A" ? a : endName == "B" ? b
                                  : endName == "C"   ? c
                                  : endName == "D"   ? d
                                                     : e);

    pair<int, vector<string>> result = dijkstra(start, end);

    cout << "Shortest path: ";
    for (string node : result.second)
    {
        cout << node << " ";
    }
    cout << "\nCost: " << result.first << endl;

    return 0;
}

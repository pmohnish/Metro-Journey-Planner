#include <iostream>
#include <queue>
#include <map>
#include <limits>

using namespace std;

const int MAX_STATIONS = 4;

// Define a structure to represent a metro station
struct Station {
    string name;
    int numNeighbours;
    int neighbours[10]; // Assuming a maximum of 10 neighbors per station
    int distances[10]; // Corresponding distances to neighbors
};

// Function to find the shortest path from start station to end station using Dijkstra's algorithm
void dijkstra(Station metro[], int start, int end) {
    int distance[MAX_STATIONS];
    int parent[MAX_STATIONS];
    bool visited[MAX_STATIONS] = {false};

    for (int i = 0; i < MAX_STATIONS; ++i) {
        distance[i] = numeric_limits<int>::max();
        parent[i] = -1;
    }

    distance[start] = 0;

    for (int i = 0; i < MAX_STATIONS - 1; ++i) {
        int minDist = numeric_limits<int>::max();
        int minIndex = -1;

        for (int j = 0; j < MAX_STATIONS; ++j) {
            if (!visited[j] && distance[j] < minDist) {
                minDist = distance[j];
                minIndex = j;
            }
        }

        if (minIndex == -1)
            break;

        visited[minIndex] = true;

        for (int j = 0; j < metro[minIndex].numNeighbours; ++j) {
            int neighbour = metro[minIndex].neighbours[j];
            int edgeWeight = metro[minIndex].distances[j];

            if (!visited[neighbour] && distance[minIndex] + edgeWeight < distance[neighbour]) {
                distance[neighbour] = distance[minIndex] + edgeWeight;
                parent[neighbour] = minIndex;
            }
        }
    }

    // Reconstruct the path from end to start
    int path[MAX_STATIONS];
    int pathIndex = 0;
    int curr = end;
    while (curr != -1) {
        path[pathIndex++] = curr;
        curr = parent[curr];
    }

    cout << "Shortest path from " << metro[start].name << " to " << metro[end].name << ": ";
    for (int i = pathIndex - 1; i >= 0; --i) {
        cout << metro[path[i]].name << " ";
    }
    cout << endl;
}

int main() {
    Station metro[MAX_STATIONS] = {
        {"S1", 2, {1, 2}, {5, 3}},
        {"S2", 3, {0, 2, 3}, {5, 2, 4}},
        {"S3", 3, {0, 1, 3}, {3, 2, 7}},
        {"S4", 2, {1, 2}, {4, 7}}
    };

    cout << "Available stations:" << endl;
    for (int i = 0; i < MAX_STATIONS; ++i) {
        cout << i << ". " << metro[i].name << endl;
    }

    int startStation, endStation;
    cout << "Enter the index of the start station: ";
    cin >> startStation;

    cout << "Enter the index of the end station: ";
    cin >> endStation;

    if (startStation < 0 || startStation >= MAX_STATIONS ||
        endStation < 0 || endStation >= MAX_STATIONS) {
        cout << "Invalid station indices." << endl;
        return 1;
    }

    dijkstra(metro, startStation, endStation);

    return 0;
}


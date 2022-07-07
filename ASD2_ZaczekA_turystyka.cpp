#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Vertex;

void passengersConversion(vector<Vertex> &vector1);

void readVertex(int d, vector<Vertex> &vector1);

bool compareTo(Vertex vertex1, Vertex vertex2);

int search(int position, int *city);

void neighbors(vector<Vertex> &mst, vector<vector<int>> &vector1);

void fillIn(bool *visited, int m);

int passengersNo(vector<Vertex> &mst, vector<int> &routes);

int routesNo(int t, int p);

void visit(bool visited[], vector<vector<int>> &nearest, vector<int> &route, int s, int e, int *x);


class Vertex {
public:
    int cityA;
    int cityB;
    int numberOfPassengers;

    Vertex(int cityA, int cityB, int numberOfPassengers) {
        this->cityA = cityA;
        this->cityB = cityB;
        this->numberOfPassengers = numberOfPassengers;
    };

    void conversion() {
        this->numberOfPassengers = this->numberOfPassengers * -1;
    };
};

void kruskalAlgorithm(int vertexNo, vector<Vertex> &possibleRoutes, vector<Vertex> &completedRoutes) {
    int *cities = new int[vertexNo];
    int cnt = 0, j = 0;

    for (int i = 0; i < vertexNo; i++) {
        cities[i] = i;
    }

    int position = 0;
    while (cnt < vertexNo - 1) {
        j = position;
        if (j == possibleRoutes.size()) {
            break;
        }

        int start_city = search(possibleRoutes[position].cityA - 1, cities);
        int destination_city = search(possibleRoutes[position].cityB - 1, cities);
        if (destination_city != start_city) {
            int tym = 0;
            if (possibleRoutes[position].cityA > possibleRoutes[position].cityB) {
                tym = possibleRoutes[position].cityB;
                possibleRoutes[position].cityB = possibleRoutes[position].cityA;
                possibleRoutes[position].cityA = tym;
            }
            completedRoutes.push_back(possibleRoutes[position]);
            tym = possibleRoutes[position].cityA;
            possibleRoutes[position].cityA = possibleRoutes[position].cityB;
            possibleRoutes[position].cityB = tym;
            completedRoutes.push_back(possibleRoutes[position]);
            cnt++;
            cities[start_city] = destination_city;
        }
        position++;
    }
    delete[]cities;
    possibleRoutes.clear();
}

void passengersConversion(vector<Vertex> &vector1) {
    for (int i = 0; i < vector1.size(); i++) {
        vector1[i].conversion();
    }
}

void readVertex(int d, vector<Vertex> &vector1) {
    int cityA, cityB, numberOfPassengers;
    for (int i = 0; i < d; i++) {
        cin >> cityA >> cityB >> numberOfPassengers;
        vector1.emplace_back(cityA, cityB, numberOfPassengers);
    }
}

bool compareTo(Vertex vertex1, Vertex vertex2) {
    return vertex1.numberOfPassengers < vertex2.numberOfPassengers;
}

int search(int position, int *city) {
    if (city[position] == position)
        return position;
    return search(city[position], city);
}

void neighbors(vector<Vertex> &mst, vector<vector<int>> &vector) {
    for (auto &i : mst) {
        vector[i.cityA].push_back(i.cityB);
    }
}

void fillIn(bool *visited, int m) {
    for (int i = 0; i <= m; i++) {
        visited[i] = false;
    }
}

int passengersNo(vector<Vertex> &mst, vector<int> &routes) {
    int passengers = 1000000;
    for (int i = 1; i < routes.size() - 1; i++) {
        for (auto &j : mst) {
            if (j.cityA == routes[i] && j.cityB == routes[i + 1]) {
                if (passengers > j.numberOfPassengers) {
                    passengers = j.numberOfPassengers;
                }
            }
        }
    }
    return passengers;
}

int routesNo(int t, int p) {
    int sum = 0;
    while (t > 0) {
        t -= p;
        sum++;
    }
    return sum;
}

void visit(bool visited[], vector<vector<int>> &nearest, vector<int> &route, int s, int e, int *x) {
    visited[s] = true;
    for (int i = 0; i < nearest[s].size(); i++) {
        if (s == e) {
            break;
        }
        *x = nearest[s][i];
        if (!visited[*x]) {
            if (route.back() == s) {
                route.pop_back();
            }
            route.push_back(s);
            if (*x == e) {
                route.push_back(e);
                break;
            }
            visit(visited, nearest, route, *x, e, x);
            if (*x == e) {
                break;
            }
        }
    }
    if (*x != e) {
        if (nearest[s].back() == *x) {
            visited[*x] = false;
            nearest[s].pop_back();
            for (int j = 0; j < nearest[*x].size(); j++) {
                if (nearest[*x][j] == s) {
                    nearest[*x].erase(nearest[*x].begin() + j);
                }
            }
            route.pop_back();
            visit(visited, nearest, route, *x, e, x);
        }
    }
}

int main() {
    int numberOfPassengers, v, vertexNo, linesNo, cityA = -1, cityB = -1;
    cin >> vertexNo;
    cin >> linesNo;
    vector<Vertex> possibleRoutes;
    vector<Vertex> completedRoutes;
    readVertex(linesNo, possibleRoutes);
    passengersConversion(possibleRoutes);
    sort(possibleRoutes.begin(), possibleRoutes.end(), compareTo);
    kruskalAlgorithm(vertexNo, possibleRoutes, completedRoutes);
    passengersConversion(completedRoutes);

    while (cityA != 0 && cityB != 0) {
        int x = 0;
        vector<vector<int>> nearby(vertexNo + 1);
        neighbors(completedRoutes, nearby);
        cin >> cityA;
        cin >> cityB;
        if (cityA == 0 && cityB == 0) {
            break;
        }
        cin >> v;
        vector<int> route;
        route.push_back(0);
        bool *visited = new bool[vertexNo + 1];
        fillIn(visited, vertexNo);
        visit(visited, nearby, route, cityA, cityB, &x);
        numberOfPassengers = passengersNo(completedRoutes, route);
        cout << routesNo(v, numberOfPassengers - 1);
        cout << endl;

        cityA = -1;
        cityB = -1;

        for (auto &i : nearby) {
            i.clear();
        }

        route.clear();
        delete[]visited;
        nearby.clear();
    }
    completedRoutes.clear();
    return 0;
}
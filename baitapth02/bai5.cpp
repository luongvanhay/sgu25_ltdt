#include <bits/stdc++.h>
using namespace std;

//  1. Ma trận kề sang danh sách kề
vector<vector<int>> MaTranKeSangDanhSachKe(vector<vector<int>> &A) {
    int n = A.size();
    vector<vector<int>> ds(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (A[i][j]) ds[i].push_back(j);
        }
    }
    return ds;
}

//  2. Ma trận kề sang danh sách cạnh
vector<pair<int,int>> MaTranKeSangDanhSachCanh(vector<vector<int>> &A) {
    int n = A.size();
    vector<pair<int,int>> canh;
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            if (A[i][j]) canh.push_back({i, j});
        }
    }
    return canh;
}

//  3. Danh sách kề sang ma trận kề
vector<vector<int>> DanhSachKeSangMaTranKe(vector<vector<int>> &ds) {
    int n = ds.size();
    vector<vector<int>> A(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j : ds[i]) {
            A[i][j] = 1;
        }
    }
    return A;
}

//  4. Danh sách kề sang danh sách cạnh
vector<pair<int,int>> DanhSachKeSangDanhSachCanh(vector<vector<int>> &ds) {
    int n = ds.size();
    vector<pair<int,int>> canh;
    for (int i = 0; i < n; i++) {
        for (int j : ds[i]) {
            if (i < j) canh.push_back({i, j}); // tránh trùng cạnh
        }
    }
    return canh;
}

//  5. Danh sách cạnh sang ma trận kề
vector<vector<int>> DanhSachCanhSangMaTranKe(int n, vector<pair<int,int>> &canh) {
    vector<vector<int>> A(n, vector<int>(n, 0));
    for (auto [u, v] : canh) {
        A[u][v] = A[v][u] = 1;
    }
    return A;
}

//  6. Danh sách cạnh sang danh sách kề
vector<vector<int>> DanhSachCanhSangDanhSachKe(int n, vector<pair<int,int>> &canh) {
    vector<vector<int>> ds(n);
    for (auto [u, v] : canh) {
        ds[u].push_back(v);
        ds[v].push_back(u);
    }
    return ds;
}

#include <bits/stdc++.h>
#include <chrono>
#include <random>
using namespace std;
using namespace chrono;

vector<vector<int>> mask;
vector<vector<int>> terrain;

const int direction_count = 8;
const int low = 1;
const int high = 11;

const int dx[direction_count] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dy[direction_count] = {-1, 0, 1, -1, 1, -1, 0, 1};

int rand(int low, int high)
{
    mt19937 generator(steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> distribution(low, high);
    return distribution(generator);
}

bool is_valid_block(int x, int y)
{
    return x >= 0 and x < mask.size() and y >= 0 and y < mask[0].size();
}

void terrain_mask(int n, int d)
{
    for (auto &row: mask)
    {
        for (auto &block: row)
        {
            block = rand(low, high);
        }
    }
}

void terrain_smooth(int n, int d)
{
    int max_height = INT_MIN, min_height = INT_MAX;

    for (int i = 0; i < terrain.size(); i++)
    {
        for (int j = 0; j < terrain[i].size(); j++)
        {
            int average = 0;
            for (int direction = 0; direction < direction_count; direction++)
            {
                int curr_block_x = i + dx[direction], curr_block_y = j + dy[direction];
                if (is_valid_block(curr_block_x, curr_block_y))
                {
                    average += mask[curr_block_x][curr_block_y];
                }
            }
            average = round((double)average / direction_count);
            terrain[i][j] = rand(average - d, average + d);
            max_height = max(max_height, terrain[i][j]);
            min_height = min(min_height, terrain[i][j]);
        }
    }
    cout << max_height << " " << min_height << "\n";
}

int main()
{
    freopen("test.txt", "r", stdin);
    freopen("terrain.txt", "w", stdout);

    int n;
    cin >> n;
    mask.resize(n, vector<int>(n));
    terrain.resize(n, vector<int>(n));
    for (int i = 1; i <= n; i++)
    {
        cerr << "n = " << n << ", d = " << i << "\n";
        terrain_mask(n, i);
        cerr << "Generated mask \n";
        for (const auto j: mask)
        {
            for (const auto k: j)
            {
                cerr << k << " ";
            }
            cerr << "\n";
        }

        terrain_smooth(n, i);
        cerr << "Generated terrain: \n";
        for (const auto j: terrain)
        {
            for (const auto k: j)
            {
                cout << k << " ";
                cerr << k << " ";
            }
            cout << "\n";
            cerr << "\n";
        }
    }
    return 0;
}
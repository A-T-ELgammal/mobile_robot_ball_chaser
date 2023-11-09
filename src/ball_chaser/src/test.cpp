#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<int> data(36, 0);
    data[8] = data[9] = data[10] = 255;

    for (int rUnit = 0; rUnit < data.size(); rUnit++)
    {
        if (data[rUnit] == 255)
        {
            for (int j = 1; j < 3; j++, rUnit += j)
                if (data[rUnit] != 255)
                    break;
        }
    }
    return 0;
}
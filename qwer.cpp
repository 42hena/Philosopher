#include <iostream>
using namespace std;

int arr[100000];
int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0 ; i < n ; ++i)
    {
        scanf("%d", &arr[i]);
    }

    int lo = 0;
    int hi = 1e9;

    int ans = 0;
    while (lo + 1 < hi)
    {
        int mid = (lo + hi) / 2;

        int now_money = mid;
        int count = 1;
        int n_count = 0;
        bool flag = false;
        for (int i = 0 ; i < n ; ++i)
        {
            if (now_money - arr[i] >= 0)
                now_money -= arr[i];
            else
            {
                now_money = mid;
                if (now_money - arr[i] < 0)
                {
                    lo = mid;
                    count = -1;
                    break;
                }
                now_money -= arr[i];

                count++;
            }
        }
        if (count == -1)
        {
            lo = mid;
            continue;
        }
        if (count <= m)
            hi = mid;
        else
            lo = mid;
        // printf("%d %d %d c:%d\n", lo, mid, hi, count);
    }
    printf("%d\n", lo + 1);
}
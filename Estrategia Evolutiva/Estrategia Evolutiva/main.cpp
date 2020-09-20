#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<vector<int> > V;


    for(int i=0;i<10;i++)
    {
        vector<int> V2;

        for(int j=0;j<15;j++)
        {
            V2.push_back(j);
        }

        V.push_back(V2);

    }
    V[2][2]=33;

    for(int i=0;i<V.size();i++)
    {
          for(int j=0;j<15;j++)
            cout<<V[i][j]<<" ";
          cout<<endl;
    }


    return 0;
}

#include <string>
#include <vector>
using namespace std;

int main()
{
	string s1 = "kissa";
    string s2;
    s1 = s2;

    s1 = "kissa";
    s1 = move(s2);

    s1 = "kissa";
    vector<string> v;
    v.push_back(move(s1));
	return 0;
}
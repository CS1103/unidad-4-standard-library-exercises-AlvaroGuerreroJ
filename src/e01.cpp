#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include <prettyprint.hpp>

using std::back_inserter;
using std::cin;
using std::copy;
using std::cout;
using std::endl;
using std::istringstream;
using std::istream_iterator;
using std::make_pair;
using std::pair;
using std::sort;
using std::string;
using std::transform;
using std::vector;

int main()
{
    size_t n_cases;
    cin >> n_cases;

    cin.ignore();

    for (; n_cases > 0; n_cases--)
    {
        string temp;

        getline(cin, temp);
        istringstream indexes_stream(temp);
        vector<size_t> indexes((istream_iterator<size_t>(indexes_stream)), istream_iterator<size_t>());

        getline(cin, temp);
        istringstream values_stream(temp);
        vector<double> values((istream_iterator<double>(values_stream)), istream_iterator<double>());

        vector<pair<size_t, double>> ordered;
        transform(indexes.begin(), indexes.end(), values.begin(),
                  back_inserter(ordered),
                  [](size_t l, double r){
                      return make_pair(l, r);
                  });
        sort(ordered.begin(), ordered.end(),
             [](pair<size_t, double> p0, pair<size_t, double> p1){
                 return p0.first < p1.first;
             });

        vector<double> result;
        transform(ordered.begin(), ordered.end(), back_inserter(result),
                  [](pair<size_t, double> p){
                      return p.second;
                  });

        cout << result << endl;
    }
}

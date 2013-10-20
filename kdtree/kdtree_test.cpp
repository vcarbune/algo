#include <iostream>

#include "kdtree.h"

using namespace std;

bool testKdTreeDuplicates()
{
    vector<pair<double, double> > duplicates;
    for (int n = 0; n < 3; ++n)
        duplicates.push_back(make_pair<double, double>(0, 0));

    KdNode root(0);
    root.setPoints(duplicates);

    return root.getSize() == 1;
}

bool testKdTreeOneAxis()
{
    vector<pair<double, double> > points;
    for (int n = 0; n < 3; ++n)
        points.push_back(make_pair<double, double>(0, n));

    KdNode root(0);
    root.setPoints(points);

    for (size_t i = 0; i < points.size(); ++i)
        if (root.findNearest(points[i]) != points[i])
            return false;

    return true;
}

bool testKdTreeExistingPoints()
{
    KdNode root(0);

    vector<pair<double, double> > places;
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j)
            places.push_back(make_pair<double, double>(i, j));
    root.setPoints(places);

    pair<double, double> pt;
    pair<double, double> sol;
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j) {
            pt = make_pair<double, double>(i, j);
            sol = root.findNearest(pt);
            if (pt != sol)
                return false;
        }

    return true;
}

bool testKdTreeSimpleNearest()
{
    vector<pair<double, double> > places;
    places.push_back(make_pair<double, double>(0, 0));
    places.push_back(make_pair<double, double>(1, 0));
    places.push_back(make_pair<double, double>(2, 0));

    KdNode root(0);
    root.setPoints(places);

    pair<double, double> s1 = root.findNearest(make_pair<double, double>(1.49, 0));
    pair<double, double> s2 = root.findNearest(make_pair<double, double>(1.51, 0));

    pair<double, double> expected1 = make_pair<double, double>(1, 0);
    pair<double, double> expected2 = make_pair<double, double>(2, 0);

    return s1 == expected1 && s2 == expected2;
}

int main() {
    cout << (!testKdTreeDuplicates() ? "FAILED" : "PASSED");
    cout << ": duplicates" << endl;

    cout << (!testKdTreeOneAxis() ? "FAILED" : "PASSED");
    cout << ": one axis" << endl;

    cout << (!testKdTreeExistingPoints() ? "FAILED" : "PASSED");
    cout << ": existing points" << endl;

    cout << (!testKdTreeSimpleNearest() ? "FAILED" : "PASSED");
    cout << ": simple" << endl;

    return 0;
}

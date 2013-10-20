#include "kdtree.h"

#include <algorithm>

using namespace std;

static bool compare_points_by_x(
        const pair<double, double>& a, const pair<double, double>& b) {
    return a.first < b.first;
}

static bool compare_points_by_y(
        const pair<double, double>& a, const pair<double, double>& b) {
    return a.second < b.second;
}

static double getDist(pair<double, double> a, pair<double, double> b) {
    double x_dist = a.first - b.first;
    double y_dist = a.second - b.second;

    return x_dist * x_dist + y_dist * y_dist;
}

static double getAxisDist(pair<double, double> a, pair<double, double> b,
        int depth) {
    double diff = depth % 2 == 0 ? (a.first - b.first) : (a.second - b.second);
    return diff * diff;
}

KdNode::KdNode(int depth)
    : m_depth(depth)
    , m_left(0)
    , m_right(0) {
        m_compare_func = depth % 2 ?
            &compare_points_by_y : &compare_points_by_x;
}

KdNode::~KdNode() {
    if (m_left)
        delete m_left;

    if (m_right)
        delete m_right;
}


void KdNode::setPoints(const vector<pair<double, double> >& points) {
    vector<pair<double, double> > pts = points;

    sort(pts.begin(), pts.end());
    pts.erase(unique(pts.begin(), pts.end()), pts.end());

    setUniquePoints(pts);
}

pair<double, double> KdNode::findNearest(const pair<double, double>& location) {
    if (!m_left && !m_right)
        return m_median;

    if (!m_right)
        return m_left->findNearest(location);
    if (!m_left)
        return m_right->findNearest(location);

    pair<double, double> currentBest;
    double currentDistance;
    double currentAxisDistance;

    KdNode *searchTree = m_compare_func(location, m_median) ? m_left : m_right;
    KdNode *otherTree = searchTree == m_right ? m_left : m_right;

    currentBest = searchTree->findNearest(location);
    currentDistance = getDist(location, currentBest);
    currentAxisDistance = getAxisDist(location, m_median, m_depth);

    if (currentAxisDistance < currentDistance) {
        pair<double, double> other = otherTree->findNearest(location);
        if (getDist(other, location) < currentDistance)
            return other;
    }

    return currentBest;
}

int KdNode::getSize() {
    return 1 + (m_left ? m_left->getSize() : 0) +
        (m_right ? m_right->getSize() : 0);
}

void KdNode::setUniquePoints(vector<pair<double, double> > points) {
    sort(points.begin(), points.end(), m_compare_func);
    m_median = points[points.size() / 2];

    if (points.size() == 1)
        return;

    vector<pair<double, double> > leftPoints;
    vector<pair<double, double> > rightPoints;

    for (size_t i = 0; i < points.size(); ++i)
        if (m_compare_func(points[i], m_median))
            leftPoints.push_back(points[i]);
        else
            rightPoints.push_back(points[i]);

    if (leftPoints.size()) {
        m_left = new KdNode(m_depth + 1);
        m_left->setUniquePoints(leftPoints);
    }

    if (rightPoints.size()) {
        m_right = new KdNode(m_depth + 1);
        m_right->setUniquePoints(rightPoints);
    }
}

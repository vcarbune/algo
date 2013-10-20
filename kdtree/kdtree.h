/**
 * Simple K-d tree implementation for spatial queries.
 */
#ifndef KDTREE_H

#include <utility>
#include <vector>

using namespace std;

typedef bool (*compare_func_t)(
        const std::pair<double, double>&, const std::pair<double, double>&);

class KdNode {
    public:
        KdNode(int);
        ~KdNode();

        void setPoints(const std::vector<std::pair<double, double> >& points);
        std::pair<double, double> findNearest(
                const std::pair<double, double>& location);
        int getSize();

    private:
        void setUniquePoints(std::vector<std::pair<double, double> > points);

        int m_depth;
        std::pair<double, double> m_median;
        compare_func_t m_compare_func;

        KdNode *m_left;
        KdNode *m_right;
};

#endif // KDTREE_H

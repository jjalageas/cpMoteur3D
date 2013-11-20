#ifndef SKELETON_H
#define SKELETON_H

#include "Image.hpp"
#include "Struct.hpp"

#include <string>

class ImageMask2d;


class Node : public Point3D_t<float>
{
public:
    Node();
    Node (float X, float Y, float Z);
    Node(Node* n);
    void setParent(int p);


public:
    bool flagview;
    int parent;
    MiList<int> children;

};


class SkeletonSlice
{
public:
    SkeletonSlice();
    ~SkeletonSlice();


public:
    Image<Point3D_t<int> >* coord;
    ImageMask2d* exam2d;

    Point2D_t<int> lightCenter;
    MiList<Point2D_t<int> > lightIsoContour;
    Triplet_t<float, float, float> lightDiameters; // min , median, max
    MiList<Point2D_t<int> > lightArea;

    Point2D_t<int> wallCenter;
    MiList<Point2D_t<int> > wallIsoContour;
    Triplet_t<float, float, float> wallDiameters; // min , median, max
    MiList<Point2D_t<int> > wallArea;

    Point2D_t<float> resolution;

};


class Branch
{
public:
    Branch();
    ~Branch();


public:
    std::string name;
    bool flagview;
    int generation;
    int parent;
    float length;
    int correlation;
    Angle angle;

    MiList<int> children;
    MiList<int> nodes;
    MiList<SkeletonSlice*> slices;

};


class Skeleton
{
public:
    Skeleton(){;}
    ~Skeleton();

    void empty();
    void emptyNodes();
    void emptyBranches();

    int getNodesSize();
    void addNode(Node*);
    Node* getNode(int n);
    MiList<Node*> getLstNode();
    MiList<Node*>& getLstNodeRef();

    int getBranchesSize();
    void addBranch(Branch*);
    Branch* getBranch(int n);
    MiList<Branch*> getLstBranch();
    MiList<Branch*>& getLstBranchRef();

    MiList<int> getLeaf();
    float getLenghtFromLeafToRoot(int i);
    float getLenghtFromLeafToJustAfterRoot(int i);
    int getNbGeneration();
    MiList<int> getBranchsByGeneration(int i);

    int searchCorrelation(unsigned int);


private:
    MiList<Node*> _nodes;
    MiList<Branch*> _branches;

};

#endif /* SKELETON_H */

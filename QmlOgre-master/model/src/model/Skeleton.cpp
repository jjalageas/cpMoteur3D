#include <Skeleton.h>
#include <ImageMask2d.h>


//------------------------------
// Node
//------------------------------
Node::Node() { flagview = true; }

Node::Node (float X, float Y, float Z)
    : Point3D_t<float>(X, Y, Z),
      flagview(true), parent(-1)
{}

Node::Node(Node* n)
    : Point3D_t<float>(n->x, n->y, n->z),
      flagview(n->flagview), parent(n->parent)
{
    for (int i=0; i < n->children.size(); ++i) {
        children.add(n->children.get(i));
    }
}

void Node::setParent(int p) { parent = p; }


//------------------------------
// SkeletonSlice
//------------------------------
SkeletonSlice::SkeletonSlice()
    : coord(NULL), exam2d(NULL)
{
    resolution = Point2D_t<float>(1, 1);
}

SkeletonSlice::~SkeletonSlice()
{
    delete coord;
    coord = NULL;
    delete exam2d;
    exam2d = NULL;
    lightIsoContour.empty();
    lightArea.empty();
    wallIsoContour.empty();
    wallArea.empty();
}


//------------------------------
// Branch
//------------------------------
Branch::Branch()
    : name(""), flagview(true), generation(-1),
      parent(-1), correlation(-1)

{
    angle = Angle();
}

Branch::~Branch()
{
    for (int i=0; i<slices.size(); ++i) {
        delete slices.get(i);
    }
    children.empty();
    nodes.empty();
}


//------------------------------
// Skeleton
//------------------------------
Skeleton::~Skeleton() { empty(); }

void
Skeleton::empty()
{
   emptyNodes();
   emptyBranches();
}

void
Skeleton::emptyNodes()
{
   for (int i=0; i<_nodes.size(); ++i) {
        delete _nodes.get(i);
   }
   _nodes.empty();
}

void
Skeleton::emptyBranches()
{
   for (int i=0; i<_branches.size(); ++i) {
        delete _branches.get(i);
   }
   _branches.empty();
}

int Skeleton::getNodesSize() { return _nodes.size(); }
void Skeleton::addNode(Node* node) { _nodes.add(node); }
Node* Skeleton::getNode(int n) { return _nodes.get(n); }
MiList<Node*> Skeleton::getLstNode() { return _nodes; }
MiList<Node*>& Skeleton::getLstNodeRef() { return _nodes; }

int Skeleton::getBranchesSize() { return _branches.size(); }
void Skeleton::addBranch(Branch* branch) { _branches.add(branch); }
Branch* Skeleton::getBranch(int n) { return _branches.get(n); }
MiList<Branch*> Skeleton::getLstBranch() { return _branches; }
MiList<Branch*>& Skeleton::getLstBranchRef() { return _branches; }

MiList<int>
Skeleton::getLeaf()
{
   int nbBranch = this->getBranchesSize();
   MiList<int>res;
   for (int i=0; i<nbBranch; ++i) {
        Branch* b = this->getBranch(i);
        if (b->children.size() == 0) {
            res.add(i);
        }
   }
   return res;
}

float
Skeleton::getLenghtFromLeafToRoot(int i)
{
   Branch* current = this->getBranch(i);
   float lenght = current->length;
   while (current->parent != -1) {
        current = this->getBranch(current->parent);
        lenght += current->length;
   }
   return lenght;
}

float
Skeleton::getLenghtFromLeafToJustAfterRoot(int i)
{
   Branch* current = this->getBranch(i);
   float lenght = current->length;
   while (current->parent != 0) {
        current = this->getBranch(current->parent);
        lenght += current->length;
   }
   return lenght;
}

int
Skeleton::getNbGeneration()
{
   MiList<int> LstLeaf = Skeleton::getLeaf();
   int nbLeaf = LstLeaf.size();
   int nbgenerationMax = 0;
   for (int i=0; i<nbLeaf; ++i) {
        int nbParents = 0;
        Branch* current = this->getBranch(LstLeaf.get(i));
        while (current->parent != -1) {
            nbParents++;
            current = this->getBranch(current->parent);
        }
        if (nbParents > nbgenerationMax) {
            nbgenerationMax = nbParents;
        }
   }
   return nbgenerationMax;
}

MiList<int>
Skeleton::getBranchsByGeneration(int generation)
{
   int nbBranch = this->getBranchesSize();
   MiList<int>res;
   for (int i=0; i<nbBranch; ++i) {
        int gen = this->getBranch(i)->generation;
        if (gen == generation) {
            res.add(i);
        }
   }
   return res;
}

int
Skeleton::searchCorrelation(unsigned int corr)
{
   int size = _branches.size();
   for (int i=0; i<size; ++i) {
        if ((unsigned) _branches.get(i)->correlation == corr) {
            return i;
        }
   }
   return -1;
}

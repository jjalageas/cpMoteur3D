#ifndef STRUCT_HPP
#define STRUCT_HPP

#include <iostream>
#include <string>
#include <vector>


/**
  * @class MiList<T>
  * @brief Surcouche du type vector
  *
  * Cette classe encapsule le type VECTOR de c++
  */
template <typename T> class MiList
{
public:
    ~MiList() { empty(); }

    void add(T new_element) { _list.push_back(new_element); }
    void erase(int i) { _list.erase(_list.begin()+i); }
    int size() { return (int)_list.size(); }

    T get(int i) { return _list.at(i); }
    T& getRef(int i) { return _list.at(i); }
    T getFirst() { return _list.at(0); }
    T getLast() { return _list.at(_list.size() - 1); }

    void removeFirst() { _list.erase(_list.begin()); }
    void removeLast() { _list.erase(_list.begin() + _list.size()-1); }
    void removeAt(int index) { erase(index); }
    void removeOne(T element)
    {
        int n = search(element);
        if (n >= 0) {
            erase(n);
        }
    }

    bool isExist(T element)
    {
        for (unsigned int i=0; i<_list.size(); ++i) {
            if (_list.at(i) == element) {
                return true;
            }
        }
        return false;
    }
    int search(T element)
    {
        for (unsigned int i=0; i<_list.size(); ++i) {
            if (_list.at(i) == element) return i; {
                return -1;
            }
        }
    }
    void empty()
    {
        while (!_list.empty()) {
            _list.pop_back();
        }
    }
    void append(MiList<T> list)
    {
        int size = list.size();
        for (int i=0; i<size; ++i) {
            _list.push_back(list.get(i));
        }
    }
    void eraseDuplicates()
    {
        T element;
        for (int i=0; i<_list.size(); ++i) {
            element = _list.at(i);
            for (int j=i+1; j<_list.size(); ++j) {
                if (_list.at(j) == element) {
                    _list.erase(j);
                    j--;
                }
            }
        }
    }
    void deletePointersList()
    {
        for (int i=0; i<_list.size(); ++i) {
            delete _list.at(i);
        }
        _list.empty();
    }
    void insert(int index, T element)
    {
        _list.insert(_list.begin()+index, element);
    }


private:
    std::vector<T> _list;

};


class MiTimer
{
public:
    void start() { clockStart = clock(); }
    void stop(std::string desc = "MiTimer result : ")
    {
        clockEnd = clock();
        double inter = (double) (clockEnd - clockStart) / CLOCKS_PER_SEC;
        std::cout << desc << inter << " sec" << std::endl;
    }


private:
    clock_t clockStart, clockEnd;

};


class DicomDir
{
public:
    DicomDir()
        : nbSlice(0)
    {}


public:
    std::string dirName;
    std::string path;

    MiList<DicomDir*> subdir;

    std::string patientName;
    std::string patientSex;
    std::string studyDate;
    int nbSlice;

};


class Color
{
public:
    Color()
        : red((char)255), green((char)255), blue((char)255),
          alpha((char)255)
    {}
    Color (int r, int g, int b)
        : red((char)r), green((char)g), blue((char)b),
          alpha((char)255)
    {}
    Color (int r, int g, int b, int a)
        : red((char)r), green((char)g), blue((char)b),
          alpha((char)a)
    {}

    int Red() { return ((int)red); }
    int Green() { return (int)green; }
    int Blue() { return (int)blue; }
    int Alpha() {return (int)alpha; }

    void Red(int r) { red = (char)r;}
    void Green(int g) { green = (char)g; }
    void Blue(int b) { blue = (char)b; }
    void Alpha(int a) {alpha = (char)a; }


public:
    char red, green, blue, alpha;

};


template <typename T>
class Point2D_t
{
public:
    Point2D_t() : x(0), y(0) {}
    Point2D_t(T X, T Y) : x(X), y(Y) {}

    bool operator== (const Point2D_t& n)
    {
        return (x == n.x && y == n.y);
    }


public:
    T x, y;

};


template<typename T, typename D>
class Point2D_Data_t
        : public Point2D_t<T>
{
public:
    Point2D_Data_t() : Point2D_t<T>(), data((D)0) {}
    Point2D_Data_t(D d) : Point2D_t<T>(), data(d) {}
    Point2D_Data_t(T X, T Y) : Point2D_t<T>(X, Y), data((D)0) {}
    Point2D_Data_t(T X, T Y, D d) : Point2D_t<T>(X, Y), data(d) {}


public:
    D data;

};


template <typename T>
class Point3D_t
        : public Point2D_t<T>
{
public:
    Point3D_t() : Point2D_t<T>(), z((T)0) {}
    Point3D_t(T X, T Y, T Z) : Point2D_t<T>(X, Y), z(Z) {}

    bool operator== (const Point3D_t& n)
    {
        return (z == n.z) && (Point2D_t<T>::operator == (n));
    }


public:
    T z;

};


template<typename T, typename D>
class Point3D_Data_t
        : public Point3D_t<T>
{
public:
    Point3D_Data_t() : Point3D_t<T>(), data((D)0) {}
    Point3D_Data_t(D d) : Point3D_t<T>(), data(d) {}
    Point3D_Data_t(T X, T Y, T Z) : Point3D_t<T>(X, Y, Z), data((D)0) {}
    Point3D_Data_t(T X, T Y, T Z, D d) : Point3D_t<T>(X, Y, Z), data(d) {}


public:
    D data;

};


template<typename T>
class Point3D_Color_t
        : public Point3D_t<T>, public Color
{
public:
    Point3D_Color_t() : Point3D_t<T>(), Color() {}
    Point3D_Color_t(T X, T Y, T Z) : Point3D_t<T>(X, Y, Z), Color() {}
    Point3D_Color_t(T X, T Y, T Z, int r, int g, int b)
        : Point3D_t<T>(X, Y, Z), Color(r, g, b) {}

};


class Angle
{
public:
    Angle() : rho(0.), theta(0.) {}
    Angle (double r, double t) : rho(r), theta(t) {}


public:
    double rho, theta;

};


class Segment
{
public:
    Segment (Point3D_t<float> s, Point3D_t<float> t) : src(s), trg(t) {}
    Segment (Point3D_t<float> s, Point3D_t<float> t, Color c) : src(s), trg(t), color(c) {}


public:
    Point3D_t<float> src, trg;
    Color color;

};


template<typename A, typename B>
class Pair_t
{
public:
    Pair_t(A a, B b) : first(a), second(b) {}


public:
    A first;
    B second;

};


template<typename A, typename B,typename C>
class Triplet_t
{
public:
    Triplet_t() {}
    Triplet_t(A a, B b,C c) : first(a), second(b), third(c) {}


public:
    A first;
    B second;
    C third;

};


class Triangle_t
        : public Triplet_t<Point3D_t<float>, Point3D_t<float>, Point3D_t<float> >
{
public:
    Point3D_t<float> normal;

};


#endif // STRUCT_HPP

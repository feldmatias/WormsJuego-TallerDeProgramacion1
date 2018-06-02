
#ifndef WORMS_OBJECTMODEL_H
#define WORMS_OBJECTMODEL_H


class MapObject {
    double x, y;
    int angle;
public:
    MapObject(const double &x, const double &y, const int &angle = 0);

    void updatePosition(const double& x, const double& y);

    int turnCCW();

    void getPosition(double &x, double &y) const;

    const int getAngle() const;

    int turnCW();
};


#endif //WORMS_OBJECTMODEL_H
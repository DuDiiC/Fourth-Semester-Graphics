#include "includes/MyWidget.h"

#include <includes/MilkyWay.h>
#include <includes/Vector3D.h>
#include <QtCore/QTime>
#include <QtCore/QEventLoop>
#include <QCoreApplication>

const std::string SUN_TEXTURE = "/home/maciejdudek/Pulpit/Fourth-Semester-Graphics/08.Solar-System-PROJECT/resources/sun.jpg";
const std::string MERCURY_TEXTURE = "/home/maciejdudek/Pulpit/Fourth-Semester-Graphics/08.Solar-System-PROJECT/resources/mercury.jpg";
const std::string VENUS_TEXTURE = "/home/maciejdudek/Pulpit/Fourth-Semester-Graphics/08.Solar-System-PROJECT/resources/venus.jpg";
const std::string EARTH_TEXTURE = "/home/maciejdudek/Pulpit/Fourth-Semester-Graphics/08.Solar-System-PROJECT/resources/earth.jpg";
const std::string MARS_TEXTURE = "/home/maciejdudek/Pulpit/Fourth-Semester-Graphics/08.Solar-System-PROJECT/resources/mars.png";
const std::string JUPITER_TEXTURE = "/home/maciejdudek/Pulpit/Fourth-Semester-Graphics/08.Solar-System-PROJECT/resources/jupiter.jpg";
const std::string SATURN_TEXTURE = "/home/maciejdudek/Pulpit/Fourth-Semester-Graphics/08.Solar-System-PROJECT/resources/saturn.jpg";
const std::string URANUS_TEXTURE = "/home/maciejdudek/Pulpit/Fourth-Semester-Graphics/08.Solar-System-PROJECT/resources/uranus.jpg";
const std::string NEPTUNE_TEXTURE = "/home/maciejdudek/Pulpit/Fourth-Semester-Graphics/08.Solar-System-PROJECT/resources/neptune.jpg";

MyWidget::MyWidget(int width, int height) {

    img = new QImage(width, height, QImage::Format_RGB32);
    imgConst = new QImage(width, height, QImage::Format_RGB32);

    MilkyWay::draw(img, 1000);

    *imgConst = *img;

    transformationMatrix = new TransformationMatrix4x4(0, 0, 0,
                                                        0, 0, 0,
                                                        1.0, 1.0, 1.0,
                                                        0.0, 0.0, 0.0, img);
    transformationMatrix->updateMatrix();

    setMatrices();
    setPlanets();
    setConstPlanets();

    planets[0]->draw(img);
    for(int i = 1; i < planets.size(); i++) {
        planets[i]->draw(img, observer);
        *planets[i] = *constPlanets[i];
    }

    repaint();
    //updateImg();
}

MyWidget::~MyWidget() {
    delete img;
    delete imgConst;
    delete transformationMatrix;
    for(auto & planet : planets) { delete planet; }

    img = nullptr;
    imgConst = nullptr;
    transformationMatrix = nullptr;
    for(auto & planet : planets) { planet = nullptr; }
}

void MyWidget::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.drawImage(0, 0, *img);
}

void MyWidget::updateImg() {

    std::vector < std::pair < int, int > > planetsZ;
    for(int i = 0; i < planets.size(); i++) {
        planetsZ.emplace_back(i, planets[i]->getZ0());
    }
    std::sort(planetsZ.begin(), planetsZ.end(), sortingPlanets);

    *img = *imgConst;
//    planets[0]->draw(img);
//    *planets[0] = *constPlanets[0];
//    for(int i = 1; i < planets.size(); i++) {
//        planets[i]->draw(img, observer);
//        std::cout << planets[i]->getZ0() << std::endl;
//        *planets[i] = *constPlanets[i];
//    }
    for(int i = 0; i < planetsZ.size(); i++) {
        if(planetsZ[i].first == 0) {
            planets[planetsZ[i].first]->draw(img);
        } else {
            planets[planetsZ[i].first]->draw(img, observer);
        }
        *planets[planetsZ[i].first] = *constPlanets[planetsZ[i].first];
    }
    repaint();
}

//bool MyWidget::sortingPlanets(const std::pair < int, int > &a, const std::pair < int, int > &b) {
//    return (a.second < b.second);
//}

void MyWidget::setPlanets() {

    planets.push_back(new Sphere(80, 25, 25, -1000, QImage(SUN_TEXTURE.c_str())));
    planets.push_back(new Sphere(10, 15, 15, -1000, QImage(MERCURY_TEXTURE.c_str()), 90, 12));
    planets.push_back(new Sphere(13, 15, 15, -1000, QImage(VENUS_TEXTURE.c_str()), 120, 15));
    planets.push_back(new Sphere(25, 25, 25, -1000, QImage(EARTH_TEXTURE.c_str()), 175, -12));
    planets.push_back(new Sphere(22, 15, 15, -1000, QImage(MARS_TEXTURE.c_str()), 240, 13));
    planets.push_back(new Sphere(45, 20, 20, -1000, QImage(JUPITER_TEXTURE.c_str()), 320, -14));
    planets.push_back(new Sphere(42, 20, 20, -1000, QImage(SATURN_TEXTURE.c_str()), 440, 11));
    planets.push_back(new Sphere(33, 15, 15, -1000, QImage(URANUS_TEXTURE.c_str()), 535, -12));
    planets.push_back(new Sphere(30, 15, 15, -1000, QImage(NEPTUNE_TEXTURE.c_str()), 630, 15));

    updatePlanets(planets);
}

void MyWidget::setConstPlanets() {
    constPlanets.push_back(new Sphere(80, 25, 25, -1000, QImage(SUN_TEXTURE.c_str())));
    constPlanets.push_back(new Sphere(10, 15, 15, -1000, QImage(MERCURY_TEXTURE.c_str()), 90, 12));
    constPlanets.push_back(new Sphere(13, 15, 15, -1000, QImage(VENUS_TEXTURE.c_str()), 120, 15));
    constPlanets.push_back(new Sphere(25, 25, 25, -1000, QImage(EARTH_TEXTURE.c_str()), 175, -12));
    constPlanets.push_back(new Sphere(22, 15, 15, -1000, QImage(MARS_TEXTURE.c_str()), 240, 13));
    constPlanets.push_back(new Sphere(45, 20, 20, -1000, QImage(JUPITER_TEXTURE.c_str()), 320, -14));
    constPlanets.push_back(new Sphere(42, 20, 20, -1000, QImage(SATURN_TEXTURE.c_str()), 440, 11));
    constPlanets.push_back(new Sphere(33, 15, 15, -1000, QImage(URANUS_TEXTURE.c_str()), 535, -12));
    constPlanets.push_back(new Sphere(30, 15, 15, -1000, QImage(NEPTUNE_TEXTURE.c_str()), 630, 15));

    updatePlanets(constPlanets);
}

void MyWidget::updatePlanets(std::vector < Sphere* > planetsTemp) {
    planetsTemp[0]->updateValues(sunMatrix);
    for(int i = 1; i < planetsTemp.size(); i++) {
        planetsTemp[i]->updateValues(planetsMatrices[i - 1]);
    }
}

void MyWidget::setMatrices() {
    sunMatrix = new SunTransformationMatrix(M_PI/2, M_PI/4, 0.0);

    planetsMatrices.push_back(new PlanetTransformationMatrix(90, 12, 0, M_PI/2, 0.0, 0.0, 0.0));
    planetsMatrices.push_back(new PlanetTransformationMatrix(120, 15, 0, M_PI/2, 0.0, 0.0, 0.0));
    planetsMatrices.push_back(new PlanetTransformationMatrix(175, -12, 0, M_PI/2, 0.0, 0.0, 0.0));
    planetsMatrices.push_back(new PlanetTransformationMatrix(240, 13, 0, M_PI/2, 0.0, 0.0, 0.0));
    planetsMatrices.push_back(new PlanetTransformationMatrix(320, -14, 0, M_PI/2, 0.0, 0.0, 0.0));
    planetsMatrices.push_back(new PlanetTransformationMatrix(440, 11, 0, M_PI/2, 0.0, 0.0, 0.0));
    planetsMatrices.push_back(new PlanetTransformationMatrix(535, -12, 0, M_PI/2, 0.0, 0.0, 0.0));
    planetsMatrices.push_back(new PlanetTransformationMatrix(630, 15, 0, M_PI/2, 0.0, 0.0, 0.0));

    updateMatrices();
}

void MyWidget::updateMatrices() {
    sunMatrix->updateMatrix();
    for(auto & planetMatrix : planetsMatrices) {
        planetMatrix->updateMatrix();
    }
}

void MyWidget::animation() {

    long long val = 0;

    double EARTH_INTERVAL = 2.0;
    double alphaSun = 0.0;
    double alphaMercury = 0.0;
    double alphaVenus = 0.0;
    double alphaEarth = 0.0;
    double alphaMars = 0.0;
    double alphaJupiter = 0.0;
    double alphaSaturn = 0.0;
    double alphaUranus = 0.0;
    double alphaNeptune = 0.0;

    while(val < 10000000L) {
        QTime pause = QTime::currentTime().addMSecs(1);
        while(QTime::currentTime() < pause) {
            QCoreApplication::processEvents(QEventLoop::AllEvents, 1);
        }
        val++;
        alphaSun += 0.5;
        alphaMercury += (EARTH_INTERVAL * 4.16);
        alphaVenus += (EARTH_INTERVAL * 1.623);
        alphaEarth += (EARTH_INTERVAL);
        alphaMars += (EARTH_INTERVAL * 0.531);
        alphaJupiter += (EARTH_INTERVAL * 0.183);
        alphaSaturn += (EARTH_INTERVAL * 0.084);
        alphaUranus += (EARTH_INTERVAL * 3.062);
        alphaNeptune += (EARTH_INTERVAL * 0.044);
        setSunRotationZ(alphaSun);
        setMercuryRotation(alphaMercury);
        setVenusRotation(alphaVenus);
        setEarthRotation(alphaEarth);
        setMarsRotation(alphaMars);
        setJupiterRotation(alphaJupiter);
        setSaturnRotation(alphaSaturn);
        setUranusRotation(alphaUranus);
        setNeptuneRotation(alphaNeptune);
        updateImg();
    }
}

void MyWidget::setSunRotationX(int value) {
    sunMatrix->setAlphaXFromDegrees(value);
    planets[0]->updateValues(sunMatrix);
//    constPlanets[0]->updateValues(sunMatrix);
//    updateImg();
}

void MyWidget::setSunRotationY(int value) {
    sunMatrix->setAlphaYFromDegrees(value);
    planets[0]->updateValues(sunMatrix);
//    constPlanets[0]->updateValues(sunMatrix);
//    updateImg();
}

void MyWidget::setSunRotationZ(int value) {
    sunMatrix->setAlphaZFromDegrees(value);
    planets[0]->updateValues(sunMatrix);
//    constPlanets[0]->updateValues(sunMatrix);
//    updateImg();
}

void MyWidget::setMercuryRotation(int value) {
    planetsMatrices[0]->setAlphaOFromDegrees(value);
    planets[1]->updateValues(planetsMatrices[0]);
//    constPlanets[1]->updateValues(planetsMatrices[0]);
//    updateImg();
}

void MyWidget::setVenusRotation(int value) {
    planetsMatrices[1]->setAlphaOFromDegrees(value);
    planets[2]->updateValues(planetsMatrices[1]);
//    updateImg();
}

void MyWidget::setEarthRotation(int value) {
    planetsMatrices[2]->setAlphaOFromDegrees(value);
    planets[3]->updateValues(planetsMatrices[2]);
//    updateImg();
}

void MyWidget::setMarsRotation(int value) {
    planetsMatrices[3]->setAlphaOFromDegrees(value);
    planets[4]->updateValues(planetsMatrices[3]);
//    updateImg();
}

void MyWidget::setJupiterRotation(int value) {
    planetsMatrices[4]->setAlphaOFromDegrees(value);
    planets[5]->updateValues(planetsMatrices[4]);
//    updateImg();
}

void MyWidget::setSaturnRotation(int value) {
    planetsMatrices[5]->setAlphaOFromDegrees(value);
    planets[6]->updateValues(planetsMatrices[5]);
//    updateImg();
}

void MyWidget::setUranusRotation(int value) {
    planetsMatrices[6]->setAlphaOFromDegrees(value);
    planets[7]->updateValues(planetsMatrices[6]);
//    updateImg();
}

void MyWidget::setNeptuneRotation(int value) {
    planetsMatrices[7]->setAlphaOFromDegrees(value);
    planets[8]->updateValues(planetsMatrices[7]);
//    updateImg();
}


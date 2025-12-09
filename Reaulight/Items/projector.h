#ifndef PROJECTOR_H
#define PROJECTOR_H

#include <QObject>
#include <QVector3D>
#include <QJsonDocument>
#include "channel.h"

class Projector : public QObject
{
    Q_OBJECT
    public:
        explicit Projector(QObject *parent = nullptr);
        Projector(QString fileName, QObject *parent = nullptr);
        Projector(QJsonDocument document, QObject *parent = nullptr);

        void load(QJsonDocument document);
        void load(QString filename);
        void load();

        void save(QString filename = "");
        QJsonDocument getJSON();


        //Accesseurs
        QString getModel();
        QString getBrand();
        QString getLightSourceType();
        QString getPowerConsumption();
        QString getVoltage();
        QString getFuse();
        QString getIPClass();
        double getWeight();
        double getLightAngle();
        double getLightIntensity();
        double getLightIntensityDistance();
        QVector3D getDimensions();
        QStringList getConnectors();
        QString getConnector(int connectorId);
        QList<int> getChannelModes();
        int getChannelMode(int id);
        QList<Channel*> getChannels(int id);

        void setModel(QString model);
        void setBrand(QString brand);
        void setLightSourceType(QString lightSourceType);
        void setPowerConsumption(QString powerConsumption);
        void setVoltage(QString voltage);
        void setFuse(QString fuse);
        void setIPClass(QString IPClass);
        void setWeight(double weight);
        void setLightAngle(double lightAngle);
        void setIntensity(double lightIntensity);
        void setLightIntensityDistance(double lightIntensityDistance);
        void setDimensions(QVector3D dimensions);
        void setDimensions(int x, int y, int z);
        void setConnectors(QStringList connectors);
        void addConnector(QString connector);
        void removeConnector(QString connector);
        void removeConnector(int connectorId);
        void addChannelMode(int channelsCount, QList<Channel*> channels);
        void removeChannelMode(int channelId);

    signals:

    public slots:

    private:
        //Informations générales
        QString model;
        QString brand;
        QString lightSourceType;
        QString powerConsumption;
        QString voltage;
        QString fuse;
        QString IPClass;
        double  weight;
        double  lightAngle;
        double  lightIntensity;
        double  lightIntensityDistance;
        QVector3D dimensions;
        QStringList connectors;
        QList<int> channelModes;
        QList< QList<Channel*> > channels;//TODO Channels Config

        QString filename;
};

#endif // PROJECTOR_H

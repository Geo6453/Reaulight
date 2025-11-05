#include "projector.h"

Projector::Projector(QObject *parent)
    : QObject{parent}
{

}

QString Projector::getModel()
{
    return this->model;
}

QString Projector::getBrand()
{
    return this->brand;
}

QString Projector::getLightSourceType()
{
    return this->lightSourceType;
}

QString Projector::getPowerConsumption()
{
    return this->powerConsumption;
}

QString Projector::getVoltage()
{
    return this->voltage;
}

QString Projector::getFuse()
{
    return this->fuse;
}

QString Projector::getIPClass()
{
    return this->IPClass;
}

double Projector::getWeight()
{
    return this->weight;
}

double Projector::getLightAngle()
{
    return this->lightAngle;
}

double Projector::getLightIntensity()
{
    return this->lightIntensity;
}

double Projector::getLightIntensityDistance()
{
    return this->lightIntensityDistance;
}

QVector3D Projector::getDimensions()
{
    return this->dimensions;
}

QStringList Projector::getConnectors()
{
    return this->connectors;
}

QString Projector::getConnector(int connectorId)
{
    if(connectorId < this->connectors.length())
    {
        return this->connectors.at(connectorId);
    }
    else
    {
        return QString();
    }
}

QList<int> Projector::getChannelModes()
{
    return this->channelModes;
}

int Projector::getChannelMode(int id)
{
    if(id < this->channelModes.length())
    {
        return this->channelModes.at(id);
    }
    else
    {
        return -1;
    }
}


QList<Channel> Projector::getChannels(int id)
{
    if(id < this->channels.length())
    {
        return this->channels.at(id);
    }
    else
    {
        return QList<Channel>();
    }
}




void Projector::setModel(QString model)
{
    this->model = model;
}

void Projector::setBrand(QString brand)
{
    this->brand = brand;
}

void Projector::setLightSourceType(QString lightSourceType)
{
    this->lightSourceType = lightSourceType;
}

void Projector::setPowerConsumption(QString powerConsumption)
{
    this->powerConsumption = powerConsumption;
}

void Projector::setVoltage(QString voltage)
{
    this->voltage = voltage;
}

void Projector::setFuse(QString fuse)
{
    this->fuse = fuse;
}

void Projector::setIPClass(QString IPClass)
{
    this->IPClass = IPClass;
}

void Projector::setWeight(double weight)
{
    this->weight = weight;
}

void Projector::setLightAngle(double lightAngle)
{
    this->lightAngle = lightAngle;
}

void Projector::setIntensity(double lightIntensity)
{
    this->lightIntensity = lightIntensity;
}

void Projector::setLightIntensityDistance(double lightIntensityDistance)
{
    this->lightIntensityDistance = lightIntensityDistance;
}

void Projector::setDimensions(QVector3D dimensions)
{
    this->dimensions = dimensions;
}

void Projector::setDimensions(int x, int y, int z)
{
    if(x < 0 || y < 0 || z < 0)
    {
        this->dimensions = QVector3D(0,0,0);
    }
    else
    {
        this->dimensions = QVector3D(x, y, z);
    }
}

void Projector::setConnectors(QStringList connectors)
{
    this->connectors = connectors;
}

void Projector::addConnector(QString connector)
{
    if(connector != QString())
    {
        this->connectors.append(connector);
    }
}

void Projector::removeConnector(QString connector)
{
    int index = this->connectors.indexOf(connector);
    this->connectors.removeAt(index);
}

void Projector::removeConnector(int connectorId)
{
    if(connectorId < this->connectors.length())
    {
        this->connectors.removeAt(connectorId);
    }
}

void Projector::addChannelMode(int channelsCount, QList<Channel> channels)
{
    if(channelsCount > 0 && channels.length() > 0)
    {
        this->channelModes.append(channelsCount);
        this->channels.append(channels);
    }
}

void Projector::removeChannelMode(int channelId)
{
    if(channelId < channels.length())
    {
        this->channels.removeAt(channelId);
        this->channelModes.removeAt(channelId);
    }
}

#include "projector.h"

#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include "Items/channel.h"

Projector::Projector(QObject *parent)
    : QObject{parent}
{
    this->filename = "";
    this->model = "";
    this->brand = "";
    this->lightSourceType = "";
    this->powerConsumption = "";
    this->voltage = "";
    this->fuse = "";
    this->IPClass = "";
    this->weight = -1;
    this->lightAngle = -1;
    this->lightIntensity = -1;
    this->lightIntensityDistance = -1;
    this->dimensions = QVector3D();
    this->connectors = QStringList();
    this->channelModes = QList<int>();
    this->channels = QList< QList<Channel*> >();
}

Projector::Projector(QString fileName, QObject *parent)
    : QObject{parent}
{
    this->filename = fileName;
    this->model = "";
    this->brand = "";
    this->lightSourceType = "";
    this->powerConsumption = "";
    this->voltage = "";
    this->fuse = "";
    this->IPClass = "";
    this->weight = -1;
    this->lightAngle = -1;
    this->lightIntensity = -1;
    this->lightIntensityDistance = -1;
    this->dimensions = QVector3D();
    this->connectors = QStringList();
    this->channelModes = QList<int>();
    this->channels = QList< QList<Channel*> >();
    this->load();
}


Projector::Projector(QJsonDocument document, QObject *parent)
    : QObject{parent}
{
    this->filename = "";
    this->model = "";
    this->brand = "";
    this->lightSourceType = "";
    this->powerConsumption = "";
    this->voltage = "";
    this->fuse = "";
    this->IPClass = "";
    this->weight = -1;
    this->lightAngle = -1;
    this->lightIntensity = -1;
    this->lightIntensityDistance = -1;
    this->dimensions = QVector3D();
    this->connectors = QStringList();
    this->channelModes = QList<int>();
    this->channels = QList< QList<Channel*> >();
    this->load(document);
}

void Projector::load(QJsonDocument document)
{
    if(document.isObject() && document.object().contains("type") && document.object().value("type") == "projector") //Ai-je bien un projecteur
    {
        QJsonObject obj = document.object(); // La structure

        if(obj.contains("model") && obj.value("model").isString())
            this->model = obj.value("model").toString();
        else
            this->model = "";

        if(obj.contains("brand") && obj.value("brand").isString())
            this->brand = obj.value("brand").toString();
        else
            this->brand = "";

        if(obj.contains("lightSourceType") && obj.value("lightSourceType").isString())
            this->lightSourceType = obj.value("lightSourceType").toString();
        else
            this->lightSourceType = "";

        if(obj.contains("powerConsumption") && obj.value("powerConsumption").isString())
            this->powerConsumption = obj.value("powerConsumption").toString();
        else
            this->powerConsumption = "";

        if(obj.contains("voltage") && obj.value("voltage").isString())
            this->voltage = obj.value("voltage").toString();
        else
            this->voltage = "";

        if(obj.contains("fuse") && obj.value("fuse").isString())
            this->fuse = obj.value("fuse").toString();
        else
            this->fuse = "";

        if(obj.contains("IPClass") && obj.value("IPClass").isString())
            this->IPClass = obj.value("IPClass").toString();
        else
            this->IPClass = "";

        if(obj.contains("weight") && obj.value("weight").isDouble())
            this->weight = obj.value("weight").toDouble(-1);
        else
            this->weight = -1;

        if(obj.contains("lightAngle") && obj.value("lightAngle").isDouble())
            this->lightAngle = obj.value("lightAngle").toDouble(-1);
        else
            this->lightAngle = -1;

        if(obj.contains("lightIntensity") && obj.value("lightIntensity").isDouble())
            this->lightIntensity = obj.value("lightIntensity").toDouble(-1);
        else
            this->lightIntensity = -1;

        if(obj.contains("lightIntensityDistance") && obj.value("lightIntensityDistance").isDouble())
            this->lightIntensityDistance = obj.value("lightIntensityDistance").toDouble(-1);
        else
            this->lightIntensityDistance = -1;

        if(obj.contains("dimensions") && obj.value("dimensions").isObject())
        {
            QJsonObject dim = obj.value("dimensions").toObject();
            if(dim.contains("x") && dim.value("x").isDouble() &&
               dim.contains("y") && dim.value("y").isDouble() &&
               dim.contains("z") && dim.value("z").isDouble())
            {
                this->dimensions = QVector3D(dim.value("x").toDouble(-1),dim.value("y").toDouble(-1),dim.value("z").toDouble(-1));
            }
            else
            {
                this->dimensions = QVector3D();
            }
        }

        if(obj.contains("connectors") && obj.value("connectors").isArray())
        {
            QJsonArray con = obj.value("connectors").toArray();
            this->connectors.clear();
            for(int i = 0; i < con.size(); i++)
            {
                if(con.at(i).isString())
                    this->connectors.append(con.at(i).toString());
            }
        }

        if(obj.contains("channelModes") && obj.value("channelModes").isArray())
        {
            QJsonArray chan = obj.value("channelModes").toArray();
            this->channelModes.clear();
            for(int i = 0; i < chan.size(); i++)
            {
                if(chan.at(i).isDouble())
                    this->channelModes.append(chan.at(i).toDouble(-1));
            }
        }

        if(obj.contains("channels") && obj.value("channels").isArray())
        {
            QJsonArray chans = obj.value("channels").toArray();
            this->channels.clear();
            for(int i = 0; i < chans.size(); i++)
            {
                if(chans.at(i).isArray())
                {
                    QJsonArray chan = chans.at(i).toArray();
                    this->channels.append(QList<Channel*>());
                    for(int j = 0; j < chan.size(); j++)
                    {
                        if(chan.at(j).isObject())
                            this->channels.last().append(new Channel(chan.at(j).toObject()));
                    }
                }
            }
        }
    }
}

void Projector::load(QString filename)
{
    this->filename = filename;
    this->load();
}

void Projector::load()
{
    QFile data(this->filename);
    data.open(QIODevice::ReadWrite);
    QJsonParseError err;
    QJsonDocument json = QJsonDocument::fromJson(QString::fromUtf8(data.readAll()).toUtf8(),&err);
    qDebug() << err.errorString();

    this->load(json);
    data.close();
}

void Projector::save(QString filename)
{
    if(filename != "")
    {
        this->filename = filename;
    }

    QFile data(this->filename);
    if(data.open(QIODevice::WriteOnly))
    {
        data.write(this->getJSON().toJson());
        data.close();
    }
    else
        qDebug() << QString("Impossible d'ouvrir le ficher");
}

QJsonDocument Projector::getJSON()
{
    QJsonObject projector = QJsonObject();
    projector.insert("type", "projector");
    projector.insert("model", this->model);
    projector.insert("brand", this->brand);
    projector.insert("lightSourceType", this->lightSourceType);
    projector.insert("powerConsumption", this->powerConsumption);
    projector.insert("voltage", this->voltage);
    projector.insert("fuse", this->fuse);
    projector.insert("IPClass", this->IPClass);
    projector.insert("weight", this->weight);
    projector.insert("lightAngle", this->lightAngle);
    projector.insert("lightIntensity", this->lightIntensity);
    projector.insert("lightIntensityDistance", this->lightIntensityDistance);

    QJsonObject dim = QJsonObject();
    dim.insert("x", this->dimensions.x());
    dim.insert("y", this->dimensions.y());
    dim.insert("z", this->dimensions.z());
    projector.insert("dimensions", dim);

    QJsonArray con = QJsonArray();
    for(int i = 0; i<connectors.length(); i++)
    {
        con.append(connectors.at(i));
    }
    projector.insert("connectors", con);

    QJsonArray chan = QJsonArray();
    for(int i = 0; i<channelModes.length(); i++)
    {
        chan.append(channelModes.at(i));
    }
    projector.insert("channelModes", chan);

    QJsonArray chans = QJsonArray();
    for(int i = 0; i<channels.length(); i++)
    {
        QJsonArray schan = QJsonArray();
        for(int j = 0; j<channels.at(i).length(); j++)
        {
            schan.append(channels.at(i).at(j)->getJSON().toVariant().toJsonObject());
        }
        chans.append(schan);
    }
    projector.insert("channels",chans);


    QJsonDocument json;
    json.setObject(projector);
    return json;
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


QList<Channel*> Projector::getChannels(int id)
{
    if(id < this->channels.length())
    {
        return this->channels.at(id);
    }
    else
    {
        return QList<Channel*>();
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

void Projector::addChannelMode(int channelsCount, QList<Channel*> channels)
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

#include "projector_old.h"

Projector_old::Projector_old(QVector3D pos, int address, double distance_attache_rotation, double angle, QObject *parent)
    : QObject{parent}
{
    // Attribution de la position
    this->pos = pos;

    // Attribution de l'identifiant
    this->address = address;

    this->distance_attache_rotation = distance_attache_rotation;
    this->angle = angle;
}

QVector3D Projector_old::get_pos()
{
    return this->pos;
}

void Projector_old::set_position(QVector3D pos)
{
    this->pos = pos;
}

int Projector_old::get_address()
{
    return this->address;
}

void Projector_old::set_address(int address)
{
    this->address = address;
}

void Projector_old::set_mode(Modes mode)
{
    this->mode = mode;
}

Modes Projector_old::get_mode()
{
    return this->mode;
}

void Projector_old::set_color(QColor _color)
{
    this->color = _color;
}

QColor Projector_old::get_color()
{
    return this->color;
}

void Projector_old::set_angle(double angle)
{
    if (angle >= 0 && angle < 360)
        this->angle = angle;
    else if (angle == 360)
        this->angle = 0;
    else if (angle > 360)
    {
        while (angle > 360)
            angle -= 360;
        this->angle = angle;
    }
}

double Projector_old::get_angle()
{
    return this->angle;
}

void Projector_old::set_size(int height, int width, int dimension)
{
    // si les tailles sont négatives ou nulles, on n'attribut pas
    if (height > 0)
        this->size.height = height;
    if (width > 0)
        this->size.width = width;
    if (dimension > 0)
        this->size.dimension = dimension;
}

Size Projector_old::get_size()
{
    return this->size;
}

void Projector_old::set_distance_attache_rotation(double distance)
{
    this->distance_attache_rotation = distance;
}

double Projector_old::get_distance_attache_rotation()
{
    return this->distance_attache_rotation;
}

QString Projector_old::get_name()
{
    return this->name;
}

void Projector_old::set_name(QString name)
{
    this->name = name;
}

double Projector_old::get_weight()
{
    return this->weight;
}

void Projector_old::set_weight(double weight)
{
    this->weight = weight;
}

QString Projector_old::get_model()
{
    return this->model;
}

void Projector_old::set_model(QString model)
{
    this->model = model;
}

QString Projector_old::get_brand()
{
    return this->brand;
}

void Projector_old::set_brand(QString brand)
{
    this->brand = brand;
}

int Projector_old::get_nb_channel()
{
    return this->nb_channel;
}

void Projector_old::set_nb_channel(int nb_channel)
{
    this->nb_channel = nb_channel;
}

void Projector_old::add_channel(int place, QList<int> range)
{
    // Si la place du canal est -1, on l'intancie à la fin de la liste
    if (place == -1)
        this->channels.push_back(new Channel((int)(this->channels.size()) + 1, range));

    // sinon, on instancie un canal à la place d'un autre
    // donc on le désintancie et en instancie un autre à la place
    if (place >= 0 && place < (int)(this->channels.size()))
    {
        this->remove_channel(place);
        this->channels.insert(this->channels.begin() + place, new Channel(place, range));
    }

    // Ou encore, si on en instancie un à un endroit mémoire où aucun canal n'est défini, on l'intancie
    if (place >= (int)(this->channels.size()) && place <= 255)
        this->channels.insert(this->channels.begin() + place, new Channel(place, range));
}

void Projector_old::remove_channel(int place)
{
    // On désintancie un canal à la fin de la liste
    if (place == -1)
        this->channels.removeAt(place); // On désalloue la mémoire

    // On veut désintancier un canal dans ceux déjà instancié
    if (place >= 0 && place < (int)(this->channels.size()))
        this->channels.removeAt(place); // On désalloue la mémoire
}

QList<Channel *> Projector_old::get_channels() { return this->channels; }

#include "data.h"




QDataStream& operator >> (QDataStream &in, DialyData &data)
{
	return in >> data.title >> data.time >> data.level >> data.path >> data.modify;
}
QDataStream& operator << (QDataStream &out, const DialyData &data)
{
	return out << data.title << data.time << data.level << data.path << data.modify;
}